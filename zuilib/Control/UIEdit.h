#ifndef __UIEDIT_H__
#define __UIEDIT_H__

#pragma once

namespace zuilib {

	class CEditWnd;

	class ZUILIB_API CEditUI : public CLabelUI
	{
		friend class CEditWnd;
	public:
		CEditUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		void SetEnabled(bool bEnable = true);
		void SetText(LPCWSTR pstrText);
		void SetMaxChar(UINT uMax);
		UINT GetMaxChar();
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void SetPasswordMode(bool bPasswordMode);
		bool IsPasswordMode() const;
		void SetPasswordChar(WCHAR cPasswordChar);
		WCHAR GetPasswordChar() const;
		bool IsAutoSelAll();
		void SetAutoSelAll(bool bAutoSelAll);
		void SetNumberOnly(bool bNumberOnly);
		bool IsNumberOnly() const;
		int GetWindowStyls() const;
		HWND GetNativeEditHWND() const;

		LPCWSTR GetNormalImage();
		void SetNormalImage(LPCWSTR pStrImage);
		LPCWSTR GetHotImage();
		void SetHotImage(LPCWSTR pStrImage);
		LPCWSTR GetFocusedImage();
		void SetFocusedImage(LPCWSTR pStrImage);
		LPCWSTR GetDisabledImage();
		void SetDisabledImage(LPCWSTR pStrImage);
		void SetNativeEditBkColor(DWORD dwBkColor);
		DWORD GetNativeEditBkColor() const;

		void SetSel(long nStartChar, long nEndChar);
		void SetSelAll();
		void SetReplaceSel(LPCWSTR lpszReplace);

		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void Move(SIZE szOffset, bool bNeedInvalidate = true);
		void SetVisible(bool bVisible = true);
		void SetInternVisible(bool bVisible = true);
		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);

	protected:
		CEditWnd* m_pWindow;

		UINT m_uMaxChar;
		bool m_bReadOnly;
		bool m_bPasswordMode;
		bool m_bAutoSelAll;
		WCHAR m_cPasswordChar;
		UINT m_uButtonState;
		DWORD m_dwEditbkColor;
		int m_iWindowStyls;

		TDrawInfo m_diNormal;
		TDrawInfo m_diHot;
		TDrawInfo m_diFocused;
		TDrawInfo m_diDisabled;
	};
}
#endif // __UIEDIT_H__