#include "stdafx.h"

#ifndef TRACE
#define TRACE
#endif

DECLARE_HANDLE(HZIP);	// An HZIP identifies a zip file that has been opened
typedef DWORD ZRESULT;
typedef struct
{ 
	int index;                 // index of this file within the zip
	char name[MAX_PATH];       // filename within the zip
	DWORD attr;                // attributes, as in GetFileAttributes.
	FILETIME atime,ctime,mtime;// access, create, modify filetimes
	long comp_size;            // sizes of item, compressed and uncompressed. These
	long unc_size;             // may be -1 if not yet known (e.g. being streamed in)
} ZIPENTRY;

typedef struct
{ 
	int index;                 // index of this file within the zip
	WCHAR name[MAX_PATH];      // filename within the zip
	DWORD attr;                // attributes, as in GetFileAttributes.
	FILETIME atime,ctime,mtime;// access, create, modify filetimes
	long comp_size;            // sizes of item, compressed and uncompressed. These
	long unc_size;             // may be -1 if not yet known (e.g. being streamed in)
} ZIPENTRYW;

#define OpenZip OpenZipU
#define CloseZip(hz) CloseZipU(hz)
extern HZIP OpenZipU(void *z,unsigned int len,DWORD flags);
extern ZRESULT CloseZipU(HZIP hz);

#define ZIPENTRY ZIPENTRYW
#define GetZipItem GetZipItemW
#define FindZipItem FindZipItemW

extern ZRESULT GetZipItemW(HZIP hz, int index, ZIPENTRYW *ze);
extern ZRESULT FindZipItemW(HZIP hz, const WCHAR *name, bool ic, int *index, ZIPENTRYW *ze);
extern ZRESULT UnzipItem(HZIP hz, int index, void *dst, unsigned int len, DWORD flags);

namespace zuilib {

CMarkup::CMarkup(LPCWSTR pstrXML)
	: m_pstrXML(nullptr)
{
	m_pElements = NULL;
	m_bPreserveWhitespace = true;

	if( pstrXML != NULL ) 
		Load(pstrXML);
}

CMarkup::~CMarkup()
{
	Release();
}

bool CMarkup::IsValid() const
{
	XmlNode node = m_parser.root();
	return node.first_child() != NULL;
}

void CMarkup::SetPreserveWhitespace(bool bPreserve)
{
	m_bPreserveWhitespace = bPreserve;
}

bool CMarkup::Load(LPCWSTR pstrXML)
{
	Release();
	SIZE_T cchLen = _tcslen(pstrXML) + 1;
	m_pstrXML = static_cast<LPTSTR>(malloc(cchLen * sizeof(WCHAR)));
	::CopyMemory(m_pstrXML, pstrXML, cchLen * sizeof(WCHAR));
	bool bRes = _Parse();
	if( !bRes ) Release();
	return bRes;
}

bool CMarkup::LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding)
{
	if (encoding == XMLFILE_ENCODING_UTF8)
	{
		if( dwSize >= 3 && pByte[0] == 0xEF && pByte[1] == 0xBB && pByte[2] == 0xBF ) 
		{
			pByte += 3; dwSize -= 3;
		}
		DWORD nWide = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, NULL, 0 );

		m_pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(WCHAR)));

		::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, m_pstrXML, nWide );

		m_pstrXML[nWide] = _T('\0');
	}
	else if (encoding == XMLFILE_ENCODING_ASNI)
	{
		DWORD nWide = ::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pByte, dwSize, NULL, 0 );

		m_pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(WCHAR)));

		::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pByte, dwSize, m_pstrXML, nWide );

		m_pstrXML[nWide] = _T('\0');
	}
	else
	{
		if ( dwSize >= 2 && ( ( pByte[0] == 0xFE && pByte[1] == 0xFF ) || ( pByte[0] == 0xFF && pByte[1] == 0xFE ) ) )
		{
			dwSize = dwSize / 2 - 1;

			if ( pByte[0] == 0xFE && pByte[1] == 0xFF )
			{
				pByte += 2;

				for ( DWORD nSwap = 0 ; nSwap < dwSize ; nSwap ++ )
				{
					CHAR nTemp = pByte[ ( nSwap << 1 ) + 0 ];
					pByte[ ( nSwap << 1 ) + 0 ] = pByte[ ( nSwap << 1 ) + 1 ];
					pByte[ ( nSwap << 1 ) + 1 ] = nTemp;
				}
			}
			else
			{
				pByte += 2;
			}

			m_pstrXML = static_cast<LPTSTR>(malloc((dwSize + 1)*sizeof(WCHAR)));
			::CopyMemory( m_pstrXML, pByte, dwSize * sizeof(WCHAR) );
			m_pstrXML[dwSize] = _T('\0');

			pByte -= 2;
		}
	}

	bool bRes = _Parse();
	if( !bRes ) Release();
	return bRes;
}

