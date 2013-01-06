#############################################################################
# Makefile for building: synth
# Generated by qmake (2.01a) (Qt 4.8.1) on: Sun Jan 6 00:51:18 2013
# Project:  synth.pro
# Template: app
# Command: /usr/bin/qmake -config debug -o Makefile synth.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -pg -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -m64 -pg
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lasound -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = chorus.cpp \
		envelope.cpp \
		envelopebox.cpp \
		envelopeconnection.cpp \
		fm.cpp \
		fmbox.cpp \
		keyboard.cpp \
		lfo.cpp \
		lfoable.cpp \
		lfobox.cpp \
		lfoconnection.cpp \
		looper.cpp \
		lpf.cpp \
		main.cpp \
		modulator.cpp \
		note.cpp \
		notefactory.cpp \
		oscillator.cpp \
		oscillators.cpp \
		soundmanager.cpp \
		synthesizer.cpp \
		vibrato.cpp \
		vibratobox.cpp \
		wavetable.cpp moc_envelopebox.cpp \
		moc_fmbox.cpp \
		moc_lfobox.cpp \
		moc_synthesizer.cpp \
		moc_vibratobox.cpp
OBJECTS       = chorus.o \
		envelope.o \
		envelopebox.o \
		envelopeconnection.o \
		fm.o \
		fmbox.o \
		keyboard.o \
		lfo.o \
		lfoable.o \
		lfobox.o \
		lfoconnection.o \
		looper.o \
		lpf.o \
		main.o \
		modulator.o \
		note.o \
		notefactory.o \
		oscillator.o \
		oscillators.o \
		soundmanager.o \
		synthesizer.o \
		vibrato.o \
		vibratobox.o \
		wavetable.o \
		moc_envelopebox.o \
		moc_fmbox.o \
		moc_lfobox.o \
		moc_synthesizer.o \
		moc_vibratobox.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		synth.pro
QMAKE_TARGET  = synth
DESTDIR       = 
TARGET        = synth

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: synth.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -config debug -o Makefile synth.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -config debug -o Makefile synth.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/synth1.0.0 || $(MKDIR) .tmp/synth1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/synth1.0.0/ && $(COPY_FILE) --parents chorus.h envelope.h envelopebox.h envelopeconnection.h fm.h fmbox.h keyboard.h lfo.h lfoable.h lfobox.h lfoconnection.h looper.h lpf.h modulatable.h modulator.h modulatorlistener.h note.h notefactory.h oscillator.h oscillators.h soundmanager.h soundprocessor.h synthesizer.h vibrato.h vibratobox.h wavetable.h .tmp/synth1.0.0/ && $(COPY_FILE) --parents chorus.cpp envelope.cpp envelopebox.cpp envelopeconnection.cpp fm.cpp fmbox.cpp keyboard.cpp lfo.cpp lfoable.cpp lfobox.cpp lfoconnection.cpp looper.cpp lpf.cpp main.cpp modulator.cpp note.cpp notefactory.cpp oscillator.cpp oscillators.cpp soundmanager.cpp synthesizer.cpp vibrato.cpp vibratobox.cpp wavetable.cpp .tmp/synth1.0.0/ && (cd `dirname .tmp/synth1.0.0` && $(TAR) synth1.0.0.tar synth1.0.0 && $(COMPRESS) synth1.0.0.tar) && $(MOVE) `dirname .tmp/synth1.0.0`/synth1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/synth1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_envelopebox.cpp moc_fmbox.cpp moc_lfobox.cpp moc_synthesizer.cpp moc_vibratobox.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_envelopebox.cpp moc_fmbox.cpp moc_lfobox.cpp moc_synthesizer.cpp moc_vibratobox.cpp
moc_envelopebox.cpp: envelope.h \
		modulator.h \
		modulatorlistener.h \
		soundprocessor.h \
		wavetable.h \
		envelopebox.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) envelopebox.h -o moc_envelopebox.cpp

moc_fmbox.cpp: notefactory.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		note.h \
		fmbox.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) fmbox.h -o moc_fmbox.cpp

moc_lfobox.cpp: lfo.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillators.h \
		lfobox.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) lfobox.h -o moc_lfobox.cpp

moc_synthesizer.cpp: keyboard.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		notefactory.h \
		note.h \
		lpf.h \
		vibrato.h \
		looper.h \
		chorus.h \
		envelopebox.h \
		lfobox.h \
		vibratobox.h \
		fmbox.h \
		soundmanager.h \
		synthesizer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) synthesizer.h -o moc_synthesizer.cpp

