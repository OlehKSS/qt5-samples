#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sysinfo.h"

//#include <QLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this),
    mMemoryWidget(this)
{
    ui->setupUi(this);
    SysInfo::instance().init();
    if (!ui->centralwidget->layout())
    {
        qDebug() << "Add new layout first!!!";
    }
    else
    {
        // force editor to add a default layout by adding a dummy elements
        // onto your main window canvas
        qDebug() << "Layout was added!!!";
    }


    ui->centralwidget->layout()->addWidget(&mCpuWidget);
    ui->centralwidget->layout()->addWidget(&mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

