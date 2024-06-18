#ifndef LOOPER_BOX
#define LOOPER_BOX

#include "looper.h"
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>

class LooperBox : public QGroupBox {
  Q_OBJECT
public:
  LooperBox(Keyboard **currentKeyboard, Keyboard *normalKeyboard,
            Looper *looper, QWidget *parent);
  virtual ~LooperBox() override {}; // Ensure virtual destructor
public slots:
  void setLooperEnabled(int state);
  void setLooperDuration(int value);
  void clear(bool value);

private:
  Keyboard **currentKeyboard;
  Keyboard *normalKeyboard;
  Looper *looper;
  QGridLayout layout;
  QSpinBox durationSelect;
  QLabel durationSelectLabel;
  QCheckBox looperEnabled;
  QLabel looperLabel;
  QPushButton clearButton;
};

#endif
