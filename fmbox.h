#ifndef FMBOX_H
#define FMBOX_H

#include "notefactory.h"
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QWidget>
#include <string>

class FmBox : public QGroupBox {
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
