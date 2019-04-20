#ifndef __UIOPTION_H__
#define __UIOPTION_H__

#pragma once

namespace zuilib {

	class ZUILIB_API COptionUI : public CButtonUI
	{
	public:
		COptionUI();
		~COptionUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);

		void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);

		bool Activate();
		void SetEnabled(bool bEnable = true);

		LPCWSTR GetSelectedImage();
		void SetSelectedImage(LPCWSTR pStrImage);

		LPCWSTR GetSelectedHotImage();
		void SetSelectedHotImage(LPCWSTR pStrImage);

		void SetSelectedTextColor(DWORD dwTextColor);
		DWORD GetSelectedTextColor();

		void SetSelectedBkColor(DWORD dwBkColor);
		DWORD GetSelectedBkColor();
		DUI_DEPRECATED DWORD GetSelectBkColor(); // deprecated, use GetSelectedBkColor instead

		LPCWSTR GetForeImage();
		void SetForeImage(LPCWSTR pStrImage);

		LPCWSTR GetGroup() const;
		void SetGroup(LPCWSTR pStrGroupName = NULL);
		bool IsSelected() const;
		virtual void Selected(bool bSelected, bool bTriggerEvent=true);

		SIZE EstimateSize(SIZE szAvailable);
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);

	protected:
		bool			m_bSelected;
		CDuiString		m_sGroupName;

		DWORD			m_dwSelectedBkColor;
		DWORD			m_dwSelectedTextColor;

		TDrawInfo		m_diSelected;
		TDrawInfo		m_diSelectedHot;
		TDrawInfo		m_diFore;
	};

} // namespace zuilib

#endif // __UIOPTION_H__