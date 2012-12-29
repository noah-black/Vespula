#ifndef FMBOX_H
#define FMBOX_H_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QCheckBox>
#include <QObject>
#include <string>
#include "keyboard.h"

using namespace std;

class FmBox : public QGroupBox 
{
    Q_OBJECT
	public:
        FmBox(Keyboard **keyboard, QWidget *parent);
    public slots:
		void setFmDepth(int i);
        void setFmEnabled(int state);
	private:
        Keyboard **keyboard;
		QLabel fmLabel;
        QGridLayout fmLayout;
		QSlider fmDepthSelect;
		QCheckBox fmEnabled;
};
#endif
