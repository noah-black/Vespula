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

using namespace std;

class FilterBox : public QGroupBox {
    Q_OBJECT
	public:
        FilterBox(Filter *filter, QWidget *parent);
    public slots:
		void setCutoff(int value);
		void setResonance(int value);
	private:
        Filter *filter;
        QGridLayout layout;
		QLabel filterLabel;
		QSlider cutoffSelect;
		QLabel cutoffLabel;
		QSlider resonanceSelect;
		QLabel resonanceLabel;
};
#endif