bool CMarkup::LoadFromFile(LPCWSTR pstrFilename, int encoding)
{
	Release();
	CDuiString sFile = CPaintManagerUI::GetResourcePath();
	if( CPaintManagerUI::GetResourceZip().IsEmpty() ) {
		sFile += pstrFilename;
		HANDLE hFile = ::CreateFile(sFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if( hFile == INVALID_HANDLE_VALUE ) 
			return _Failed(_T("Error opening file"));

		DWORD dwSize = ::GetFileSize(hFile, NULL);
		if( dwSize == 0 ) 
			return _Failed(_T("File is empty"));

		if ( dwSize > 4096*1024 ) 
			return _Failed(_T("File too large"));

		DWORD dwRead = 0;
		BYTE* pByte = new BYTE[ dwSize ];
		::ReadFile( hFile, pByte, dwSize, &dwRead, NULL );
		::CloseHandle( hFile );

		if( dwRead != dwSize ) {
			delete[] pByte;
			Release();
			return _Failed(_T("Could not read file"));
		}
		bool ret = LoadFromMem(pByte, dwSize, encoding);
		delete[] pByte;

		return ret;
	}
	else {
		sFile += CPaintManagerUI::GetResourceZip();
		HZIP hz = NULL;
		if( CPaintManagerUI::IsCachedResourceZip() ) 
			hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
		else 
			hz = OpenZip((void*)sFile.GetData(), 0, 2);

		if( hz == NULL ) 
			return _Failed(_T("Error opening zip file"));

		ZIPENTRY ze; 
		int i; 
		if( FindZipItem(hz, pstrFilename, true, &i, &ze) != 0 ) 
			return _Failed(_T("Could not find ziped file"));

		DWORD dwSize = ze.unc_size;
		if( dwSize == 0 ) 
			return _Failed(_T("File is empty"));

		if ( dwSize > 4096*1024 ) 
			return _Failed(_T("File too large"));

		BYTE* pByte = new BYTE[ dwSize ];
		int res = UnzipItem(hz, i, pByte, dwSize, 3);
		if( res != 0x00000000 && res != 0x00000600) {
			delete[] pByte;
			if( !CPaintManagerUI::IsCachedResourceZip() ) CloseZip(hz);
			return _Failed(_T("Could not unzip file"));
		}
		if( !CPaintManagerUI::IsCachedResourceZip() ) 
			CloseZip(hz);

		bool ret = LoadFromMem(pByte, dwSize, encoding);
		delete[] pByte;

		return ret;
	}
}

void CMarkup::Release()
{
	if( m_pstrXML != NULL ) 
		free(m_pstrXML);
	if( m_pElements != NULL ) 
		free(m_pElements);

	m_pstrXML = NULL;
	m_pElements = NULL;
	m_nElements = 0;
}

void CMarkup::GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const
{
	_tcsncpy(pstrMessage, m_szErrorMsg, cchMax);
}

void CMarkup::GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const
{
	_tcsncpy(pstrSource, m_szErrorXML, cchMax);
}

XmlNode CMarkup::GetRoot()
{
	return m_parser.root();
}

bool CMarkup::_Parse()
{
	_ReserveElement(); // Reserve index 0 for errors
	::ZeroMemory(m_szErrorMsg, sizeof(m_szErrorMsg));
	::ZeroMemory(m_szErrorXML, sizeof(m_szErrorXML));
	LPTSTR pstrXML = m_pstrXML;

	XmlResult result = m_parser.load_string(pstrXML);

	return result.status == pugi::status_ok;
}

bool CMarkup::_Parse(LPTSTR& pstrText, ULONG iParent)
{
	_SkipWhitespace(pstrText);
	ULONG iPrevious = 0;

	for( ; ; ) 
	{
		if( *pstrText == _T('\0') && iParent <= 1 ) 
			return true;

		_SkipWhitespace(pstrText);
		if( *pstrText != _T('<') ) 
			return _Failed(_T("Expected start tag"), pstrText);

		if( pstrText[1] == _T('/') )
			return true;

		*pstrText++ = _T('\0');
		_SkipWhitespace(pstrText);

		// Skip comment or processing directive
		if( *pstrText == _T('!') || *pstrText == _T('?') ) {
			WCHAR ch = *pstrText;
			if( *pstrText == _T('!') ) 
				ch = _T('-');

			while( *pstrText != _T('\0') && !(*pstrText == ch && *(pstrText + 1) == _T('>')) ) 
				pstrText = ::CharNext(pstrText);

			if( *pstrText != _T('\0') ) 
				pstrText += 2;

			_SkipWhitespace(pstrText);
			continue;
		}
		_SkipWhitespace(pstrText);

		// Fill out element structure
		XMLELEMENT* pEl = _ReserveElement();
		ULONG iPos = pEl - m_pElements;
		pEl->iStart = pstrText - m_pstrXML;
		pEl->iParent = iParent;
		pEl->iNext = pEl->iChild = 0;
		if( iPrevious != 0 ) 
			m_pElements[iPrevious].iNext = iPos;
		else if( iParent > 0 ) 
			m_pElements[iParent].iChild = iPos;
		iPrevious = iPos;

		// Parse name
		LPCWSTR pstrName = pstrText;
		_SkipIdentifier(pstrText);
		LPTSTR pstrNameEnd = pstrText;
		if( *pstrText == _T('\0') ) 
			return _Failed(_T("Error parsing element name"), pstrText);

		// Parse attributes
		if( !_ParseAttributes(pstrText) ) 
			return false;

		_SkipWhitespace(pstrText);
		if( pstrText[0] == _T('/') && pstrText[1] == _T('>') )
		{
			pEl->iData = pstrText - m_pstrXML;
			*pstrText = _T('\0');
			pstrText += 2;
		}
		else
		{
			if( *pstrText != _T('>') ) 
				return _Failed(_T("Expected start-tag closing"), pstrText);

			// Parse node data
			pEl->iData = ++pstrText - m_pstrXML;
			LPTSTR pstrDest = pstrText;
			if( !_ParseData(pstrText, pstrDest, _T('<')) ) 
				return false;

			// Determine type of next element
			if( *pstrText == _T('\0') && iParent <= 1 ) 
				return true;
			if( *pstrText != _T('<') ) 
				return _Failed(_T("Expected end-tag start"), pstrText);

			if( pstrText[0] == _T('<') && pstrText[1] != _T('/') ) 
			{
				if( !_Parse(pstrText, iPos) ) 
					return false;
			}
			if( pstrText[0] == _T('<') && pstrText[1] == _T('/') ) 
			{
				*pstrDest = _T('\0');
				*pstrText = _T('\0');
				pstrText += 2;
				_SkipWhitespace(pstrText);
				SIZE_T cchName = pstrNameEnd - pstrName;
				if( _tcsncmp(pstrText, pstrName, cchName) != 0 ) 
					return _Failed(_T("Unmatched closing tag"), pstrText);
				pstrText += cchName;
				_SkipWhitespace(pstrText);
				if( *pstrText++ != _T('>') ) 
					return _Failed(_T("Unmatched closing tag"), pstrText);
			}
		}
		*pstrNameEnd = _T('\0');
		_SkipWhitespace(pstrText);
	}
}

CMarkup::XMLELEMENT* CMarkup::_ReserveElement()
{
	if( m_nElements == 0 ) 
		m_nReservedElements = 0;
	if( m_nElements >= m_nReservedElements ) {
		m_nReservedElements += (m_nReservedElements / 2) + 500;
		m_pElements = static_cast<XMLELEMENT*>(realloc(m_pElements, m_nReservedElements * sizeof(XMLELEMENT)));
	}
	return &m_pElements[m_nElements++];
}

void CMarkup::_SkipWhitespace(LPCWSTR& pstr) const
{
	while( *pstr > _T('\0') && *pstr <= _T(' ') ) 
		pstr = ::CharNext(pstr);
}

void CMarkup::_SkipWhitespace(LPTSTR& pstr) const
{
	while( *pstr > _T('\0') && *pstr <= _T(' ') ) 
		pstr = ::CharNext(pstr);
}

void CMarkup::_SkipIdentifier(LPCWSTR& pstr) const
{
	// 属性只能用英文，所以这样处理没有问题
	while( *pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr)) ) 
		pstr = ::CharNext(pstr);
}

