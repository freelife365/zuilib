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

typedef pugi::xml_document		XmlDoc;
typedef pugi::xml_node			XmlNode;
typedef pugi::xml_attribute		XmlAttr;
typedef pugi::xml_parse_result	XmlResult;



class CMarkup;
class CMarkupNode;


class ZUILIB_API CMarkup
{
	friend class CMarkupNode;
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
	//XML节点元素类型定义 
	typedef struct tagXMLELEMENT
	{
		ULONG iStart;	//节点元素在xml文件中的起始位置
		ULONG iChild;	//节点元素子节点
		ULONG iNext;	//节点元素的下一个节点(兄弟节点)
		ULONG iParent;	//节点元素的父节点
		ULONG iData;	//节点元素的数据
	} XMLELEMENT;

	LPTSTR m_pstrXML;			//为CMarkup存储的以加载xml文件数据内容的指针缓冲区
	XmlDoc m_parser;

	XMLELEMENT* m_pElements;	//保存XMLELEMENT类型的节点元素信息的缓冲区，事实上可能有部分未预料的存储空间；
	ULONG m_nElements;			//实际的保存m_pElements中有效的节点元素数
	ULONG m_nReservedElements = 0;	//预留的m_pElements缓冲区空间大小
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


#if 0
class ZUILIB_API CMarkupNode
{
	friend class CMarkup;
private:
	CMarkupNode();
	CMarkupNode(CMarkup* pOwner, int iPos);

public:
	bool IsValid() const;

	CMarkupNode GetParent();
	CMarkupNode GetSibling();
	CMarkupNode GetChild();
	CMarkupNode GetChild(LPCWSTR pstrName);

	bool HasSiblings() const;
	bool HasChildren() const;
	LPCWSTR GetName() const;
	LPCWSTR GetValue() const;

	bool HasAttributes();
	bool HasAttribute(LPCWSTR pstrName);
	int GetAttributeCount();
	LPCWSTR GetAttributeName(int iIndex);
	LPCWSTR GetAttributeValue(int iIndex);
	LPCWSTR GetAttributeValue(LPCWSTR pstrName);
	bool GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax);
	bool GetAttributeValue(LPCWSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax);

private:
	void _MapAttributes();

	enum { MAX_XML_ATTRIBUTES = 64 };

	//节点属性结构体定义
	typedef struct
	{
		ULONG iName;  //属性名
		ULONG iValue; //属性值
	} XMLATTRIBUTE;

	int m_iPos; //指定该属性节点在所属拥有者(指CMarkup对象)中的节点元素中的当前位置
	int m_nAttributes; //节点中属性数
	XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES]; //节点支持最多64个属性个数
	CMarkup* m_pOwner; //该节点所属拥有者(指CMarkup对象)
};
#endif // 

} // namespace ZuiLib

#endif // __UIMARKUP_H__
