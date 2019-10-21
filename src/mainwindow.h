#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	struct Point
	{
		double x;
		double y;
		double z;
	};
	// массив точек из которых построю графики
	typedef QVector<Point> Points;

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private:
	Ui::MainWindow *ui;
	Points _points;
};

#endif // MAINWINDOW_H
