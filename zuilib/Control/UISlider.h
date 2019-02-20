#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#pragma once

namespace zuilib
{
	class ZUILIB_API CSliderUI : public CProgressUI
	{
	public:
		CSliderUI();

		LPCWSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCWSTR pstrName);

		void SetEnabled(bool bEnable = true);

		int GetChangeStep();
		void SetChangeStep(int step);
		void SetThumbSize(SIZE szXY);
		RECT GetThumbRect() const;
		bool IsImmMode() const;
		void SetImmMode(bool bImmMode);
		LPCWSTR GetThumbImage() const;
		void SetThumbImage(LPCWSTR pStrImage);
		LPCWSTR GetThumbHotImage() const;
		void SetThumbHotImage(LPCWSTR pStrImage);
		LPCWSTR GetThumbPushedImage() const;
		void SetThumbPushedImage(LPCWSTR pStrImage);

		void DoEvent(TEventUI& event);
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		SIZE m_szThumb;
		UINT m_uButtonState;
		int m_nStep;
		bool m_bImmMode;

		TDrawInfo m_diThumb;
		TDrawInfo m_diThumbHot;
		TDrawInfo m_diThumbPushed;
	};
}

#endif // __UISLIDER_H__