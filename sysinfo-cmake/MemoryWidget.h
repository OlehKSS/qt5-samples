#pragma once

#include "SysInfoWidget.h"

#include <QtCharts/QLineSeries>

class MemoryWidget : public SysInfoWidget
{
	Q_OBJECT

public:
	explicit MemoryWidget(QWidget* parent = nullptr);

protected slots:
	void updateSeries() override;

private:
	QtCharts::QLineSeries* mSeries;
	qint64 mPointPositionX = 0;

	static constexpr auto CHART_X_RANGE_COUNT = 50;
	static constexpr auto COLOR_DARK_BLUE = 0x209fdf;
	static constexpr auto COLOR_LIGHT_BLUE = 0xbfdfef;
	static constexpr auto PEN_WIDTH = 3;
	static constexpr auto CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
};
