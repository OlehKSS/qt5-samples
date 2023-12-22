#pragma once

#include <QMainWindow>

namespace Ui
{
	class MandelbrotMainWindow;
}

class MandelbrotMainWindow : public QMainWindow
{
	Q_OBJECT

	Ui::MandelbrotMainWindow* ui;

public:
	MandelbrotMainWindow(QWidget* parent = nullptr);
	~MandelbrotMainWindow();
};