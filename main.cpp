#include "QtSampleWidgets.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	// 支持高DPI缩放 support high dpi scale
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	// 避免Native子部件抢夺主窗口事件（QOpenGL、嵌入其他绘图引擎等） avoid main window event loss
	QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
	QApplication a(argc, argv);

	// 全局样式 global stylesheet
	{
		QFile f(":/QtWidgets/QtWidget.qss");
		f.open(QIODevice::ReadOnly);
		a.setStyleSheet(f.readAll());
		f.close();
	}

	// 全局字体 global font
	{
		QFont ft("Microsoft YaHei UI");
		a.setFont(ft);
	}

	QtWidgets w;
	w.show();
	return a.exec();
}
