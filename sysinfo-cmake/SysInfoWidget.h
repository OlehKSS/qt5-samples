#pragma once

#include <QWidget>
#include <QTimer>
#include <QtCharts/QChartView>

class SysInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SysInfoWidget(QWidget *parent = nullptr,
        int startDelayMs = 500,
        int updateSeriesDelayMs = 500);
    virtual ~SysInfoWidget() = default;

protected:
    QtCharts::QChartView& chartView();

protected slots:
    virtual void updateSeries() = 0;

private:
    QTimer mRefreshTimer;
    QtCharts::QChartView mChartView;
};
