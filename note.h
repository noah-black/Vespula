#ifndef NOTE_H
#define NOTE_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

class Note {
	public:
		virtual double getSample() = 0;
		virtual bool isDead() = 0;
		virtual Note *clone(double freq) = 0;
		void setFreq(double freq);
		void setRelease(double release);
		void setLevel(double level);
		void incrementRelease(double amount);
		void incrementLevel(double amount);
	protected:
		double period;
		double samples_elapsed;
		double freq;
		double level;
		double release;
};
#endif
