#include "WinWidget.h"
#include <QApplication>

WinWindow::WinWindow(QWidget* parent) : WinQt<QWidget>(parent)
{
}

WinWindow::~WinWindow() {
}

bool WinWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* pMsg = reinterpret_cast<MSG*>(message);

	switch (pMsg->message) {
	case WM_SIZE:
	{
		WINDOWPLACEMENT wp = { 0 };
		wp.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(pMsg->hwnd, &wp);
		if (wp.showCmd != SW_MAXIMIZE && wp.showCmd != SW_SHOWNORMAL) {
			break;
		}

		bool isMax = false;
		if (wp.showCmd == SW_MAXIMIZE) {
			// 最大化时避免内容超出显示器
			// Windows的某种Future 带边框的原生窗口最大化也会标题栏变窄
			// 暂无完美的解决办法 也可以注释掉不解决
			if (devicePixelRatio() == 1) m_outOfScreen = 8; // 数值根据缩放倍率需要微调，此为缩放100%， 125%的值
			else if (devicePixelRatio() == 2) {
				m_outOfScreen = 5; // 此为150%，175%的值
			}
			isMax = true;
		}
		else if (wp.showCmd == SW_SHOWNORMAL) {
			m_outOfScreen = 0;
		}
		setContentsMargins(m_outOfScreen, m_outOfScreen, m_outOfScreen, m_outOfScreen);
		repaint();
		emit signalNativeMaximized(isMax);
		break;
	}
	}

	return __super::nativeEvent(eventType, message, result);
}

WinDialog::WinDialog(QWidget* parent) :WinQt<QDialog>(parent)
{
}

WinDialog::~WinDialog()
{
}
