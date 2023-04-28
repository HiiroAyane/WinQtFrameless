#include "WinEvtProcess.h"
#include <QApplication>

#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

const LRESULT hitAction[3][3] =
{
	{ HTTOPLEFT,    HTTOP,         HTTOPRIGHT },
	{ HTLEFT,       HTNOWHERE,     HTRIGHT },
	{ HTBOTTOMLEFT, HTBOTTOM,      HTBOTTOMRIGHT },
};

bool nativeEvtProcess_WM_NCCALCSIZE(long* result)
{
	// 去除边框 frameless
	*result = 0;
	return true;
}

bool nativeEvtProcess_WM_ACTIVATE(MSG* pMsg, long* result)
{
	// 阴影 shadow
	MARGINS margins = { -1 };
	HRESULT hr = DwmExtendFrameIntoClientArea(pMsg->hwnd, &margins);
	*result = hr;

	return true;
}

bool nativeEvtProcess_WM_NCHITTEST(MSG* pMsg, QWidget* titleBar, long* result, bool wFixed, bool hFixed, int outOfScreen)
{
	// 模糊边界宽度
	int bound = 5;
	// 标题栏高度
	int titleBarHeight = 30;
	if (titleBar) titleBarHeight = titleBar->height();

	// 鼠标点击的坐标
	POINT ptMouse = { GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam) };
	// 窗口矩形
	RECT rcWindow;
	GetWindowRect(pMsg->hwnd, &rcWindow);

	// 动作
	USHORT uRow = 1;
	USHORT uCol = 1;

	// 检测是不是在标题栏上
	if (ptMouse.x >= rcWindow.left + bound && ptMouse.x <= rcWindow.right - bound && ptMouse.y > rcWindow.top + bound && ptMouse.y <= rcWindow.top + titleBarHeight + outOfScreen)
	{
		// 检测是否落在标题栏本身，而不是其子部件上
		QWidget* w = QApplication::widgetAt(QCursor::pos());
		if (titleBar && w != titleBar)
			return false;

		*result = HTCAPTION;
		return true;
	}
	// 确认鼠标指针是否在top或者bottom
	if (!hFixed) {
		if (ptMouse.y >= rcWindow.top - bound && ptMouse.y < rcWindow.top + bound)
		{
			uRow = 0;
		}
		else if (ptMouse.y < rcWindow.bottom + bound && ptMouse.y >= rcWindow.bottom - bound)
		{
			uRow = 2;
		}
	}

	// 确认鼠标指针是否在left或者right
	if (!wFixed) {
		if (ptMouse.x >= rcWindow.left - bound && ptMouse.x < rcWindow.left + bound)
		{
			uCol = 0;
		}
		else if (ptMouse.x < rcWindow.right + bound && ptMouse.x >= rcWindow.right - bound)
		{
			uCol = 2;
		}
	}

	if (uRow == 1 && uCol == 1) return false;
	*result = hitAction[uRow][uCol];
	return true;
}

void nativeEvtProcess_WM_MOVE(HWND hWnd, int width, int height)
{
	RECT rcClient;
	GetWindowRect(hWnd, &rcClient);
	SetWindowPos(hWnd, NULL, rcClient.left, rcClient.top, width, height, SWP_FRAMECHANGED);
}