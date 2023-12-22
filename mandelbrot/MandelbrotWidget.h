#pragma once

#include <memory>

#include <QList>
#include <QPoint>
#include <QThread>
#include <QWidget>

#include "MandelbrotCalculator.h"

class QResizeEvent;

class MandelbrotWidget : public QWidget
{
	Q_OBJECT

	static constexpr auto ITERATION_MAX = 4000;
	static constexpr double DEFAULT_SCALE = 0.005;
	static constexpr double DEFAULT_OFFSET_X = -0.74364390249094747;
	static constexpr double DEFAULT_OFFSET_Y = 0.13182589977450967;

	MandelbrotCalculator mMandelbrotCalculator;
	QThread mThreadCalculator;
	double mScaleFactor = DEFAULT_SCALE;
	QPoint mLastMouseMovePosition;
	QPointF mMoveOffset{ DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y };
	QSize mAreaSize;
	int mIterationMax = ITERATION_MAX;
	std::unique_ptr<QImage> mImage;

public:
	explicit MandelbrotWidget(QWidget* parent = nullptr);
	~MandelbrotWidget();

signals:
	void requestPicture(QSize areaSize, QPointF moveOffset,
		double scaleFactor, int iterationMax);

public slots:
	void processJobResults(QList<JobResult> jobResults);

protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	QRgb generateColorFromIteration(int iteration);
};