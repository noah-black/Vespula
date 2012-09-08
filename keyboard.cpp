#include "keyboard.h"
#include "sawtooth.h"
#include "delay.h"
#include <math.h>

using namespace std;

char notekeys[] = {'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j', 'k', 'o', 'l'};

Keyboard::Keyboard() {
	octave = 0;
	initMaps();
	modules.push_back(new Delay(1, 2, 0.5));
}

void Keyboard::initMaps() {
	freqs[a] = 440;
	freqs[aSharp] = 469.66667;
	freqs[b] = 490;
	freqs[c] = 522.5;
	freqs[cSharp] = 550;
	freqs[d] = 583.33333;
	freqs[dSharp] = 625.77778;
	freqs[e] = 660;
	freqs[f] = 691.42857;
	freqs[fSharp] = 736.66667;
	freqs[g] = 782.22222;
	freqs[gSharp] = 825;
	freqs[a2] = 880;
	freqs[aSharp2] = 938.66667;
	freqs[b2] = 980;

	keyMap['a'] = a;
	keyMap['w'] = aSharp;
	keyMap['s'] = b;
	keyMap['e'] = c;
	keyMap['d'] = cSharp;
	keyMap['f'] = d;
	keyMap['t'] = dSharp;
	keyMap['g'] = e;
	keyMap['y'] = f;
	keyMap['h'] = fSharp;
	keyMap['u'] = g;
	keyMap['j'] = gSharp;
	keyMap['k'] = a2;
	keyMap['o'] = aSharp2;
	keyMap['l'] = b2;
}

void Keyboard::takeInput(char c) {
	if(isNote(c)) {
		playNote(c);
		return;
	}
	switch(c) {
		case 'z':  
			if (octave > -3) 
				octave--;
			break;
		case 'x': 
			if (octave < 3)
				octave++; 
			break;
	}
}

bool Keyboard::isNote(char c) {
	int i;
	int length = sizeof(notekeys) / sizeof(char);
	for (i = 0; i < length; i++) {
		if(c == notekeys[i])
			return true;
	}
	return false;
}

void Keyboard::playNote(char c) {
	notes.push_back(new Sawtooth(freqs[keyMap[c]] * pow(2.0, octave), 0.1, 0.1));
}

double Keyboard::getSample() {
	vector<Note*>::iterator it;
	vector<SoundModule*>::iterator modit;
	double sample;
	sample = 0;
	it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample();
		if((*it)->isDead())
			it = notes.erase(it);
		else
			it++;
	}
	for(modit = modules.begin(); modit != modules.end(); modit++)
		sample = (*modit)->getSample(sample);
	return sample;
}
