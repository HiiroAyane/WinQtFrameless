#pragma once
#include "WinQt.h"
#include <QDialog>

/// <summary>
/// 主窗口基类 main window base class
/// 实例化模板从而能使用Q_OBJECT instantiate to use Q_OBJECT
/// </summary>
class WinWindow : public WinQt<QWidget> {
	Q_OBJECT;
signals:
	void signalNativeMaximized(bool isMax);
public:
	explicit WinWindow(QWidget* parent = nullptr);
	virtual ~WinWindow();
protected:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
};

/// <summary>
/// 对话框基类 dialog base class
/// 实例化模板从而能使用Q_OBJECT instantiate to use Q_OBJECT
/// </summary>
class WinDialog : public WinQt<QDialog> {
	Q_OBJECT;
public:
	explicit WinDialog(QWidget* parent = nullptr);
	virtual ~WinDialog();
};
