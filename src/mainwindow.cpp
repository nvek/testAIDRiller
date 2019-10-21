#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "src/csvreader.h"
#include <qmath.h>
#include "chart.h"
#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include "src/chartsmodel.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CSVReader reader(":/Test Surveys (1).csv");
	ChartsModel model(reader.getRecords());
	auto points = model._points;

	// отрисовываем данные
	QLineSeries *series = new QLineSeries();
	for (int i = 0; i < points.size(); i++)
	{
		QPointF p(points[i].x, points[i].y);
		*series << p;
	}

	Chart *chart = new Chart();
	chart->addSeries(series);
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();
	chart->createDefaultAxes();

	ChartView *chartView = new ChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QLineSeries *series1 = new QLineSeries();
	for (int i = 0; i < points.size(); i++)
	{
		QPointF p(points[i].z, points[i].x);
		*series1 << p;
	}
	Chart *chart1 = new Chart();
	chart1->addSeries(series1);
	chart1->setAnimationOptions(QChart::SeriesAnimations);
	chart1->legend()->hide();
	chart1->createDefaultAxes();
	ChartView *chartView1 = new ChartView(chart1);
	chartView1->setRenderHint(QPainter::Antialiasing);

	QVBoxLayout* l = new QVBoxLayout();
	l->addWidget(chartView);
	l->addWidget(chartView1);
	QWidget* w = new QWidget;
	w->setLayout(l);
	setCentralWidget(w);



	resize(400, 300);
	grabGesture(Qt::PanGesture);
	grabGesture(Qt::PinchGesture);
}

MainWindow::~MainWindow()
{
	delete ui;
}
