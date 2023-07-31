#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SysInfoMain.h"
#include "CpuWidget.h"
#include "MemoryWidget.h"

class SysInfoMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SysInfoMainWindow(QWidget *parent = nullptr);
    ~SysInfoMainWindow() = default;

private:
    Ui::SysInfoMain ui;
    CpuWidget mCpuWidget;
    MemoryWidget mMemoryWidget;
};
