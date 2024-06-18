#ifndef ENVELOPE_BOX_H
#define ENVELOPE_BOX_H

#include "envelope.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QWidget>
#include <string>

class EnvelopeBox : public QGroupBox {
  Q_OBJECT
public:
  EnvelopeBox(Envelope *envelope, QWidget *parent);
  ~EnvelopeBox() override {}; // Ensure virtual destructor
public slots:
  void setAttack(int value);
  void setDecay(int value);
  void setSustain(int value);
  void setRelease(int value);

private:
  Envelope *envelope;
  QGridLayout envLayout;
  QLabel envelopeLabel;
  QSlider attackSelect;
  QLabel attackLabel;
  QSlider decaySelect;
  QLabel decayLabel;
  QSlider sustainSelect;
  QLabel sustainLabel;
  QSlider releaseSelect;
  QLabel releaseLabel;
};
#endif
