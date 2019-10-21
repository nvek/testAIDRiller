#include "chartsmodel.h"
#include <QtMath>
#include <QVector>
#include <QDebug>

ChartsModel::ChartsModel(const CSVReader::CSVRecords& data)
{
	_points.resize(data.size());
	// первая координата нулевая
	_points[0] = {0, 0, 0};
	for(int i = 1; i < data.size(); i++)
	{
		auto toRadian = [](qreal c) -> qreal
		{
			return (c * 180) / M_PI;
		};

		// радианы
		qreal incPrev = toRadian(data[i - 1].Inc);
		qreal azPrev =	toRadian(data[i - 1].AZ);
		qreal inc =		toRadian(data[i].Inc);
		qreal az =		toRadian(data[i].AZ);

		qreal D = qAcos(qSin(incPrev) * qSin(azPrev) * qSin(inc) * qSin(az) +
						qSin(incPrev) * qCos(azPrev) * qSin(inc) * qCos(az) +
						qCos(incPrev) * qCos(inc));

		qreal T = (100 * qTan(D/2))/(D);

		_points[i].y = _points[i - 1].y + T * ( qSin(incPrev) * qSin(azPrev) + qSin(inc) * qSin(az) );

		_points[i].x = _points[i - 1].x + T * ( qSin(incPrev) * qCos(azPrev) + qSin(inc) * qCos(az) );

		_points[i].z = _points[i - 1].z + T * ( qCos(incPrev) + qCos(inc) );
	}
}


