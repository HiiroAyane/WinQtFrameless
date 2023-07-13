#pragma once
#include "WinWidget.h"
#include <QStyle>
#include <QPushButton>
#include <QApplication>

/// <summary>
/// 标题栏用例 titlebar sample
/// </summary>
class TitleBar : public QWidget {
	Q_OBJECT;
public:
	TitleBar(QWidget* parent) :QWidget(parent) { 
		setFixedHeight(30);
		setAttribute(Qt::WA_StyledBackground);

		auto layout = new QHBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		
		auto closeBtn = new QPushButton(this);
		closeBtn->setIcon(QIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarCloseButton)));
		closeBtn->setFixedSize(30, 30);
		connect(closeBtn, &QPushButton::clicked, parentWidget(), &QWidget::close);

		layout->addWidget(closeBtn);
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
