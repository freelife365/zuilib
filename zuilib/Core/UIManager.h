#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#pragma once

#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;

class ZUILIB_API Gdiplus::RectF;
struct ZUILIB_API Gdiplus::GdiplusStartupInput;

namespace zuilib {

class CControlUI;

enum EVENTTYPE_UI
{
	UIEVENT__FIRST = 1,
	UIEVENT__KEYBEGIN,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT__KEYEND,
	UIEVENT__MOUSEBEGIN,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_RBUTTONDOWN,
	UIEVENT_DBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_SCROLLWHEEL,
	UIEVENT__MOUSEEND,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT__LAST,
};

// Flags for CControlUI::GetControlFlags()
constexpr auto UIFLAG_TABSTOP = 0x00000001;
constexpr auto UIFLAG_SETCURSOR = 0x00000002;
constexpr auto UIFLAG_WANTRETURN = 0x00000004;

// Flags for FindControl()
constexpr auto UIFIND_ALL = 0x00000000;
constexpr auto UIFIND_VISIBLE = 0x00000001;
constexpr auto UIFIND_ENABLED = 0x00000002;
constexpr auto UIFIND_HITTEST = 0x00000004;
constexpr auto UIFIND_UPDATETEST = 0x00000008;
constexpr auto UIFIND_TOP_FIRST = 0x00000010;
constexpr auto UIFIND_ME_FIRST = 0x80000000;

// Flags for the CDialogLayout stretching
constexpr auto UISTRETCH_NEWGROUP = 0x00000001;
constexpr auto UISTRETCH_NEWLINE = 0x00000002;
constexpr auto UISTRETCH_MOVE_X = 0x00000004;
constexpr auto UISTRETCH_MOVE_Y = 0x00000008;
constexpr auto UISTRETCH_SIZE_X = 0x00000010;
constexpr auto UISTRETCH_SIZE_Y = 0x00000020;

// Flags used for controlling the paint
constexpr auto UISTATE_FOCUSED = 0x00000001;
constexpr auto UISTATE_SELECTED = 0x00000002;
constexpr auto UISTATE_DISABLED = 0x00000004;
constexpr auto UISTATE_HOT = 0x00000008;
constexpr auto UISTATE_PUSHED = 0x00000010;
constexpr auto UISTATE_READONLY = 0x00000020;
constexpr auto UISTATE_CAPTURED = 0x00000040;


typedef struct ZUILIB_API tagTFontInfo
{
	HFONT hFont;
	CDuiString sFontName;
	int iSize;
	bool bBold;
	bool bUnderline;
	bool bItalic;
	bool bStrikeOut;
	TEXTMETRIC tm;
} TFontInfo;

typedef struct ZUILIB_API tagTImageInfo
{
	HBITMAP hBitmap;
	LPBYTE pBits;
	LPBYTE pSrcBits;
	int nX;
	int nY;
	bool bAlpha;
	bool bUseHSL;
	CDuiString sResType;
	DWORD dwMask;
} TImageInfo;

typedef struct ZUILIB_API tagTDrawInfo
{
	tagTDrawInfo();
	tagTDrawInfo(LPCWSTR lpsz);
	void Clear();
	CDuiString sDrawString;
	CDuiString sImageName;
	bool bLoaded;
	const TImageInfo* pImageInfo;
	RECT rcDestOffset;
	RECT rcBmpPart;
	RECT rcScale9;
	BYTE uFade;
	bool bHole;
	bool bTiledX;
	bool bTiledY;
} TDrawInfo;

typedef struct ZUILIB_API tagTPercentInfo
{
	double left;
	double top;
	double right;
	double bottom;
} TPercentInfo;

typedef struct ZUILIB_API tagTResInfo
{
	DWORD m_dwDefaultDisabledColor;
	DWORD m_dwDefaultFontColor;
	DWORD m_dwDefaultLinkFontColor;
	DWORD m_dwDefaultLinkHoverFontColor;
	DWORD m_dwDefaultSelectedBkColor;
	TFontInfo m_DefaultFontInfo;
	CDuiStringPtrMap m_CustomFontsHash;
	CDuiStringPtrMap m_ImageHash;
	CDuiStringPtrMap m_AttrHash;
	CDuiStringPtrMap m_MultiLanguageHash;
} TResInfo;

// Structure for notifications from the system
// to the control implementation.
typedef struct ZUILIB_API tagTEventUI
{
	int Type;
	CControlUI* pSender;
	ULONGLONG dwTimestamp;
	POINT ptMouse;
	WCHAR chKey;
	WORD wKeyState;
	WPARAM wParam;
	LPARAM lParam;
} TEventUI;

// Listener interface
class ZUILIB_API INotifyUI
{
public:
	virtual void Notify(TNotifyUI& msg) = 0;
};

// MessageFilter interface
class ZUILIB_API IMessageFilterUI
{
public:
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

class ZUILIB_API ITranslateAccelerator
{
public:
	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
using LPCREATE_CONTROL = CControlUI* (*)(LPCWSTR pstrType);

class ZUILIB_API CPaintManagerUI
{
public:
	CPaintManagerUI();
	~CPaintManagerUI();

public:
	void Init(HWND hWnd, LPCWSTR pstrName = NULL);
	bool IsUpdateNeeded() const;
	void NeedUpdate();
	void Invalidate();
	void Invalidate(RECT& rcItem);