moc_vibratobox.cpp: vibrato.h \
		soundprocessor.h \
		wavetable.h \
		vibratobox.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) vibratobox.h -o moc_vibratobox.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

chorus.o: chorus.cpp chorus.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chorus.o chorus.cpp

envelope.o: envelope.cpp envelope.h \
		modulator.h \
		modulatorlistener.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o envelope.o envelope.cpp

envelopebox.o: envelopebox.cpp envelopebox.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o envelopebox.o envelopebox.cpp

envelopeconnection.o: envelopeconnection.cpp envelopeconnection.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		soundprocessor.h \
		wavetable.h \
		modulatable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o envelopeconnection.o envelopeconnection.cpp

fm.o: fm.cpp fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fm.o fm.cpp

fmbox.o: fmbox.cpp fmbox.h \
		notefactory.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		note.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fmbox.o fmbox.cpp

keyboard.o: keyboard.cpp keyboard.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		notefactory.h \
		note.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o keyboard.o keyboard.cpp

lfo.o: lfo.cpp lfo.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillators.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lfo.o lfo.cpp

lfoable.o: lfoable.cpp lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillators.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lfoable.o lfoable.cpp

lfobox.o: lfobox.cpp lfobox.h \
		lfo.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillators.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lfobox.o lfobox.cpp

lfoconnection.o: lfoconnection.cpp lfoconnection.h \
		lfo.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillators.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lfoconnection.o lfoconnection.cpp

looper.o: looper.cpp looper.h \
		note.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillator.h \
		envelopeconnection.h \
		modulatable.h \
		keyboard.h \
		fm.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		notefactory.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o looper.o looper.cpp

lpf.o: lpf.cpp lpf.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lpf.o lpf.cpp

main.o: main.cpp synthesizer.h \
		keyboard.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		notefactory.h \
		note.h \
		lpf.h \
		vibrato.h \
		looper.h \
		chorus.h \
		envelopebox.h \
		lfobox.h \
		vibratobox.h \
		fmbox.h \
		soundmanager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

modulator.o: modulator.cpp modulator.h \
		modulatorlistener.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o modulator.o modulator.cpp

note.o: note.cpp note.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		oscillator.h \
		envelopeconnection.h \
		modulatable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o note.o note.cpp

notefactory.o: notefactory.cpp notefactory.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		note.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o notefactory.o notefactory.cpp

oscillator.o: oscillator.cpp oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o oscillator.o oscillator.cpp

oscillators.o: oscillators.cpp oscillators.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o oscillators.o oscillators.cpp

soundmanager.o: soundmanager.cpp soundmanager.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o soundmanager.o soundmanager.cpp

synthesizer.o: synthesizer.cpp synthesizer.h \
		keyboard.h \
		fm.h \
		oscillator.h \
		soundprocessor.h \
		wavetable.h \
		envelope.h \
		modulator.h \
		modulatorlistener.h \
		modulatable.h \
		envelopeconnection.h \
		lfoable.h \
		lfoconnection.h \
		lfo.h \
		oscillators.h \
		notefactory.h \
		note.h \
		lpf.h \
		vibrato.h \
		looper.h \
		chorus.h \
		envelopebox.h \
		lfobox.h \
		vibratobox.h \
		fmbox.h \
		soundmanager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o synthesizer.o synthesizer.cpp

vibrato.o: vibrato.cpp vibrato.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vibrato.o vibrato.cpp

vibratobox.o: vibratobox.cpp vibratobox.h \
		vibrato.h \
		soundprocessor.h \
		wavetable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vibratobox.o vibratobox.cpp

wavetable.o: wavetable.cpp wavetable.h \
		soundprocessor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wavetable.o wavetable.cpp

moc_envelopebox.o: moc_envelopebox.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_envelopebox.o moc_envelopebox.cpp

moc_fmbox.o: moc_fmbox.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_fmbox.o moc_fmbox.cpp

moc_lfobox.o: moc_lfobox.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_lfobox.o moc_lfobox.cpp

moc_synthesizer.o: moc_synthesizer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_synthesizer.o moc_synthesizer.cpp

moc_vibratobox.o: moc_vibratobox.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_vibratobox.o moc_vibratobox.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