void CMarkup::_SkipIdentifier(LPTSTR& pstr) const
{
	// 属性只能用英文，所以这样处理没有问题
	while( *pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr)) ) 
		pstr = ::CharNext(pstr);
}

bool CMarkup::_ParseAttributes(LPTSTR& pstrText)
{   
	if( *pstrText == _T('>') ) return true;
	*pstrText++ = _T('\0');
	_SkipWhitespace(pstrText);
	while( *pstrText != _T('\0') && *pstrText != _T('>') && *pstrText != _T('/') ) {
		_SkipIdentifier(pstrText);
		LPTSTR pstrIdentifierEnd = pstrText;
		_SkipWhitespace(pstrText);

		if( *pstrText != _T('=') ) 
			return _Failed(_T("Error while parsing attributes"), pstrText);

		*pstrText++ = _T(' ');
		*pstrIdentifierEnd = _T('\0');
		_SkipWhitespace(pstrText);
		if( *pstrText++ != _T('\"') ) 
			return _Failed(_T("Expected attribute value"), pstrText);

		LPTSTR pstrDest = pstrText;

		if( !_ParseData(pstrText, pstrDest, _T('\"')) ) 
			return false;

		if( *pstrText == _T('\0') ) 
			return _Failed(_T("Error while parsing attribute string"), pstrText);

		*pstrDest = _T('\0');
		if( pstrText != pstrDest ) 
			*pstrText = _T(' ');

		pstrText++;
		_SkipWhitespace(pstrText);
	}
	return true;
}

