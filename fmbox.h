#ifndef FMBOX_H
#define FMBOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QCheckBox>
#include <QObject>
#include <string>
#include "notefactory.h"


class FmBox : public QGroupBox 
{
    Q_OBJECT
	public:
        FmBox(NoteFactory *noteFactory, QWidget *parent);
    public slots:
		void setFmDepth(int i);
        void setFmEnabled(int state);
        void setFmEnvelopeEnabled(int state);
        void setFmEnvAmount(int i);
        void setFmLfoEnabled(int state);
        void setFmLfoAmount(int i);
	private:
        NoteFactory *noteFactory;
        QGridLayout fmLayout;
		QLabel fmLabel;

        QLabel fmDepthLabel;
		QSlider fmDepthSelect;
		QCheckBox fmEnabled;

        QLabel fmEnvelopeLabel;
		QSlider fmEnvAmountSelect;
		QCheckBox fmEnvelopeEnabled;

        QLabel fmLfoLabel;
		QSlider fmLfoAmountSelect;
		QCheckBox fmLfoEnabled;
};
#endif
