#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>


QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQuickView *appViewer, CSVReader::CSVRecords data, QObject *parent) :
	QObject(parent),
	m_appViewer(appViewer),
	m_index(-1)
{
	qRegisterMetaType<QAbstractSeries*>();
	qRegisterMetaType<QAbstractAxis*>();

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



	generateData(0, 5, 1024);
}

void DataSource::update(QAbstractSeries *series)
{
	if (series) {
		QXYSeries *xySeries = static_cast<QXYSeries *>(series);
		m_index++;
		if (m_index > m_data.count() - 1)
			m_index = 0;

		QVector<QPointF> points = m_data.at(m_index);
		// Use replace instead of clear + append, it's optimized for performance
		xySeries->replace(points);
	}
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
	// Remove previous data
	m_data.clear();

	// Append the new data depending on the type
	for (int i(0); i < rowCount; i++) {
		QVector<QPointF> points;
		points.reserve(colCount);
		for (int j(0); j < colCount; j++) {
			qreal x(0);
			qreal y(0);
			switch (type) {
			case 0:
				// data with sin + random component
				y = qSin(M_PI / 50 * j) + 0.5 + QRandomGenerator::global()->generateDouble();
				x = j;
				break;
			case 1:
				// linear data
				x = j;
				y = (qreal) i / 10;
				break;
			default:
				// unknown, do nothing
				break;
			}
			points.append(QPointF(x, y));
		}
		m_data.append(points);
	}
}