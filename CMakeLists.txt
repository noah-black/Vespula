cmake_minimum_required(VERSION 3.14)

project(Vespula)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the sources and headers
set(SOURCES
    chorus.cpp
    envelope.cpp
    envelopebox.cpp
    envelopeconnection.cpp
    filter.cpp
    filterbox.cpp
    filterproxy.cpp
    fm.cpp
    fmbox.cpp
    keyboard.cpp
    lfo.cpp
    lfoable.cpp
    lfobox.cpp
    lfoconnection.cpp
    looper.cpp
    looperbox.cpp
    lpf.cpp
    main.cpp
    musicgenerator.cpp
    note.cpp
    notefactory.cpp
    oscillator.cpp
    oscillators.cpp
    soundmanager.cpp
    synthesizer.cpp
    vibrato.cpp
    vibratobox.cpp
    waveformcombobox.cpp
    wavetable.cpp
)

set(HEADERS
    chorus.h
    envelope.h
    envelopebox.h
    envelopeconnection.h
    filter.h
    filterbox.h
    filterproxy.h
    fm.h
    fmbox.h
    keyboard.h
    lfo.h
    lfoable.h
    lfobox.h
    lfoconnection.h
    looper.h
    looperbox.h
    lpf.h
    modulatable.h
    musicgenerator.h
    note.h
    notefactory.h
    oscillator.h
    oscillators.h
    soundmanager.h
    soundprocessor.h
    synthesizer.h
    vibrato.h
    vibratobox.h
    waveformcombobox.h
    wavetable.h
)

# Set the CMAKE_PREFIX_PATH to include the Qt installation path
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6/lib/cmake")

# Find required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia Widgets Concurrent)

# Add these lines in the CMakeLists.txt file after find_package
link_directories(/opt/homebrew/Cellar/qt/6.7.0_1/lib)

# Debug messages

message(STATUS "Qt6 Core: ${Qt6Core_VERSION}")
message(STATUS "Qt6 Gui: ${Qt6Gui_VERSION}")
message(STATUS "Qt6 Multimedia: ${Qt6Multimedia_VERSION}")
message(STATUS "Qt6 Widgets: ${Qt6Widgets_VERSION}")
message(STATUS "Qt6 Concurrent: ${Qt6Concurrent_VERSION}")

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link against Qt libraries
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Multimedia Qt6::Widgets Qt6::Concurrent)

# Compiler flags for debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")

# Link against AudioToolbox framework
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
target_link_libraries(${PROJECT_NAME} ${AUDIOTOOLBOX_LIBRARY})

# Enable verbose makefiles
set(CMAKE_VERBOSE_MAKEFILE ON)
