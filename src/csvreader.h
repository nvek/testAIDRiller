#pragma once

#include <QVector>
#include <QString>
#include <QTextStream>

class CSVReader
{
public:
	// описание структуры CSV файла
	struct CSVRecord
	{
		// глубина по стволу
		double MD;
		// зенитный угол
		double Inc;
		// азимут
		double AZ;
	};
	typedef QVector<CSVRecord> CSVRecords;

	CSVReader(const QString& csvFileName);
	const CSVRecords getRecords() const;

private:
	CSVRecord readCSVRow(const QString& line);

	CSVRecords _records;
};


