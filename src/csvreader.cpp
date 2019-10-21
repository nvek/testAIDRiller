#include "csvreader.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

CSVReader::CSVReader(const QString& cvsFileName)
{
	QFile file(cvsFileName);
	if ( !file.open(QFile::ReadOnly | QFile::Text) )
	{
		qDebug() << "File not exists";
	}
	else
	{
		// Создаём поток для извлечения данных из файла
		QTextStream in(&file);
		// пропускаем заголовок
		in.readLine();
		// Считываем данные до конца файла
		while (!in.atEnd())
		{
			QString line = in.readLine();
			auto record = readCSVRow(line);
			_records.push_back(record);
		}
		file.close();
	}
}

const CSVReader::CSVRecords CSVReader::getRecords() const
{
	return _records;
}

CSVReader::CSVRecord CSVReader::readCSVRow(const QString& line)
{
	QStringList list = line.split(";");
	CSVRecord record {
		list[0].toDouble(),
		list[1].toDouble(),
		list[2].toDouble()
	};
	return record;
}
