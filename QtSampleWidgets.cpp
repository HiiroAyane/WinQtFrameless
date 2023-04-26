#include "QtSampleWidgets.h"

QtWidgets::QtWidgets(QWidget* parent)
    :WinWindow(parent)
{
    TitleBar* t = new TitleBar(this);
    setTitleWidget(t);

    resize(1000, 500);
    resize(800, 600);
}

void QtWidgets::mouseDoubleClickEvent(QMouseEvent* e)
{
    /// <summary>
    /// 对话框用例 dialog sample
    /// </summary>
    auto d = new WinDialog(this);
    TitleBar* t = new TitleBar(d);
    d->setTitleWidget(t);
    d->resize(400, 300);

    d->exec();  // 模态测试  model dialog test
    d->show();// 非模态测试 modeless dialog test
}
