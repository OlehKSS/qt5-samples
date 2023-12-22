#include "MandelbrotCalculator.h"

#include <QDebug>
#include <QThreadPool>

#include "Job.h"

MandelbrotCalculator::MandelbrotCalculator(QObject* parent)
	: QObject(parent)
{

}

void MandelbrotCalculator::generatePicture(QSize areaSize, QPointF moveOffset,
	double scaleFactor, int iterationMax)
{
	if (areaSize.isEmpty())
	{
		return;
	}

	mTimer.start();
	clearJobs();

	mAreaSize = areaSize;
	mMoveOffset = moveOffset;
	mScaleFactor = scaleFactor;
	mIterationMax = iterationMax;

	for(int pixelPositionY = 0; pixelPositionY < mAreaSize.height(); ++pixelPositionY)
	{
		QThreadPool::globalInstance()->start(createJob(pixelPositionY));
	}
}

Job* MandelbrotCalculator::createJob(int pixelPositionY)
{
	auto job = new Job();

	job->setPixelPositionY(pixelPositionY);
	job->setMoveOffset(mMoveOffset);
	job->setScaleFactor(mScaleFactor);
	job->setAreaSize(mAreaSize);
	job->setIterationMax(mIterationMax);

	connect(this, &MandelbrotCalculator::abortAllJobs,
		job, &Job::abort);
	connect(job, &Job::jobCompleted, this, &MandelbrotCalculator::process);

	return job;
}

void MandelbrotCalculator::clearJobs()
{
	mReceivedJobResults = 0;
	emit abortAllJobs();
	QThreadPool::globalInstance()->clear();
}

void MandelbrotCalculator::process(JobResult jobResult)
{
	if (jobResult.areaSize != mAreaSize ||
		jobResult.moveOffset != mMoveOffset ||
		jobResult.scaleFactor != mScaleFactor)
	{
		return;
	}

	++mReceivedJobResults;
	mJobResults.append(jobResult);

	if (mJobResults.size() >= JOB_RESULT_THRESHOLD ||
		mReceivedJobResults == mAreaSize.height())
	{
		emit pictureLinesGenerated(mJobResults);
		mJobResults.clear();
	}

	if (mReceivedJobResults == mAreaSize.height())
	{
		qDebug() << "Generate in " << mTimer.elapsed() << " ms";
	}
}