	LPCWSTR GetName() const;
	HDC GetPaintDC() const;
	HBITMAP GetPaintOffscreenBitmap();
	HWND GetPaintWindow() const;
	HWND GetTooltipWindow() const;
	int GetTooltipWindowWidth() const;
	void SetTooltipWindowWidth(int iWidth);
	int GetHoverTime() const;
	void SetHoverTime(int iTime);

	POINT GetMousePos() const;
	SIZE GetClientSize() const;
	SIZE GetInitSize();
	void SetInitSize(int cx, int cy);
	RECT& GetSizeBox();
	void SetSizeBox(RECT& rcSizeBox);
	RECT& GetCaptionRect();
	void SetCaptionRect(RECT& rcCaption);
	SIZE GetRoundCorner() const;
	void SetRoundCorner(int cx, int cy);
	SIZE GetMinInfo() const;
	void SetMinInfo(int cx, int cy);
	SIZE GetMaxInfo() const;
	void SetMaxInfo(int cx, int cy);
	bool IsShowUpdateRect() const;
	void SetShowUpdateRect(bool show);
	bool IsNoActivate();
	void SetNoActivate(bool bNoActivate);

	BYTE GetOpacity() const;
	void SetOpacity(BYTE nOpacity);

	int GetShadowSize() const;
	void SetShadowSize(int nSize);
	DWORD GetShadowColor() const;
	void SetShadowColor(DWORD dwColor);
	float GetShadowFocusScales() const;
	void SetShadowFocusScales(float fValue);

	bool IsLayered();
	void SetLayered(bool bLayered);
	//RECT& GetLayeredInset();
	//void SetLayeredInset(RECT& rcLayeredInset);
	RECT& GetNoLayeredPaddingRect();
	void SetNoLayeredPaddingRect(RECT& rcValue);
	bool IsHaveNoLayeredPaddingRect();

	BYTE GetLayeredOpacity();
	void SetLayeredOpacity(BYTE nOpacity);
	LPCWSTR GetLayeredImage();
	void SetLayeredImage(LPCWSTR pstrImage);

	static HINSTANCE GetInstance();
	static CDuiString GetInstancePath();
	static CDuiString GetCurrentPath();
	static CDuiString GetParentDir(LPCWSTR pStrPath);
	static HINSTANCE GetResourceDll();
	static const CDuiString& GetResourcePath();
	static const CDuiString& GetResourceZip();
	static bool IsCachedResourceZip();
	static HANDLE GetResourceZipHandle();
	static void SetInstance(HINSTANCE hInst);
	static void SetCurrentPath(LPCWSTR pStrPath);
	static void SetResourceDll(HINSTANCE hInst);
	static void SetResourcePath(LPCWSTR pStrPath);
	static void SetResourceZip(LPVOID pVoid, unsigned int len);
	static void SetResourceZip(LPCWSTR pstrZip, bool bCachedResourceZip = false);
	static bool GetHSL(short* H, short* S, short* L);
	static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
	static void ReloadSkin();
	static CPaintManagerUI* GetPaintManager(LPCWSTR pstrName);
	static CDuiPtrArray* GetPaintManagers();
	static bool LoadPlugin(LPCWSTR pstrModuleName);
	static CDuiPtrArray* GetPlugins();

	bool IsForceUseSharedRes() const;
	void SetForceUseSharedRes(bool bForce);

	DWORD GetDefaultDisabledColor() const;
	void SetDefaultDisabledColor(DWORD dwColor, bool bShared = false);
	DWORD GetDefaultFontColor() const;
	void SetDefaultFontColor(DWORD dwColor, bool bShared = false);
	DWORD GetDefaultLinkFontColor() const;
	void SetDefaultLinkFontColor(DWORD dwColor, bool bShared = false);
	DWORD GetDefaultLinkHoverFontColor() const;
	void SetDefaultLinkHoverFontColor(DWORD dwColor, bool bShared = false);
	DWORD GetDefaultSelectedBkColor() const;
	void SetDefaultSelectedBkColor(DWORD dwColor, bool bShared = false);

