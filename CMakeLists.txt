cmake_minimum_required(VERSION 2.8.9)
project (midistar)

# Find external libraries
include_directories(include)
include_directories(/home/jez/projects/smartpianoclient-cpp/include)
include_directories(/home/jez/sandbox/serial/include/)

# Set headers
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/midistar/BackgroundSongPlayerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/BarComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/CollidableComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/CollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Component.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Constants.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Config.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DefaultGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DelayedComponentComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DeleteOffscreenComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DrumGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DrumSceneFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DrumScoreDeltaProvider.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DrumSongNoteCollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/FadeOutEffectComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Game.h
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObject.h
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObject.tpp
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentAutoPlayComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentInputHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/IntroSceneFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/IntroSceneSfmlEventsHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InvertColourComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/KeepAliveComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/LambdaComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuBuilder.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuInputHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuItemBuilder.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MenuItemComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiFileGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiFileIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiFileInComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiInstrumentGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiInstrumentIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiInstrumentInComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiMessage.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiNoteComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiOut.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiOutputComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiPortIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/NoteInfoComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/OutlineEffectComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PhysicsComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PianoGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PianoSceneFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PianoScoreDeltaProvider.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PianoSongNoteCollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ResizeComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Scene.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SceneFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ScoreComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ScoreDeltaProvider.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ScoreManagerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ScoreManagerFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SfmlEventsComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SfmlEventsHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ShrinkGrowComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongEndWatcherComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongSceneSfmlEventsHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongNoteCreatorComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongNoteComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SpriteAnimatorComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/TextFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Utility.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Version.h
    ${CMAKE_SOURCE_DIR}/include/midistar/VerticalCollisionDetectorComponent.h
)

# Set source
set(SOURCE
    ${CMAKE_SOURCE_DIR}/src/BackgroundSongPlayerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/BarComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollidableComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Component.cpp
    ${CMAKE_SOURCE_DIR}/src/Config.cpp
    ${CMAKE_SOURCE_DIR}/src/DefaultGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DelayedComponentComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/DeleteOffscreenComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumSceneFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumScoreDeltaProvider.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumSongNoteCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/FadeOutEffectComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentAutoPlayComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/IntroSceneFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/IntroSceneSfmlEventsHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentInputHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertColourComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/KeepAliveComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/LambdaComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuBuilder.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuInputHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuItemBuilder.cpp
    ${CMAKE_SOURCE_DIR}/src/MenuItemComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiFileGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiFileIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiFileInComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiInstrumentGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiInstrumentIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiInstrumentInComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiOut.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiOutputComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiPortIn.cpp
    ${CMAKE_SOURCE_DIR}/src/NoteInfoComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/OutlineEffectComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PhysicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoSceneFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoScoreDeltaProvider.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoSongNoteCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ResizeComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Scene.cpp
    ${CMAKE_SOURCE_DIR}/src/ScoreComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ScoreManagerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ScoreManagerFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/SfmlEventsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SfmlEventsHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongSceneSfmlEventsHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ShrinkGrowComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongNoteCreatorComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongEndWatcherComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SpriteAnimatorComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/TextFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/Utility.cpp
    ${CMAKE_SOURCE_DIR}/src/VerticalCollisionDetectorComponent.cpp
)

# If build type is not set, default to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

# Check for valid build type
if(NOT ${build_type} STREQUAL "debug" AND NOT ${build_type} STREQUAL "release")
    message("Warning: invalid build type \"${CMAKE_BUILD_TYPE}\" supplied. Setting to \"Debug\"...")
    set(CMAKE_BUILD_TYPE "Debug")
    set(build_type "debug")
endif()

# Inject git revision to Version.h
set(MIDISTAR_VERSION_REVISION 0)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  find_package(Git)
  if (GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "MIDISTAR_VERSION_REVISION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Git revision: ${MIDISTAR_VERSION_REVISION}" )
  endif()
