#ifndef FILTER_BOX_H
#define FILTER_BOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QObject>
#include <string>
#include "filter.h"
#include "notefactory.h"


class FilterBox : public QGroupBox {
    Q_OBJECT
	public:
        FilterBox(Filter *filter, LFO *lfo, NoteFactory *noteFactory, QWidget *parent);
	virtual ~FilterBox() override {}; // Ensure virtual destructor
    public slots:
		void setCutoff(int value);
		void setResonance(int value);
        void setCutoffLfoAmount(int i);
        void setCutoffEnvAmount(int i);
	private:
        Filter *filter;
        LFO *lfo;
        NoteFactory *noteFactory;
        QGridLayout layout;
		QLabel filterLabel;
		QSlider cutoffSelect;
		QLabel cutoffLabel;
		QSlider resonanceSelect;
		QLabel resonanceLabel;
        QLabel cutoffLfoLabel;
		QSlider cutoffLfoAmountSelect;
        QLabel cutoffEnvLabel;
		QSlider cutoffEnvAmountSelect;
};
#endif
