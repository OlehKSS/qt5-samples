#pragma once
#include <QObject>
#include <QRunnable>
#include <QPointF>
#include <QSize>
#include <QAtomicInteger>

#include "JobResult.h"

class Job : public QObject, public QRunnable
{
	Q_OBJECT

public:
	Job(QObject* parent = nullptr);
	void run() override;

	void setPixelPositionY(int value)
	{
		mPixelPositionY = value;
	}

	void setMoveOffset(const QPointF& value)
	{
		mMoveOffset = value;
	}

	void setScaleFactor(double value)
	{
		mScaleFactor = value;
	}

	void setAreaSize(const QSize& value)
	{
		mAreaSize = value;
	}

	void setIterationMax(int value)
	{
		mIterationMax = value;
	}

signals:
	void jobCompleted(JobResult jobResult);

public slots:
	void abort();

private:
	QAtomicInteger<bool> mAbort{ false };
	int mPixelPositionY = 0;
	QPointF mMoveOffset{ 0, 0 };
	double mScaleFactor = 0;
	QSize mAreaSize{ 0, 0 };
	int mIterationMax = 1;
};
