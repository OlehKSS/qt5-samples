#include "SysInfoWidget.h"

#include <QLayout>

SysInfoWidget::SysInfoWidget(QWidget *parent,
    int startDelayMs, int updateSeriesDelayMs)
    : QWidget(parent)
    , mChartView(this)
{
    mRefreshTimer.setInterval(updateSeriesDelayMs);
    connect(&mRefreshTimer, &QTimer::timeout,
        this, &SysInfoWidget::updateSeries);
    QTimer::singleShot(startDelayMs,
        [this] { mRefreshTimer.start(); });

    mChartView.setRenderHint(QPainter::Antialiasing);
    mChartView.chart()->legend()->setVisible(false);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(&mChartView);
    setLayout(layout);
}

QtCharts::QChartView& SysInfoWidget::chartView()
{
    return mChartView;
}
