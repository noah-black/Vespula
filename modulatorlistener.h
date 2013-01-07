#ifndef MODULATORLISTENER_H
#define MODULATORLISTENER_H

class ModulatorListener {
    public:
        virtual void update(double signal) = 0;
};

#endif
