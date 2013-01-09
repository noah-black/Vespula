#ifndef LOOPER_BOX
#define LOOPER_BOX

#include "looper.h"
#include <QGroupBox>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QCheckBox>

using namespace std;

class LooperBox : public QGroupBox {
    Q_OBJECT
    public:
        LooperBox(Keyboard **currentKeyboard, Keyboard *normalKeyboard, Looper *looper, QWidget *parent);
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
