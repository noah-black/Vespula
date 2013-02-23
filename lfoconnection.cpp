#include "lfoconnection.h"

LfoConnection::LfoConnection(LFO *target, double amount) : 
target(target), 
amount(amount) 
{ }

double LfoConnection::getPos() {
    return target->getPos()*amount;
}

void LfoConnection::setAmount(double amount) {
    this->amount = amount;
}
