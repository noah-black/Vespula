#ifndef NOTE_H
#define NOTE_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

class Note {
	public:
		virtual double getSample() = 0;
		virtual bool isDead() = 0;
};
#endif
