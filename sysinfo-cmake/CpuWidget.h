#pragma once

#include "SysInfoWidget.h"
#include <QtCharts/QPieSeries>

class CpuWidget : public SysInfoWidget
{
	// This macro is needed again because we overrode updateSeries() 
	Q_OBJECT

public:
	explicit CpuWidget(QWidget* parent = nullptr);

protected slots:
	void updateSeries() override;

private:
	QtCharts::QPieSeries* mSeries;
};