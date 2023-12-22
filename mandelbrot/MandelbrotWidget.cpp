#include "MandelbrotWidget.h"

#include <QResizeEvent>
#include <QImage>
#include <QPainter>
#include <QtMath>

MandelbrotWidget::MandelbrotWidget(QWidget* parent)
	: QWidget(parent)
	, mThreadCalculator(this)
{
	mMandelbrotCalculator.moveToThread(&mThreadCalculator);

	connect(this, &MandelbrotWidget::requestPicture,
		&mMandelbrotCalculator, &MandelbrotCalculator::generatePicture);
	connect(&mMandelbrotCalculator, &MandelbrotCalculator::pictureLinesGenerated,
		this, &MandelbrotWidget::processJobResults);

	mThreadCalculator.start();
}

MandelbrotWidget::~MandelbrotWidget()
{
	mThreadCalculator.quit();
	mThreadCalculator.wait(1000);

	if (!mThreadCalculator.isFinished())
	{
		mThreadCalculator.terminate();
	}
}

void MandelbrotWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.save();

	auto imageRect = event->region().boundingRect();
	painter.drawImage(imageRect, *mImage, imageRect);

	painter.setPen(Qt::white);
	painter.drawText(10, 20, QString("Size: %1 x %2")
		.arg(mImage->width()).arg(mImage->height()));
	painter.drawText(10, 35, QString("Offset: %1 x %2")
		.arg(mMoveOffset.x()).arg(mMoveOffset.y()));
	painter.drawText(10, 50, QString("Scale: %1")
		.arg(mScaleFactor));
	painter.drawText(10, 65, QString("Max iteration: %1")
		.arg(ITERATION_MAX));

	painter.restore();
}

void MandelbrotWidget::resizeEvent(QResizeEvent* event)
{
	mAreaSize = event->size();

	mImage = std::make_unique<QImage>(mAreaSize, QImage::Format_RGB32);
	mImage->fill(Qt::black);

	emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
}

void MandelbrotWidget::wheelEvent(QWheelEvent* event)
{
	auto delta = event->delta();
	mScaleFactor *= qPow(0.75, delta / 120.0);
	emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
}

void MandelbrotWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		mLastMouseMovePosition = event->pos();
	}
}

void MandelbrotWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		QPointF offset = mLastMouseMovePosition - event->pos();

		if (QPointF::dotProduct(offset, offset) > 50)
		{
			mLastMouseMovePosition = event->pos();
			// We invert a y-axis value because the mouse event is in a top-left referential,
			// whereas the Mandelbrot algorithm relies on a bottom-left referential.
			offset.setY(-offset.y());
			mMoveOffset += offset * mScaleFactor;
			emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
		}
	}
}

void MandelbrotWidget::processJobResults(QList<JobResult> jobResults)
{
	auto yMin = height();
	auto yMax = 0;

	for (auto& jobResult : jobResults)
	{
		if (mImage->size() != jobResult.areaSize)
		{
			continue;
		}

		auto y = jobResult.pixelPositionY;
		auto scanLine = reinterpret_cast<QRgb*>(mImage->scanLine(y));

		for (auto x = 0; x < mAreaSize.width(); ++x)
		{
			scanLine[x] = generateColorFromIteration(jobResult.values[x]);
		}

		if (y < yMin)
		{
			yMin = y;
		}

		if (y > yMax)
		{
			yMax = y;
		}
	}

	// Repaint only the updated region
	repaint(0, yMin, width(), yMax);
}

QRgb MandelbrotWidget::generateColorFromIteration(int iteration)
{
	if (iteration == mIterationMax)
	{
		return qRgb(50, 50, 255);
	}

	return qRgb(0, 0, (255.0 * iteration / mIterationMax));
}