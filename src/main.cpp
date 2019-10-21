#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>
#include "src/csvreader.h"
#include "src/mainwindow.h"
#include "src/chartsmodel.h"

int main(int argc, char *argv[])
{
	// Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
	QApplication app(argc, argv);

//	QQuickView viewer;

	//DataSource dataSource(&viewer, reader.getRecords());
//	QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

//	viewer.setTitle(QStringLiteral("QML Oscilloscope"));

//	viewer.engine()->addImportPath("qrc:/qml/qml");

//	viewer.rootContext()->setContextProperty("dataSource", &dataSource);

//	viewer.setSource(QUrl("qrc:/qml/qml/main.qml"));
//	viewer.setResizeMode(QQuickView::SizeRootObjectToView);
//	viewer.setColor(QColor("#404040"));
//	viewer.show();
	MainWindow window;
	window.show();

	return app.exec();
}
