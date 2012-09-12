#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QtConcurrentRun>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QSlider>
#include "synthesizer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Synthesizer synth;
	QHBoxLayout layout;
	QFuture<void> future = QtConcurrent::run(&synth, &Synthesizer::start);

	QComboBox waveformSelect(&synth);
	waveformSelect.addItem("Sawtooth");
	waveformSelect.addItem("Triangle");
	waveformSelect.addItem("Square");
	waveformSelect.addItem("Sine");

	QSpinBox transposeSelect(&synth);
	transposeSelect.setRange(-12, 12);
	transposeSelect.setSingleStep(1);

	QSlider attackSelect(&synth);
	attackSelect.setRange(0, 100);

	QSlider decaySelect(&synth);
	decaySelect.setRange(0, 100);

	QSlider sustainSelect(&synth);
	sustainSelect.setRange(0, 100);
	sustainSelect.setValue(100);

	QSlider releaseSelect(&synth);
	releaseSelect.setRange(0, 100);

	layout.addWidget(&waveformSelect);
	layout.addWidget(&transposeSelect);
	layout.addWidget(&attackSelect);
	layout.addWidget(&decaySelect);
	layout.addWidget(&sustainSelect);
	layout.addWidget(&releaseSelect);
	synth.setLayout(&layout);

	synth.show();
	synth.setFocus();

	QObject::connect(&app, SIGNAL(lastWindowClosed()), &synth, SLOT(done()));

	QObject::connect(&waveformSelect, SIGNAL(activated(int)), &synth, SLOT(changeWaveform(int)));
	QObject::connect(&waveformSelect, SIGNAL(activated(int)), &synth, SLOT(setFocus()));

	QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setTranspose(int)));
	QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));

	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setAttack(int)));
	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));

	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), &synth, SLOT(setDecay(int)));
	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));

	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setSustain(int)));
	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));

	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setRelease(int)));
	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), &synth, SLOT(setFocus()));

	app.exec();

	return 0;
}
