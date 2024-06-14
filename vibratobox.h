#ifndef VIBRATOBOX_H
#define VIBRATOBOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QObject>
#include <string>
#include "vibrato.h"


class VibratoBox : public QGroupBox 
{
    Q_OBJECT
	public:
        VibratoBox(Vibrato *vibrato, QWidget *parent);
	virtual ~VibratoBox() override {}; // Ensure virtual destructor

    public slots:
		void setVibDepth(int value);
		void setVibPeriod(int value);
	private:
        Vibrato *vibrato;
        QGridLayout vibLayout;
		QLabel vibratoLabel;
		QSlider vibDepthSelect;
		QLabel vibDepthLabel;
		QSlider vibPeriodSelect;
		QLabel vibPeriodLabel;
};
#endif
