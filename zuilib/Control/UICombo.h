#ifndef __UICOMBO_H__
#define __UICOMBO_H__

#pragma once

namespace zuilib {

class CComboWnd;
class ZUILIB_API CComboUI : public CContainerUI, public IListOwnerUI
{
	friend class CComboWnd;
public:
	CComboUI();

	LPCWSTR GetClass() const;
	LPVOID GetInterface(LPCWSTR pstrName);

	void DoInit();
	UINT GetControlFlags() const;

	CDuiString GetText() const;
	void SetEnabled(bool bEnable = true);

	CDuiString GetDropBoxAttributeList();
	void SetDropBoxAttributeList(LPCWSTR pstrList);
	SIZE GetDropBoxSize() const;
	void SetDropBoxSize(SIZE szDropBox);

	int GetCurSel() const;
	bool GetSelectCloseFlag();
	void SetSelectCloseFlag(bool flag);
	bool SelectItem(int iIndex, bool bTakeFocus = false, bool bTriggerEvent=true);
	bool ExpandItem(int iIndex, bool bExpand = true);
	int GetExpandedItem() const;

	bool SetItemIndex(CControlUI* pControl, int iNewIndex);
	bool SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
	bool RemoveAt(int iIndex, bool bDoNotDestroy=false);
	void RemoveAll();

	bool Activate();

	bool GetShowText() const;
	void SetShowText(bool flag);

	void SetTextColor(DWORD dwTextColor);
	DWORD GetTextColor() const;
	void SetDisabledTextColor(DWORD dwTextColor);
	DWORD GetDisabledTextColor() const;
	void SetFont(int index);
	int GetFont() const;

	RECT GetTextPadding() const;
	void SetTextPadding(RECT rc);
	LPCWSTR GetNormalImage() const;
	void SetNormalImage(LPCWSTR pStrImage);
	LPCWSTR GetHotImage() const;
	void SetHotImage(LPCWSTR pStrImage);
	LPCWSTR GetPushedImage() const;
	void SetPushedImage(LPCWSTR pStrImage);
	LPCWSTR GetFocusedImage() const;
	void SetFocusedImage(LPCWSTR pStrImage);
	LPCWSTR GetDisabledImage() const;
	void SetDisabledImage(LPCWSTR pStrImage);

	TListInfoUI* GetListInfo();
	UINT GetItemFixedHeight();
	void SetItemFixedHeight(UINT nHeight);
	int GetItemFont(int index);
	void SetItemFont(int index);
	UINT GetItemTextStyle();
	void SetItemTextStyle(UINT uStyle);
	RECT GetItemTextPadding() const;
	void SetItemTextPadding(RECT rc);
	DWORD GetItemTextColor() const;
	void SetItemTextColor(DWORD dwTextColor);
	DWORD GetItemBkColor() const;
	void SetItemBkColor(DWORD dwBkColor);
	LPCWSTR GetItemBkImage() const;
	void SetItemBkImage(LPCWSTR pStrImage);
	bool IsAlternateBk() const;
	void SetAlternateBk(bool bAlternateBk);
	DWORD GetSelectedItemTextColor() const;
	void SetSelectedItemTextColor(DWORD dwTextColor);
	DWORD GetSelectedItemBkColor() const;
	void SetSelectedItemBkColor(DWORD dwBkColor);
	LPCWSTR GetSelectedItemImage() const;
	void SetSelectedItemImage(LPCWSTR pStrImage);
	DWORD GetHotItemTextColor() const;
	void SetHotItemTextColor(DWORD dwTextColor);
	DWORD GetHotItemBkColor() const;
	void SetHotItemBkColor(DWORD dwBkColor);
	LPCWSTR GetHotItemImage() const;
	void SetHotItemImage(LPCWSTR pStrImage);
	DWORD GetDisabledItemTextColor() const;
	void SetDisabledItemTextColor(DWORD dwTextColor);
	DWORD GetDisabledItemBkColor() const;
	void SetDisabledItemBkColor(DWORD dwBkColor);
	LPCWSTR GetDisabledItemImage() const;
	void SetDisabledItemImage(LPCWSTR pStrImage);
	int GetItemHLineSize() const;
	void SetItemHLineSize(int iSize);
	DWORD GetItemHLineColor() const;
	void SetItemHLineColor(DWORD dwLineColor);
	int GetItemVLineSize() const;
	void SetItemVLineSize(int iSize);
	DWORD GetItemVLineColor() const;
	void SetItemVLineColor(DWORD dwLineColor);
	bool IsItemShowHtml();
	void SetItemShowHtml(bool bShowHtml = true);

	SIZE EstimateSize(SIZE szAvailable);
	void SetPos(RECT rc, bool bNeedInvalidate = true);
	void Move(SIZE szOffset, bool bNeedInvalidate = true);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
	
	bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

	LPCTSTR GetVscrollbar() const;
	LPCTSTR GetHscrollbar() const;
	LPCTSTR GetVscrollStyle() const;
	LPCTSTR GetHscrollStyle() const;
protected:
	CComboWnd* m_pWindow;

	int m_iCurSel;
	bool m_bShowText;
	bool m_bSelectCloseFlag;
	RECT m_rcTextPadding;
	CDuiString m_sDropBoxAttributes;
	CDuiString m_sVscrollbar;
	CDuiString m_sVscrollbarStyle;
	CDuiString m_sHscrollbar;
	CDuiString m_sHscrollStyle;
	SIZE m_szDropBox;
	UINT m_uButtonState;

	int		m_iFont;
	DWORD	m_dwTextColor;
	DWORD	m_dwDisabledTextColor;
	UINT	m_uTextStyle;

	TDrawInfo m_diNormal;
	TDrawInfo m_diHot;
	TDrawInfo m_diPushed;
	TDrawInfo m_diFocused;
	TDrawInfo m_diDisabled;

	TListInfoUI m_ListInfo;
};

} // namespace zuilib

#endif // __UICOMBO_H__
