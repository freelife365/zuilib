#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#pragma once

namespace Zuilib {

class IDialogBuilderCallback
{
public:
    virtual CControlUI* CreateControl(LPCWSTR pstrClass) = 0;
};


class ZUILIB_API CDialogBuilder
{
public:
    CDialogBuilder();
    CControlUI* Create(StringOrID xml, LPCWSTR type = NULL, IDialogBuilderCallback* pCallback = NULL,
        CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
    CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, 
		CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);

    CMarkup* GetMarkup();

    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
private:
    CControlUI* _Parse(XmlNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);

    CMarkup m_xml;
    IDialogBuilderCallback* m_pCallback;
    LPCWSTR m_pstrtype;
};

} // namespace ZuiLib

#endif // __UIDLGBUILDER_H__
