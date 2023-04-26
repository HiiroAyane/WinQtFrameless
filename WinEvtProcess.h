#pragma once
#include <Windows.h>
#include <QWidget>

bool nativeEvtProcess_WM_NCCALCSIZE(long* result);

bool nativeEvtProcess_WM_ACTIVATE(MSG* pMsg, long* result);

bool nativeEvtProcess_WM_NCHITTEST(MSG* pMsg, QWidget* titleBar, long* result, bool wFixed, bool hFixed, int outOfScreen = 0);

void nativeEvtProcess_WM_MOVE(HWND hWnd, int width, int height);