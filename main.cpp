#include <QApplication>
#include <QtConcurrent>
#include "synthesizer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyleSheet("QGroupBox { border: 1px solid black; }");

    Synthesizer synth;
    QObject::connect(&app, &QApplication::lastWindowClosed, &synth, &Synthesizer::done);

    QFuture<void> future = QtConcurrent::run([&synth]() { synth.start(); });

    return app.exec();
}
