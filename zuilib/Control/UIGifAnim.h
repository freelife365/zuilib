#ifndef GifAnimUI_h__
#define GifAnimUI_h__

#pragma once

namespace zuilib
{
	class CControl;

#define EVENT_TIEM_ID	100

	class ZUILIB_API CGifAnimUI : public CControlUI
	{
	public:
		CGifAnimUI(void);
		~CGifAnimUI(void);

		LPCWSTR	GetClass() const;
		LPVOID	GetInterface(LPCWSTR pstrName);
		void	DoInit() override;
		bool	DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		void	DoEvent(TEventUI& event);
		void	SetVisible(bool bVisible = true );
		void	SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
		void	SetBkImage(LPCWSTR pStrImage);
		LPCWSTR GetBkImage();

		void	SetAutoPlay(bool bIsAuto = true );
		bool	IsAutoPlay() const;
		void	SetAutoSize(bool bIsAuto = true );
		bool	IsAutoSize() const;
		void	PlayGif();
		void	PauseGif();
		void	StopGif();

	private:
		void	InitGifImage();
		void	DeleteGif();
		void    OnTimer( UINT_PTR idEvent );
		void	DrawFrame( HDC hDC );		// 绘制GIF每帧
		Gdiplus::Image*	LoadGifFromFile(LPCWSTR pstrGifPath);
		Gdiplus::Image* LoadGifFromMemory( LPVOID pBuf,size_t dwSize );
	private:
		Gdiplus::Image	*m_pGifImage;
		UINT			m_nFrameCount;				// gif图片总帧数
		UINT			m_nFramePosition;			// 当前放到第几帧
		Gdiplus::PropertyItem*	m_pPropertyItem;	// 帧与帧之间间隔时间

		CDuiString		m_sBkImage;
		bool			m_bIsAutoPlay;				// 是否自动播放gif
		bool			m_bIsAutoSize;				// 是否自动根据图片设置大小
		bool			m_bIsPlaying;
		IStream*	m_pStream;
	};
}

#endif // GifAnimUI_h__
