#ifndef VIBRATOBOX_H
#define VIBRATOBOX_H

#include "vibrato.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QWidget>
#include <string>

class VibratoBox : public QGroupBox {
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
