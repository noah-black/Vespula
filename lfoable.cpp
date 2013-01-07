#include "lfoable.h"

void Lfoable::addLfoConnection(LfoConnection* lfoConnection) {
    lfoConnections.push_back(lfoConnection);
}

double Lfoable::getLfoPosition() {
    double lfoModifier;
    lfoModifier = 0;
    vector<LfoConnection*>::iterator it;
    for(it = lfoConnections.begin(); it != lfoConnections.end(); ++it) {
        lfoModifier += (*it)->getPos();
    }
    return lfoModifier;
}
