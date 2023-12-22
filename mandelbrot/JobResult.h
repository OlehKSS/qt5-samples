#pragma once
#include <QSize>
#include <QVector>
#include <QPointF>

struct JobResult
{
	JobResult(int valueCount = 1)
		: values(valueCount)
	{

	}

	QSize areaSize{ 0, 0 };
	int pixelPositionY = 0;
	QPointF moveOffset{ 0, 0 };
	double scaleFactor = 0;

	QVector<int> values;
};