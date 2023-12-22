#pragma once

#include <QObject>
#include <QSize>
#include <QPointF>
#include <QElapsedTimer>
#include <QList>

#include "JobResult.h"

class Job;

class MandelbrotCalculator : public QObject
{
	Q_OBJECT

	static constexpr auto JOB_RESULT_THRESHOLD = 10;

	QPointF mMoveOffset{ 0.0, 0.0 };
	double mScaleFactor = 0.005;
	QSize mAreaSize{ 0, 0 };
	int mIterationMax = 10;
	int mReceivedJobResults = 0;
	QList<JobResult> mJobResults;
	QElapsedTimer mTimer;

public:
	explicit MandelbrotCalculator(QObject* parent = nullptr);

signals:
	void pictureLinesGenerated(QList<JobResult> jobResults);
	void abortAllJobs();

public slots:
	void generatePicture(QSize areaSize, QPointF moveOffset,
		double scaleFactor, int iterationMax);
	void process(JobResult jobResult);

private:
	Job* createJob(int pixelPositionY);
	void clearJobs();
};
