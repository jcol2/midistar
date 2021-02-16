/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIDISTAR_MIDIOUT_H_
#define MIDISTAR_MIDIOUT_H_

#include <fluidsynth.h>

#include "smartpiano/SmartPianoClientImplementation.hpp"

namespace midistar {

/**
 * The MidiOut class provides an interface for playing MIDI audio.
 */
class MidiOut {
 public:
    /**
     * Constructor.
     */
    MidiOut();

    /**
     * Destructor.
     */
    ~MidiOut();

    /**
     * Initialises the class.
     *
     * \return true for success. false indicates failure.
     */
    bool Init();

    /**
     * Sends a MIDI note off event.
     *
     * \param note The MIDI note.
     * \param chan The MIDI channel.
     */
    void SendNoteOff(int note, int chan);

    /**
     * Sends a MIDI note on event.
     *
     * \param note The MIDI note.
     * \param chan The MIDI channel.
     * \param velocity The MIDI velocity.
     */
    void SendNoteOn(int note, int chan, int velocity);

 private:
    fluid_audio_driver_t* a_driver_;  //!< Stores fluidsynth audio driver
    int s_font_id_;  //!< Stores SoundFont handle
    fluid_settings_t* settings_;  //!< Stores fluidsynth settings
    fluid_synth_t* synth_;  //!< Stores fluidsynth synth instance

    smartpianoclient::SmartPianoClientImplementation* smart_piano_;
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIOUT_H_
