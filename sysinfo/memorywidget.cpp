#include "memorywidget.h"

#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

#include <sysinfo.h>

const int CHART_X_RANGE_COUNT = 50;
const int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
const int COLOR_DARK_BLUE = 0x209fdf;
const int COLOR_LIGHT_BLUE = 0xbfdfef;
const int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget* parent) :
    SysInfoWidget(parent),
    mSeries(new QtCharts::QLineSeries(this)),
    mPointPositionX(0)
{
    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    QtCharts::QAreaSeries* areaSeries = new QtCharts::QAreaSeries(mSeries);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);

    QtCharts::QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory used");
    chart->createDefaultAxes();

    auto xAxis = chart->axes(Qt::Horizontal)[0],
         yAxis = chart->axes(Qt::Vertical)[0];

    xAxis->setVisible(false);
    yAxis->setRange(0, CHART_X_RANGE_MAX);
    yAxis->setRange(0, 100);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = SysInfo::instance().memoryUsed();
    // add new point with memory information
    mSeries->append(mPointPositionX++, memoryUsed);
    // remove old points if we have more than enough
    if (mSeries->count() > CHART_X_RANGE_COUNT)
    {
        QtCharts::QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX, 0);
        mSeries->remove(0);
    }
}
