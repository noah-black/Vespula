#include "waveformcombobox.h"

WaveformComboBox::WaveformComboBox(QWidget *parent) : QComboBox(parent) {
  this->addItem("Sawtooth");
  this->addItem("Triangle");
  this->addItem("Square");
  this->addItem("Sine");
}

waveformType WaveformComboBox::getWaveformType(int i) {
  switch (i) {
  case 0:
    return &WaveTable::sawtooth;
  case 1:
    return &WaveTable::triangle;
  case 2:
    return &WaveTable::square;
  case 3:
    return &WaveTable::sine;
  }
  return NULL;
}
