#ifndef LOOPER_H
#define LOOPER_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include "keyboard.h"
#include "note.h"
#include <pthread.h>
#include <vector>

struct savedNote {
  enum note note;
  int octave;
  int duration;
};

class Looper : public Keyboard {
public:
  Looper(NoteFactory *noteFactory, double periodSeconds);
  double getSample();
  void releaseNote(enum note n);
  void setDuration(double value);
  void clear();

protected:
  void releaseNoteInternal(enum note n);

private:
  pthread_mutex_t mutexsum;
  pthread_mutex_t savedNoteMutex;
  void playSavedNote(struct savedNote);
  double getNotesSample();
  std::vector<std::vector<struct savedNote>> savedNotes;
  int period;
  int phase;
};

#endif