	TFontInfo* GetDefaultFontInfo();
	void SetDefaultFont(LPCWSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bStrikeOut, bool bShared = false);
	DWORD GetCustomFontCount(bool bShared = false) const;
	HFONT AddFont(int id, LPCWSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bStrikeOut, bool bShared = false);
	HFONT GetFont(int id);
	HFONT GetFont(LPCWSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bStrikeOut);
	int GetFontIndex(HFONT hFont, bool bShared = false);
	int GetFontIndex(LPCWSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bStrikeOut, bool bShared = false);
	void RemoveFont(HFONT hFont, bool bShared = false);
	void RemoveFont(int id, bool bShared = false);
	void RemoveAllFonts(bool bShared = false);
	TFontInfo* GetFontInfo(int id);
	TFontInfo* GetFontInfo(HFONT hFont);

	const TImageInfo* GetImage(LPCWSTR bitmap);
	const TImageInfo* GetImageEx(LPCWSTR bitmap, LPCWSTR type = NULL, DWORD mask = 0, bool bUseHSL = false);
	const TImageInfo* AddImage(LPCWSTR bitmap, LPCWSTR type = NULL, DWORD mask = 0, bool bUseHSL = false, bool bShared = false);
	const TImageInfo* AddImage(LPCWSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha, bool bShared = false);
	void RemoveImage(LPCWSTR bitmap, bool bShared = false);
	void RemoveAllImages(bool bShared = false);
	static void ReloadSharedImages();
	void ReloadImages();

	void AddDefaultAttributeList(LPCWSTR pStrControlName, LPCWSTR pStrControlAttrList, bool bShared = false);
	LPCWSTR GetDefaultAttributeList(LPCWSTR pStrControlName) const;
	bool RemoveDefaultAttributeList(LPCWSTR pStrControlName, bool bShared = false);
	void RemoveAllDefaultAttributeList(bool bShared = false);

	void AddWindowCustomAttribute(LPCWSTR pstrName, LPCWSTR pstrAttr);
	LPCWSTR GetWindowCustomAttribute(LPCWSTR pstrName) const;
	bool RemoveWindowCustomAttribute(LPCWSTR pstrName);
	void RemoveAllWindowCustomAttribute();

	CDuiString GetWindowAttribute(LPCWSTR pstrName);
	void SetWindowAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
	CDuiString GetWindowAttributeList(bool bIgnoreDefault = true);
	void SetWindowAttributeList(LPCWSTR pstrList);
	bool RemoveWindowAttribute(LPCWSTR pstrName);

	CDuiString GetWindowXML();

	static void AddMultiLanguageString(int id, LPCWSTR pStrMultiLanguage);
	static LPCWSTR GetMultiLanguageString(int id);
	static bool RemoveMultiLanguageString(int id);
	static void RemoveAllMultiLanguageString();
	static void ProcessMultiLanguageTokens(CDuiString& pStrMultiLanguage);

	bool AttachDialog(CControlUI* pControl);
	bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
	bool RenameControl(CControlUI* pControl, LPCWSTR pstrName);
	void ReapObjects(CControlUI* pControl);

	bool AddOptionGroup(LPCWSTR pStrGroupName, CControlUI* pControl);
	CDuiPtrArray* GetOptionGroup(LPCWSTR pStrGroupName);
	void RemoveOptionGroup(LPCWSTR pStrGroupName, CControlUI* pControl);
	void RemoveAllOptionGroups();

	CControlUI* GetFocus() const;
	void SetFocus(CControlUI* pControl, bool bFocusWnd=true);
	void SetFocusNeeded(CControlUI* pControl);

	bool SetNextTabControl(bool bForward = true);

	bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
	bool KillTimer(CControlUI* pControl, UINT nTimerID);
	void KillTimer(CControlUI* pControl);
	void RemoveAllTimers();

	void SetCapture();
	void ReleaseCapture();
	bool IsCaptured();

	bool IsPainting();
	void SetPainting(bool bIsPainting);

	bool AddNotifier(INotifyUI* pControl);
	bool RemoveNotifier(INotifyUI* pControl);   
	void SendNotify(TNotifyUI& Msg, bool bAsync = false, bool bEnableRepeat = true);
	void SendNotify(CControlUI* pControl, LPCWSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false, bool bEnableRepeat = true);

	bool AddPreMessageFilter(IMessageFilterUI* pFilter);
	bool RemovePreMessageFilter(IMessageFilterUI* pFilter);

	bool AddMessageFilter(IMessageFilterUI* pFilter);
	bool RemoveMessageFilter(IMessageFilterUI* pFilter);

	int GetPostPaintCount() const;
	bool AddPostPaint(CControlUI* pControl);
	bool RemovePostPaint(CControlUI* pControl);
	bool SetPostPaintIndex(CControlUI* pControl, int iIndex);

	int GetNativeWindowCount() const;
	RECT GetNativeWindowRect(HWND hChildWnd);
	bool AddNativeWindow(CControlUI* pControl, HWND hChildWnd);
	bool RemoveNativeWindow(HWND hChildWnd);

