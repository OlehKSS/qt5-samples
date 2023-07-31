#include "SysInfoMainWindow.h"

#include <QLayout>

#include "SysInfo.h"

SysInfoMainWindow::SysInfoMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mCpuWidget(this)
    , mMemoryWidget(this)
{
    ui.setupUi(this);
    SysInfo::instance().init();
    ui.centralWidget->layout()->addWidget(&mCpuWidget);
    ui.centralWidget->layout()->addWidget(&mMemoryWidget);
}
