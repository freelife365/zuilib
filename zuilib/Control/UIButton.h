#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#pragma once

namespace zuilib {

	class ZUILIB_API CButtonUI : public CLabelUI
	{
	public:
		CButtonUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);
		UINT GetControlFlags() const;

		bool Activate();
		void SetEnabled(bool bEnable = true);
		void DoEvent(TEventUI& event);

		LPCWSTR GetNormalImage();
		void SetNormalImage(LPCWSTR pStrImage);
		LPCWSTR GetHotImage();
		void SetHotImage(LPCWSTR pStrImage);
		LPCWSTR GetPushedImage();
		void SetPushedImage(LPCWSTR pStrImage);
		LPCWSTR GetFocusedImage();
		void SetFocusedImage(LPCWSTR pStrImage);
		LPCWSTR GetDisabledImage();
		void SetDisabledImage(LPCWSTR pStrImage);
		LPCWSTR GetForeImage();
		void SetForeImage(LPCWSTR pStrImage);
		LPCWSTR GetHotForeImage();
		void SetHotForeImage(LPCWSTR pStrImage);
		CDuiString GetCursor();
		void SetCursor(const CDuiString& strCursor);
		UINT GetButtonState() {return m_uButtonState;};

		// 对应按钮的5个状态图
		void SetFiveStatusImage(LPCWSTR pStrImage);
		void SetFadeAlphaDelta(BYTE uDelta);
		BYTE GetFadeAlphaDelta();

		void SetHotBkColor(DWORD dwColor);
		DWORD GetHotBkColor() const;
		void SetHotBorderColor(DWORD dwColor);
		DWORD GetHotBorderColor() const;
		void SetHotTextColor(DWORD dwColor);
		DWORD GetHotTextColor() const;
		void SetPushedTextColor(DWORD dwColor);
		DWORD GetPushedTextColor() const;
		void SetFocusedTextColor(DWORD dwColor);
		DWORD GetFocusedTextColor() const;
		void SetFocusedBkColor(DWORD dwColor);
		DWORD GetFocusedBkColor() const;
		SIZE EstimateSize(SIZE szAvailable);
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);

		void PaintText(HDC hDC);
		void PaintBkColor(HDC hDC);
		void PaintStatusImage(HDC hDC);
		void PaintBorder(HDC hDC);

	protected:
		enum
		{ 
			FADE_TIMERID = 11,
			FADE_ELLAPSE = 30,
		};

		UINT m_uButtonState;
		CDuiString m_sCursor;	//光标形状 arrow/hand 其他根据需要添加

		DWORD m_dwHotBkColor;
		DWORD m_dwHotTextColor;
		DWORD m_dwHotBorderColor;
		DWORD m_dwPushedTextColor;
		DWORD m_dwFocusedTextColor;
		DWORD m_dwFocusedBkColor;
		
		BYTE m_uFadeAlpha;
		BYTE m_uFadeAlphaDelta;

		TDrawInfo m_diNormal;
		TDrawInfo m_diHot;
		TDrawInfo m_diHotFore;
		TDrawInfo m_diPushed;
		TDrawInfo m_diPushedFore;
		TDrawInfo m_diFocused;
		TDrawInfo m_diDisabled;
	};

}	// namespace zuilib

#endif // __UIBUTTON_H__