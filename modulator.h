#ifndef MODULATOR_H
#define MODULATOR_H
#include <set>
#include "modulatorlistener.h"

using namespace std;

class Modulator {
    public:
        void addListener(ModulatorListener *listener);
        void removeListener(ModulatorListener *listener);
        virtual void updateListeners() = 0;
    protected:
        set<ModulatorListener*> listeners;
};

#endif
