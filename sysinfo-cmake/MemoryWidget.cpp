#include "MemoryWidget.h"

#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

#include "SysInfo.h"

MemoryWidget::MemoryWidget(QWidget* parent)
	: SysInfoWidget(parent)
	, mSeries(new QtCharts::QLineSeries(this))
{
	QPen pen(COLOR_DARK_BLUE);
	pen.setWidth(PEN_WIDTH);

	QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
	gradient.setColorAt(1.0, COLOR_DARK_BLUE);
	gradient.setColorAt(0, COLOR_LIGHT_BLUE);
	gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

	auto areaSeries = new QtCharts::QAreaSeries(mSeries);
	areaSeries->setPen(pen);
	areaSeries->setBrush(gradient);

	auto chart = chartView().chart();
	chart->addSeries(areaSeries);
	chart->setTitle("Memory Used");
	chart->createDefaultAxes();
	chart->axisX()->setVisible(false);
	chart->axisX()->setRange(0, CHART_X_RANGE_MAX);
	chart->axisY()->setRange(0, 100);
}

void MemoryWidget::updateSeries()
{
	auto memoryUsed = SysInfo::instance().memoryUsed();
	mSeries->append(mPointPositionX, memoryUsed);
	++mPointPositionX;

	if (mSeries->count() > CHART_X_RANGE_COUNT)
	{
		auto chart = chartView().chart();
		chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX, 0);
		mSeries->remove(0);
	}
}