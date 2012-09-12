src = delay.cpp keyboard.cpp main.cpp sawtooth.cpp synthesizer.cpp triangle.cpp note.cpp
deps = delay.cpp delay.h keyboard.cpp keyboard.h main.cpp note.h sawtooth.cpp sawtooth.h soundmodule.h synthesizer.cpp synthesizer.h triangle.cpp triangle.h note.cpp
all: synthesizer
synthesizer: $(deps)
	g++ -g $(src) -o synthesizer -lasound -lm -pthread -lncurses
.PHONY: clean
clean:
	rm -f synthesizer 
