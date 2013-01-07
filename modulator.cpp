#include "modulator.h"

void Modulator::addListener(ModulatorListener *listener) {
    listeners.insert(listener);
}

void Modulator::removeListener(ModulatorListener *listener) {
    listeners.erase(listener);
}
