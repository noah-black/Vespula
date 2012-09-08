src = main.cpp synthesizer.cpp sawtooth.cpp delay.cpp keyboard.cpp
deps = main.cpp synthesizer.cpp sawtooth.cpp delay.cpp keyboard.cpp synthesizer.h sawtooth.h delay.h note.h keyboard.h soundmodule.h
all: synthesizer
synthesizer: $(deps)
	g++ -g $(src) -o synthesizer -lasound -lm -pthread -lncurses
.PHONY: clean
clean:
	rm -f synthesizer 
