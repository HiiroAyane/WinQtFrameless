#pragma once
#include "WinEvtProcess.h"
#include <QStyleOption>
#include <QPainter>
#include <QLayout>

template <typename T>
class WinQt : public T {
public:
	explicit WinQt(QWidget* parent = nullptr) {
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

protected:
	void paintEvent(QPaintEvent* e) override {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		return style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override {
		MSG* pMsg = reinterpret_cast<MSG*>(message);

		switch (pMsg->message) {
		case WM_NCCALCSIZE:
			return nativeEvtProcess_WM_NCCALCSIZE(result);
		case WM_ACTIVATE:
			return nativeEvtProcess_WM_ACTIVATE(pMsg, result);
		case WM_NCHITTEST:
			return nativeEvtProcess_WM_NCHITTEST(pMsg, m_titleBar, result, m_outOfScreen);
		case WM_MOVE:
			if (m_firstShow) {
				nativeEvtProcess_WM_MOVE(pMsg->hwnd, width(), height());
				m_firstShow = false;
			}
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
};