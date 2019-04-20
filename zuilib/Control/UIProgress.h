#ifndef __UIPROGRESS_H__
#define __UIPROGRESS_H__

#pragma once

namespace zuilib {

	class ZUILIB_API CProgressUI : public CLabelUI
	{
	public:
		CProgressUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);

		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);
		int GetMinValue() const;
		void SetMinValue(int nMin);
		int GetMaxValue() const;
		void SetMaxValue(int nMax);
		int GetValue() const;
		void SetValue(int nValue);
		LPCWSTR GetForeImage() const;
		void SetForeImage(LPCWSTR pStrImage);

		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		bool m_bHorizontal;
		int m_nMax;
		int m_nMin;
		int m_nValue;

		TDrawInfo m_diFore;
	};

} // namespace zuilib

#endif // __UIPROGRESS_H__
