#pragma once
#include "src/csvreader.h"

class ChartsModel
{
public:
	// make coords
	struct Point
	{
		qreal x;
		qreal y;
		qreal z;
	};
	QVector<Point> _points;

	ChartsModel(const CSVReader::CSVRecords& data);

};

