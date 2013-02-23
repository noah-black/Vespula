#ifndef FILTER_PROXY_H
#define FILTER_PROXY_H

#include <stdlib.h>
#include <filter.h>
#include <modulatable.h>

class FilterProxy : public Filter, public Modulatable {
    public:
        FilterProxy(Filter *filter);
        void modulate(double amount);
        double getCutoff();
        double getResonance();
        double getSample(double input);
	private:
        Filter *filter;
        double cutoffMod;
};

#endif