bool CMarkup::_ParseData(LPTSTR& pstrText, LPTSTR& pstrDest, char cEnd)
{
	while( *pstrText != _T('\0') && *pstrText != cEnd ) {
		if( *pstrText == _T('&') ) {
			while( *pstrText == _T('&') ) {
				_ParseMetaChar(++pstrText, pstrDest);
			}
			if (*pstrText == cEnd)
				break;
		}

		if( *pstrText == _T(' ') ) {
			*pstrDest++ = *pstrText++;
			if( !m_bPreserveWhitespace ) 
				_SkipWhitespace(pstrText);
		}
		else {
			LPTSTR pstrTemp = ::CharNext(pstrText);
			while( pstrText < pstrTemp) {
				*pstrDest++ = *pstrText++;
			}
		}
	}
	// Make sure that MapAttributes() works correctly when it parses
	// over a value that has been transformed.
	LPTSTR pstrFill = pstrDest + 1;
	while( pstrFill < pstrText ) 
		*pstrFill++ = _T(' ');
	return true;
}

void CMarkup::_ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest)
{
	if( pstrText[0] == _T('a') && pstrText[1] == _T('m') && pstrText[2] == _T('p') && pstrText[3] == _T(';') ) {
		*pstrDest++ = _T('&');
		pstrText += 4;
	}
	else if( pstrText[0] == _T('l') && pstrText[1] == _T('t') && pstrText[2] == _T(';') ) {
		*pstrDest++ = _T('<');
		pstrText += 3;
	}
	else if( pstrText[0] == _T('g') && pstrText[1] == _T('t') && pstrText[2] == _T(';') ) {
		*pstrDest++ = _T('>');
		pstrText += 3;
	}
	else if( pstrText[0] == _T('q') && pstrText[1] == _T('u') && pstrText[2] == _T('o') && pstrText[3] == _T('t') && pstrText[4] == _T(';') ) {
		*pstrDest++ = _T('\"');
		pstrText += 5;
	}
	else if( pstrText[0] == _T('a') && pstrText[1] == _T('p') && pstrText[2] == _T('o') && pstrText[3] == _T('s') && pstrText[4] == _T(';') ) {
		*pstrDest++ = _T('\'');
		pstrText += 5;
	}
	else {
		*pstrDest++ = _T('&');
	}
}

bool CMarkup::_Failed(LPCWSTR pstrError, LPCWSTR pstrLocation)
{
	// Register last error
	TRACE(_T("XML Error: %s"), pstrError);
	if( pstrLocation != NULL ) 
		TRACE(pstrLocation);
	_tcsncpy(m_szErrorMsg, pstrError, (sizeof(m_szErrorMsg) / sizeof(m_szErrorMsg[0])) - 1);
	_tcsncpy(m_szErrorXML, pstrLocation != NULL ? pstrLocation : _T(""), lengthof(m_szErrorXML) - 1);
	return false; // Always return 'false'
}

} // namespace ZuiLib
