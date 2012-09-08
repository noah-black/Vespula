#ifndef SOUNDMODULE
#define SOUNDMODULE

using namespace std;

class SoundModule {
	public:
		virtual double getSample(double sample) = 0;
};

#endif
