#pragma once
#include "WinEvtProcess.h"
#include <QStyleOption>
#include <QPainter>
#include <QLayout>

template <typename T>
class WinQt : public T {
public:
	explicit WinQt(QWidget* parent = nullptr):T(parent) {
		setAttribute(Qt::WA_StyledBackground);
		m_vLayout = new QVBoxLayout(this);
		m_vLayout->setContentsMargins(0, 0, 0, 0);
		m_vLayout->setSpacing(0);
	}
	virtual ~WinQt() {}

	void setTitleWidget(QWidget* titleBar) {
		m_titleBar = titleBar;
		m_vLayout->addWidget(titleBar, 0, Qt::AlignTop);
	}
	void resize(int w, int h) {
		__super::resize(w, h);
		nativeEvtProcess_WM_MOVE((HWND)winId(), width(), height());
	}
	void resize(const QSize& size) {
		return resize(size.width(), size.height());
	}
	void setFixedSize(const QSize& size) {
		m_wFixed = true;
		m_hFixed = true;
		return __super::setFixedsize(size);
	}
	void setFixedSize(int w, int h) {
		m_wFixed = true;
		m_hFixed = true;
		return __super::setFixedsize(w, h);
	}
	void setFixedWidth(int w) {
		m_wFixed = true;
		return __super::setFixedWidth(w);
	}
	void setFixedHeight(int h) {
		m_hFixed = true;
		return __super::setFixedHeight(h);
	}
protected:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override {
		MSG* pMsg = reinterpret_cast<MSG*>(message);

		switch (pMsg->message) {
		case WM_NCCALCSIZE:
			return nativeEvtProcess_WM_NCCALCSIZE(result);
		case WM_ACTIVATE:
			return nativeEvtProcess_WM_ACTIVATE(pMsg, result);
		case WM_NCHITTEST:
			return nativeEvtProcess_WM_NCHITTEST(pMsg, m_titleBar, result, m_wFixed, m_hFixed, m_outOfScreen);
		case WM_MOVE:
			// 多显示器窗口创建时避免尺寸错误
			if (m_firstShow) {
				QMetaObject::invokeMethod(this, [this] { nativeEvtProcess_WM_MOVE((HWND)winId(), width(), height()); m_firstShow = false; }, Qt::QueuedConnection);
			}
			break;
		case WM_MOVING:
			// 多显示器间移动时避免尺寸错误
			nativeEvtProcess_WM_MOVE(pMsg->hwnd, width(), height());
			break;
		}

		return false;
	}
protected:
	QVBoxLayout* m_vLayout = nullptr;
	QWidget*     m_titleBar = nullptr;
	int          m_outOfScreen = 0;
private:
	bool         m_firstShow = true;
	bool         m_wFixed = false;
	bool         m_hFixed = false;
};