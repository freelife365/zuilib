#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#pragma once

namespace zuilib
{
	class CDateTimeWnd;

	/// 时间选择控件
	class ZUILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);

		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;

		void UpdateText();

		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void Move(SIZE szOffset, bool bNeedInvalidate = true);

		void DoEvent(TEventUI& event);

	protected:
		SYSTEMTIME m_sysTime;
		int        m_nDTUpdateFlag;
		bool       m_bReadOnly;

		CDateTimeWnd* m_pWindow;
	};
}
#endif // __UIDATETIME_H__