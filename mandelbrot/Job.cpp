#include "Job.h"

Job::Job(QObject* parent)
	: QObject(parent)
{

}

void Job::run()
{
	JobResult jobResult(mAreaSize.width());
	jobResult.areaSize = mAreaSize;
	jobResult.pixelPositionY = mPixelPositionY;
	jobResult.moveOffset = mMoveOffset;
	jobResult.scaleFactor = mScaleFactor;

	auto imageHalfWidth = mAreaSize.width() / 2.0;
	auto imageHalfHeight = mAreaSize.height() / 2.0;

	for (auto imageX = 0; imageX < mAreaSize.width(); ++imageX)
	{
		auto iteration = 0;
		double x = 0.0;
		double y = 0.0;
		double x0 = (imageX - imageHalfWidth) * mScaleFactor + mMoveOffset.x();
		double y0 = (mPixelPositionY - imageHalfHeight) * mScaleFactor - mMoveOffset.y();

		do
		{
			if (mAbort.load())
			{
				return;
			}

			double nextX = (x * x) - (y * y) + x0;
			y = 2.0 * x * y + y0;
			x = nextX;
			++iteration;
		} while (iteration < mIterationMax && (x * x + y * y) < 4.0);

		jobResult.values[imageX] = iteration;
	}

	emit jobCompleted(jobResult);
}

void Job::abort()
{
	mAbort.store(true);
}