endif()

if ("${MIDISTAR_VERSION_REVISION}" EQUAL "0")
    message("Warning: could not set git revision in Version.h.")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/midistar/Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/midistar/Version.h @ONLY)

# Specify platform
if (WIN32)
    message("-- Windows detected")
    message("-- Release/Debug modes")
    set(platform win32)

    # Specify link directory
    link_directories(${CMAKE_SOURCE_DIR}/lib)
else()
    if (${APPLE})
        message("-- OSX detected")
        set(platform osx)
    else()
        message("-- Linux detected")
        set(platform debian)
    endif()

    # Specify link directory by build type
    link_directories(${CMAKE_SOURCE_DIR}/lib/${build_type})
    link_directories(/home/jez/projects/smartpianoclient-cpp)
    link_directories(/home/jez/sandbox/serial/build/devel/lib)

    # Change binary output dir
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${build_type})
endif()

# Create executable
add_executable(midistar
    ${HEADERS}
    ${SOURCE}
)

# Create config (if it does not exist)
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/config.cfg)
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/config.cfg
        ${CMAKE_SOURCE_DIR}/.)
endif()

# OS specific stuff
if (WIN32) # Windows
    # We only want Debug and Release
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    # Add libraries
    target_link_libraries(midistar
        debug debug/fluidsynth optimized release/fluidsynth
        debug debug/midifile optimized release/midifile
        debug debug/rtmidi-d optimized release/rtmidi
        debug debug/sfml-graphics-d optimized release/sfml-graphics
        debug debug/sfml-system-d optimized release/sfml-system
        debug debug/sfml-window-d optimized release/sfml-window)

    # Copy Release and Debug libs
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:midistar>)

    # Set compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # Set debugging directory
    set_property(TARGET midistar
        PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    # Set startup project
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT midistar)

    # Copy Windows run script for Debug / Release
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/win32/run_$<CONFIGURATION>.bat
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_SOURCE_DIR}/run_$<CONFIGURATION>.bat
        ../run.bat)

    # Copy 'make.bat' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/win32/make.bat
        ${CMAKE_SOURCE_DIR}/.)

    # Copy 'startvs.bat' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/win32/startvs.bat
        ${CMAKE_SOURCE_DIR}/.)

else() # Linux/OSX
    # Do common stuff for Linux/OSX (Unix)
    # Set compiler flags
    if(${build_type} STREQUAL "release")
        message("-- Release mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
    else()
        message("-- Debug mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -DDEBUG -g -O0")
    endif()

    # Add stdc++ filesystem flag
    if(NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
    endif()

    # Link libraries depending on build type
    if(${build_type} STREQUAL "release")
        set(UNIX_LIBS midifile rtmidi sfml-graphics sfml-system sfml-window)
    else()
        set(UNIX_LIBS midifile rtmidi sfml-graphics-d sfml-system-d sfml-window-d smartpianoclient serial)
    endif()

    # Add stdc++ filesystem flag
    if(NOT APPLE)
        list(APPEND UNIX_LIBS stdc++fs)
    endif()

    # Link libraries
    target_link_libraries(midistar ${UNIX_LIBS})

    # Copy Unix 'make' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/unix/make
        ${CMAKE_SOURCE_DIR}/.)

    # Copy Linux/OSX run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/run_${build_type}
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_SOURCE_DIR}/run_${build_type}
        ../run)

    # Copy Linux/OSX debug script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/debug
        ${CMAKE_SOURCE_DIR}/.)

    # OSX specific stuff
    if(${APPLE})
        # fluidsynth is a framework on OSX
        set_target_properties(midistar PROPERTIES LINK_FLAGS
            "-Wl,-F${CMAKE_SOURCE_DIR}/lib/${build_type}")
        target_link_libraries(midistar
            "-framework FluidSynth")

    # Linux specific stuff
    elseif(UNIX)
        # fluidsynth is a normal library on Linux
        target_link_libraries(midistar
            fluidsynth)
    endif()
endif()