	void AddDelayedCleanup(CControlUI* pControl);
	void AddMouseLeaveNeeded(CControlUI* pControl);
	bool RemoveMouseLeaveNeeded(CControlUI* pControl);

	bool AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool TranslateAccelerator(LPMSG pMsg);

	CControlUI* GetRoot() const;
	CControlUI* FindControl(POINT pt) const;
	CControlUI* FindControl(LPCWSTR pstrName) const;
	CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
	CControlUI* FindSubControlByName(CControlUI* pParent, LPCWSTR pstrName) const;
	CControlUI* FindSubControlByClass(CControlUI* pParent, LPCWSTR pstrClass, int iIndex = 0);
	CDuiPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCWSTR pstrClass);

	static int MessageLoop();
	static bool TranslateMessage(const LPMSG pMsg);
	static void Term();

	bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	void UsedVirtualWnd(bool bUsed);

private:
	CDuiPtrArray* GetFoundControls();
	static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlsFromUpdate(CControlUI* pThis, LPVOID pData);

	static void AdjustSharedImagesHSL();
	void AdjustImagesHSL();
	void PostAsyncNotify();

	void PaintShadow();

private:
	CDuiString m_sName;
	HWND m_hWndPaint;
	HDC m_hDcPaint;
	HDC m_hDcOffscreen;
	HDC m_hDcBackground;
	HBITMAP m_hbmpOffscreen;
	COLORREF* m_pOffscreenBits;
	HBITMAP m_hbmpBackground;
	COLORREF* m_pBackgroundBits;
	int m_iTooltipWidth;
	int m_iLastTooltipWidth;
	HWND m_hwndTooltip;
	TOOLINFO m_ToolTip;
	int m_iHoverTime;
	bool m_bNoActivate;
	bool m_bShowUpdateRect;
	//
	CControlUI* m_pRoot;
	CControlUI* m_pFocus;
	CControlUI* m_pEventHover;
	CControlUI* m_pEventClick;
	CControlUI* m_pEventKey;
	CControlUI* m_pLastToolTip;
	//
	POINT m_ptLastMousePos;
	SIZE m_szMinWindow;
	SIZE m_szMaxWindow;
	SIZE m_szInitWindowSize;
	RECT m_rcSizeBox;
	SIZE m_szRoundCorner;
	RECT m_rcCaption;
	UINT m_uTimerID;
	bool m_bFirstLayout;
	bool m_bUpdateNeeded;
	bool m_bFocusNeeded;
	bool m_bOffscreenPaint;

	int m_nShadowSize;
	DWORD m_dwShadowColor;
	float m_fShadowFocusScales;
	bool m_bShadowChanged;

	BYTE m_nOpacity;
	bool m_bLayered;
	//RECT m_rcLayeredInset;
	bool m_bLayeredChanged;
	RECT m_rcLayeredUpdate;
	TDrawInfo m_diLayered;
	RECT m_rcNoLayeredPadding;

	bool m_bMouseTracking;
	bool m_bMouseCapture;
	bool m_bIsPainting;
	bool m_bUsedVirtualWnd;
	bool m_bAsyncNotifyPosted;

	//
	CDuiPtrArray m_aNotifiers;
	CDuiPtrArray m_aTimers;
	CDuiPtrArray m_aPreMessageFilters;
	CDuiPtrArray m_aMessageFilters;
	CDuiPtrArray m_aPostPaintControls;
	CDuiPtrArray m_aNativeWindow;
	CDuiPtrArray m_aNativeWindowControl;
	CDuiPtrArray m_aDelayedCleanup;
	CDuiPtrArray m_aAsyncNotify;
	CDuiPtrArray m_aFoundControls;
	CDuiPtrArray m_aNeedMouseLeaveNeeded;
	CDuiStringPtrMap m_mNameHash;
	CDuiStringPtrMap m_mWindowAttrHash;
	CDuiStringPtrMap m_mOptionGroup;

	//
	bool m_bForceUseSharedRes;
	TResInfo m_ResInfo;

	//
	static HINSTANCE m_hResourceInstance;
	static CDuiString m_sResourcePath;
	static CDuiString m_sResourceZip;
	static HANDLE m_hResourceZip;

	static bool m_bCachedResourceZip;
	static TResInfo m_SharedResInfo;
	static HINSTANCE m_hInstance;
	static bool m_bUseHSL;
	static short m_H;
	static short m_S;
	static short m_L;
	static CDuiPtrArray m_aPreMessages;
	static CDuiPtrArray m_aPlugins;
	
	ULONG_PTR	m_gdiplusToken;
	GdiplusStartupInput		m_gdiplusStartupInput;

public:
	CDuiPtrArray m_aTranslateAccelerator;
};

} // namespace zuilib

#endif // __UIMANAGER_H__
