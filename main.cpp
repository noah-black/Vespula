#include <QApplication>
#include "synthesizer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyleSheet("QGroupBox { border: 1px solid black }");
	Synthesizer synth;
	QObject::connect(&app, SIGNAL(lastWindowClosed()), &synth, SLOT(done()));
	QFuture<void> future = QtConcurrent::run(&synth, &Synthesizer::start);
	app.exec();
	return 0;
}
