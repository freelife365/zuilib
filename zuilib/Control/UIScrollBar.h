#ifndef __UISCROLLBAR_H__
#define __UISCROLLBAR_H__

#pragma once

namespace zuilib
{
	class ZUILIB_API CScrollBarUI : public CControlUI
	{
	public:
		CScrollBarUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);

		CContainerUI* GetOwner() const;
		void SetOwner(CContainerUI* pOwner);

		void SetVisible(bool bVisible = true);
		void SetEnabled(bool bEnable = true);
		void SetFocus();

		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);
		int GetScrollRange() const;
		void SetScrollRange(int nRange);
		int GetScrollPos() const;
		void SetScrollPos(int nPos, bool bTriggerEvent=true);
		int GetLineSize() const;
		void SetLineSize(int nSize);
		int GetScrollUnit() const;
		void SetScrollUnit(int iUnit);

		bool GetShowButton1();
		void SetShowButton1(bool bShow);
		DWORD GetButton1Color() const;
		void SetButton1Color(DWORD dwColor);
		LPCWSTR GetButton1NormalImage();
		void SetButton1NormalImage(LPCWSTR pStrImage);
		LPCWSTR GetButton1HotImage();
		void SetButton1HotImage(LPCWSTR pStrImage);
		LPCWSTR GetButton1PushedImage();
		void SetButton1PushedImage(LPCWSTR pStrImage);
		LPCWSTR GetButton1DisabledImage();
		void SetButton1DisabledImage(LPCWSTR pStrImage);

		bool GetShowButton2();
		void SetShowButton2(bool bShow);
		DWORD GetButton2Color() const;
		void SetButton2Color(DWORD dwColor);
		LPCWSTR GetButton2NormalImage();
		void SetButton2NormalImage(LPCWSTR pStrImage);
		LPCWSTR GetButton2HotImage();
		void SetButton2HotImage(LPCWSTR pStrImage);
		LPCWSTR GetButton2PushedImage();
		void SetButton2PushedImage(LPCWSTR pStrImage);
		LPCWSTR GetButton2DisabledImage();
		void SetButton2DisabledImage(LPCWSTR pStrImage);

		DWORD GetThumbColor() const;
		void SetThumbColor(DWORD dwColor);
		LPCWSTR GetThumbNormalImage();
		void SetThumbNormalImage(LPCWSTR pStrImage);
		LPCWSTR GetThumbHotImage();
		void SetThumbHotImage(LPCWSTR pStrImage);
		LPCWSTR GetThumbPushedImage();
		void SetThumbPushedImage(LPCWSTR pStrImage);
		LPCWSTR GetThumbDisabledImage();
		void SetThumbDisabledImage(LPCWSTR pStrImage);

		LPCWSTR GetRailNormalImage();
		void SetRailNormalImage(LPCWSTR pStrImage);
		LPCWSTR GetRailHotImage();
		void SetRailHotImage(LPCWSTR pStrImage);
		LPCWSTR GetRailPushedImage();
		void SetRailPushedImage(LPCWSTR pStrImage);
		LPCWSTR GetRailDisabledImage();
		void SetRailDisabledImage(LPCWSTR pStrImage);

		LPCWSTR GetBkNormalImage();
		void SetBkNormalImage(LPCWSTR pStrImage);
		LPCWSTR GetBkHotImage();
		void SetBkHotImage(LPCWSTR pStrImage);
		LPCWSTR GetBkPushedImage();
		void SetBkPushedImage(LPCWSTR pStrImage);
		LPCWSTR GetBkDisabledImage();
		void SetBkDisabledImage(LPCWSTR pStrImage);

		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);

		bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

		void PaintBk(HDC hDC);
		void PaintButton1(HDC hDC);
		void PaintButton2(HDC hDC);
		void PaintThumb(HDC hDC);
		void PaintRail(HDC hDC);

	protected:

		enum
		{ 
			DEFAULT_SCROLLBAR_SIZE = 16,
			DEFAULT_TIMERID = 10,
		};

		bool m_bHorizontal;
		int m_nRange;
		int m_nScrollPos;
		int m_nLineSize;
		int m_nScrollUnit;
		CContainerUI* m_pOwner;
		POINT ptLastMouse;
		int m_nLastScrollPos;
		int m_nLastScrollOffset;
		int m_nScrollRepeatDelay;

		TDrawInfo m_diBkNormal;
		TDrawInfo m_diBkHot;
		TDrawInfo m_diBkPushed;
		TDrawInfo m_diBkDisabled;

		bool m_bShowButton1;
		RECT m_rcButton1;
		UINT m_uButton1State;
		DWORD m_dwButton1Color;
		TDrawInfo m_diButton1Normal;
		TDrawInfo m_diButton1Hot;
		TDrawInfo m_diButton1Pushed;
		TDrawInfo m_diButton1Disabled;

		bool m_bShowButton2;
		RECT m_rcButton2;
		UINT m_uButton2State;
		DWORD m_dwButton2Color;
		TDrawInfo m_diButton2Normal;
		TDrawInfo m_diButton2Hot;
		TDrawInfo m_diButton2Pushed;
		TDrawInfo m_diButton2Disabled;

		RECT m_rcThumb;
		UINT m_uThumbState;
		DWORD m_dwThumbColor;
		TDrawInfo m_diThumbNormal;
		TDrawInfo m_diThumbHot;
		TDrawInfo m_diThumbPushed;
		TDrawInfo m_diThumbDisabled;

		TDrawInfo m_diRailNormal;
		TDrawInfo m_diRailHot;
		TDrawInfo m_diRailPushed;
		TDrawInfo m_diRailDisabled;
	};
}

#endif // __UISCROLLBAR_H__