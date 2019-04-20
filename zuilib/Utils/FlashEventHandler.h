
#ifndef __FLASH_EVENT_HANDLER_H__ 
#define __FLASH_EVENT_HANDLER_H__

#pragma once

namespace zuilib {

	class CFlashEventHandler
	{
	public:
		CFlashEventHandler() {}
		~CFlashEventHandler() {}

		virtual ULONG STDMETHODCALLTYPE Release( void ) { return S_OK;}
		virtual ULONG STDMETHODCALLTYPE AddRef( void ) { return S_OK;}

		virtual HRESULT OnReadyStateChange ( long newState )
		{
			return S_OK;
		}

		virtual HRESULT OnProgress (long percentDone )
		{
			return S_OK;
		}

		virtual HRESULT FSCommand ( LPCWSTR command, LPCWSTR args )
		{
			return S_OK;
		}
		
		virtual HRESULT FlashCall ( LPCWSTR request )
		{
			return S_OK;
		}
	};
}
#endif //__FLASH_EVENT_HANDLER_H__