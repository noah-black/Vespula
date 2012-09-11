#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QtConcurrentRun>
#include <QSpinBox>
#include "synthesizer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Synthesizer synth;
	QFuture<void> future = QtConcurrent::run(&synth, &Synthesizer::start);
	QComboBox comboBox(&synth);
	comboBox.addItem("Sawtooth");
	comboBox.addItem("Triangle");
	comboBox.addItem("Square");
	comboBox.addItem("Sine");
	comboBox.show();
	QSpinBox spinBox(&synth);
	spinBox.setRange(-12, 12);
	spinBox.setSingleStep(1);
	synth.show();
	synth.setFocus();
	QObject::connect(&app, SIGNAL(lastWindowClosed()), &synth, SLOT(done()));
	QObject::connect(&comboBox, SIGNAL(activated(int)), &synth, SLOT(changeWaveform(int)));
	QObject::connect(&comboBox, SIGNAL(activated(int)), &synth, SLOT(setFocus()));
	QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &synth, SLOT(setTranspose(int)));
	QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));
	app.exec();
	return 0;
}
