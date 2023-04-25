#pragma once
#include "WinWidget.h"
#include <QPushButton>

/// <summary>
/// 标题栏用例 titlebar sample
/// </summary>
class TitleBar : public QWidget {
	Q_OBJECT;
public:
	TitleBar(QWidget* parent) :QWidget(parent) { 
		setFixedHeight(30);

		auto layout = new QHBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		
		auto closeBtn = new QPushButton(this);
		closeBtn->setIcon(QIcon(":/QtWidgets/close.png"));
		closeBtn->setFixedSize(30, 30);
		connect(closeBtn, &QPushButton::clicked, parentWidget(), &QWidget::close);

		layout->addWidget(closeBtn);
	}
protected:
	void paintEvent(QPaintEvent* e) override {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}
};

/// <summary>
/// 主窗口用例 main window sample
/// </summary>
class QtWidgets : public WinWindow
{
	Q_OBJECT;
public:
	QtWidgets(QWidget *parent = nullptr);
protected:
	void mouseDoubleClickEvent(QMouseEvent* e) override;
private:
};
