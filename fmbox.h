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
#include "notefactory.h"

using namespace std;

class FmBox : public QGroupBox 
{
    Q_OBJECT
	public:
        FmBox(NoteFactory *noteFactory, QWidget *parent);
    public slots:
		void setFmDepth(int i);
        void setFmEnabled(int state);
	private:
        NoteFactory *noteFactory;
		QLabel fmLabel;
        QGridLayout fmLayout;
		QSlider fmDepthSelect;
		QCheckBox fmEnabled;
};
#endif
