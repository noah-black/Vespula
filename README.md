Vespula
=====

Installation:

1. Install the libasound2-dev package (Debian : sudo apt-get install libasound2-dev)
2. Install Qt 4 (Debian : sudo apt-get install qt4-dev-tools)
3. Generate the Makefile with the qmake command.
4. Use the make command to build the 'vespula' executable file.

Instructions:

You can use your QWERTY keyboard to play the Vespula synthesizer. The keys are laid out like a piano. 
Think of the home row as the white keys, and the row above it as the black keys.
(Except the white keys are, by default, the A major scale, instead of C major)

Press the 1..9 keys to change octave.

Use the transpose setting (in the GUI) to transpose all notes by some number of semitones (i.e., change key). 
Example: A transpose of +3 puts you in C major (A major shifted up by 3).

Press ctrl-[1-9] to transpose in key. Ctrl-1 is unshifted, 2-9 are shifted up by a number of whole tones.
In the 'looper' mode, a series of these transitions can sound like a chord progression.
In regular mode, shifting the 'white' notes while preserving key has the effect of shifting to different 'modes'.
