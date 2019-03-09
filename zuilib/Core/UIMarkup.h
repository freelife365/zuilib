#ifndef __UIMARKUP_H__
#define __UIMARKUP_H__

#pragma once

#include "Utils/pugiconfig.hpp"
#include "Utils/pugixml.hpp"

namespace zuilib {

enum
{
	XMLFILE_ENCODING_UTF8 = 0,
	XMLFILE_ENCODING_UNICODE = 1,
	XMLFILE_ENCODING_ASNI = 2,
};

class ZUILIB_API pugi::xml_document;
typedef pugi::xml_document		XmlDoc;
typedef pugi::xml_node			XmlNode;
typedef pugi::xml_attribute		XmlAttr;
typedef pugi::xml_parse_result	XmlResult;


class ZUILIB_API CMarkup
{
public:
	CMarkup(LPCWSTR pstrXML = NULL);
	~CMarkup();

	bool Load(LPCWSTR pstrXML);
	bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8);
	bool LoadFromFile(LPCWSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8);
	void Release();
	bool IsValid() const;

	void SetPreserveWhitespace(bool bPreserve = true);
	void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
	void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

	XmlNode GetRoot();
private:
	//XML�ڵ�Ԫ�����Ͷ��� 
	typedef struct tagXMLELEMENT
	{
		ULONG iStart;	//�ڵ�Ԫ����xml�ļ��е���ʼλ��
		ULONG iChild;	//�ڵ�Ԫ���ӽڵ�
		ULONG iNext;	//�ڵ�Ԫ�ص���һ���ڵ�(�ֵܽڵ�)
		ULONG iParent;	//�ڵ�Ԫ�صĸ��ڵ�
		ULONG iData;	//�ڵ�Ԫ�ص�����
	} XMLELEMENT;

	LPTSTR m_pstrXML; //ΪCMarkup�洢���Լ���xml�ļ��������ݵ�ָ�뻺����
	XmlDoc m_parser;

	XMLELEMENT* m_pElements;		//����XMLELEMENT���͵Ľڵ�Ԫ����Ϣ�Ļ���������ʵ�Ͽ����в���δԤ�ϵĴ洢�ռ䣻
	ULONG m_nElements;				//ʵ�ʵı���m_pElements����Ч�Ľڵ�Ԫ����
	ULONG m_nReservedElements = 0;	//Ԥ����m_pElements�������ռ��С
	WCHAR m_szErrorMsg[100];
	WCHAR m_szErrorXML[50];
	bool m_bPreserveWhitespace;

private:
	bool _Parse();
	bool _Parse(LPTSTR& pstrText, ULONG iParent);
	XMLELEMENT* _ReserveElement();
	inline void _SkipWhitespace(LPTSTR& pstr) const;
	inline void _SkipWhitespace(LPCWSTR& pstr) const;
	inline void _SkipIdentifier(LPTSTR& pstr) const;
	inline void _SkipIdentifier(LPCWSTR& pstr) const;
	bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);
	void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);
	bool _ParseAttributes(LPTSTR& pstrText);
	bool _Failed(LPCWSTR pstrError, LPCWSTR pstrLocation = NULL);
};

} // namespace ZuiLib

#endif // __UIMARKUP_H__
