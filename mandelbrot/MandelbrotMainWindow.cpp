#include "MandelbrotMainWindow.h"
#include "ui_MandelbrotMainWindow.h"

MandelbrotMainWindow::MandelbrotMainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MandelbrotMainWindow())
{
	ui->setupUi(this);
}

MandelbrotMainWindow::~MandelbrotMainWindow()
{
	delete ui;
}