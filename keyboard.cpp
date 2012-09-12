#include "keyboard.h"
#include "sawtooth.h"
#include "delay.h"
#include <math.h>
#include <stdio.h>

using namespace std;

char notekeys[] = {'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j', 'k', 'o', 'l'};

Keyboard::Keyboard() : sawtooth(440, 0.02, 0.1), triangle(440, 0.02, 0.1), delay(2, &sawtooth) {
	currentNote = &sawtooth;
	octave = 0;
	initMaps();
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
	if(c >= '0' && c <= '9') {
		delay.setTranspose(c - '0');
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
		case 'c':
			currentNote = &sawtooth;
			delay.setPrototype(&sawtooth);
			break;
		case 'v':
			currentNote = &triangle;
			delay.setPrototype(&triangle);
			break;
		case 'b':
			currentNote->incrementRelease(-0.05);
			break;
		case 'n':
			currentNote->incrementRelease(0.05);
			break;
		case 'm':
			currentNote->incrementLevel(-0.05);
			break;
		case ',':
			currentNote->incrementLevel(0.05);
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
	delay.addNote(freqs[keyMap[c]] * pow(2.0, octave));
}

double Keyboard::getSample() {
	return delay.getSample();	
}
