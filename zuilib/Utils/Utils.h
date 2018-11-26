#ifndef __UTILS_H__
#define __UTILS_H__

#pragma once

namespace Zuilib {
	//统一资源ID, 字符串类型和整型统一输出为字符串类型
	class ZUILIB_API StringOrID
	{
	public:
		StringOrID(LPCWSTR lpString);
		StringOrID(unsigned int nID);

		LPCWSTR m_lpstr;
	};

    class CDuiString;
	class ZUILIB_API CDuiPoint : public tagPOINT
	{
	public:
		CDuiPoint();
		CDuiPoint(const POINT& src);
		CDuiPoint(long x, long y);
		CDuiPoint(LPARAM lParam);
        CDuiPoint(LPCWSTR pstrValue);
        CDuiString ToString();
	};

	class ZUILIB_API CDuiSize : public tagSIZE
	{
	public:
		CDuiSize();
		CDuiSize(const SIZE& src);
		CDuiSize(const RECT rc);
		CDuiSize(long cx, long cy);
        CDuiSize(LPCWSTR pstrValue);
        CDuiString ToString();
	};

	class ZUILIB_API CDuiRect : public tagRECT
	{
	public:
		CDuiRect();
		CDuiRect(const RECT& src);
		CDuiRect(long iLeft, long iTop, long iRight, long iBottom);
        CDuiRect(LPCWSTR pstrValue);
        CDuiString ToString();

		int GetWidth() const;
		int GetHeight() const;
		void Empty();
		bool IsNull() const;
		void Join(const RECT& rc);
		void ResetOffset();
		void Normalize();
		void Offset(int cx, int cy);
		void Inflate(int cx, int cy);
		void Deflate(int cx, int cy);
		void Union(CDuiRect& rc);
	};

    class ZUILIB_API CDuiString
    {
    public:
        enum { MAX_LOCAL_STRING_LEN = 63 };

        CDuiString();
        CDuiString(const WCHAR ch);
        CDuiString(const CDuiString& src);
        CDuiString(LPCWSTR lpsz, int nLen = -1);
        ~CDuiString();
        CDuiString ToString();

        void Empty();
        int GetLength() const;
        bool IsEmpty() const;
        WCHAR GetAt(int nIndex) const;
        void Append(LPCWSTR pstr);
        void Assign(LPCWSTR pstr, int nLength = -1);
		LPCWSTR GetData() const;

        void SetAt(int nIndex, WCHAR ch);
        operator LPCWSTR() const;

        WCHAR operator[] (int nIndex) const;
        const CDuiString& operator=(const CDuiString& src);
        const CDuiString& operator=(const WCHAR ch);

        const CDuiString& operator=(LPCWSTR pstr);

        const CDuiString& operator=(LPCSTR lpStr);
        const CDuiString& operator+=(LPCSTR lpStr);

        CDuiString operator+(const CDuiString& src) const;
        CDuiString operator+(LPCWSTR pstr) const;
        const CDuiString& operator+=(const CDuiString& src);
        const CDuiString& operator+=(LPCWSTR pstr);
        const CDuiString& operator+=(const WCHAR ch);

		bool operator == (const CDuiString& str) const;
		bool operator == (LPCWSTR str) const;
		bool operator != (const CDuiString& str) const;
		bool operator != (LPCWSTR str) const;
		bool operator <= (LPCWSTR str) const;
		bool operator <  (LPCWSTR str) const;
		bool operator >= (LPCWSTR str) const;
		bool operator >  (LPCWSTR str) const;

        int Compare(LPCWSTR pstr) const;
        int CompareNoCase(LPCWSTR pstr) const;

        void MakeUpper();
        void MakeLower();

        CDuiString Left(int nLength) const;
        CDuiString Mid(int iPos, int nLength = -1) const;
        CDuiString Right(int nLength) const;

        int Find(WCHAR ch, int iPos = 0) const;
        int Find(LPCWSTR pstr, int iPos = 0) const;
        int ReverseFind(WCHAR ch) const;
        int Replace(LPCWSTR pstrFrom, LPCWSTR pstrTo);

        int __cdecl Format(LPCWSTR pstrFormat, ...);
        int __cdecl SmallFormat(LPCWSTR pstrFormat, ...);

    protected:
        LPWSTR m_pstr;
        WCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
    };

	class ZUILIB_API CDuiPtrArray
	{
	public:
		CDuiPtrArray(int iPreallocSize = 0);
		CDuiPtrArray(const CDuiPtrArray& src);
		~CDuiPtrArray();

		void Empty();
		void Resize(int iSize);
		bool IsEmpty() const;
		int Find(LPVOID iIndex) const;
		bool Add(LPVOID pData);
		bool SetAt(int iIndex, LPVOID pData);
		bool InsertAt(int iIndex, LPVOID pData);
		bool Remove(int iIndex, int iCount = 1);
		int GetSize() const;
		LPVOID* GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPVOID* m_ppVoid;
		int m_nCount;
		int m_nAllocated;
	};

	class ZUILIB_API CDuiValArray
	{
	public:
		CDuiValArray(int iElementSize, int iPreallocSize = 0);
		~CDuiValArray();

		void Empty();
		bool IsEmpty() const;
		bool Add(LPCVOID pData);
		bool Remove(int iIndex,  int iCount = 1);
		int GetSize() const;
		LPVOID GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPBYTE m_pVoid;
		int m_iElementSize;
		int m_nCount;
		int m_nAllocated;
	};

    struct TITEM;
	class ZUILIB_API CDuiStringPtrMap
	{
	public:
		CDuiStringPtrMap(int nSize = 83);
		~CDuiStringPtrMap();

		void Resize(int nSize = 83);
		LPVOID Find(LPCWSTR key, bool optimize = true) const;
		bool Insert(LPCWSTR key, LPVOID pData);
		LPVOID Set(LPCWSTR key, LPVOID pData);
		bool Remove(LPCWSTR key);
		void RemoveAll();
		int GetSize() const;
		LPCWSTR GetAt(int iIndex) const;
		LPCWSTR operator[] (int nIndex) const;

	protected:
		TITEM** m_aT;
		int m_nBuckets;
		int m_nCount;
	};

	class ZUILIB_API CWaitCursor
	{
	public:
		CWaitCursor();
		~CWaitCursor();

	protected:
		HCURSOR m_hOrigCursor;
	};

	class CVariant : public VARIANT
	{
	public:
		CVariant() 
		{ 
			VariantInit(this); 
		}
		CVariant(int i)
		{
			VariantInit(this);
			this->vt = VT_I4;
			this->intVal = i;
		}
		CVariant(float f)
		{
			VariantInit(this);
			this->vt = VT_R4;
			this->fltVal = f;
		}
		CVariant(LPOLESTR s)
		{
			VariantInit(this);
			this->vt = VT_BSTR;
			this->bstrVal = s;
		}
		CVariant(IDispatch *disp)
		{
			VariantInit(this);
			this->vt = VT_DISPATCH;
			this->pdispVal = disp;
		}

		~CVariant() 
		{ 
			VariantClear(this); 
		}
	};

}// namespace Zuilib

#endif // __UTILS_H__