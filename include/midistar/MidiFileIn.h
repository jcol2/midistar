/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
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

#ifndef MIDISTAR_MIDIFILEIN_H_
#define MIDISTAR_MIDIFILEIN_H_

#include <midifile/MidiFile.h>
#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "midistar/MidiIn.h"

namespace midistar {

/**
 * The MidiFileIn reads events from a MIDI file in a real-time fashion.
 */
class MidiFileIn : public MidiIn {
 public:
    /**
     * Constructor.
     */
    MidiFileIn();

    /**
     * Destructor.
     */
    ~MidiFileIn();

    /**
     * Gets the maximum duration of all notes in the MIDI file.
     *
     */
    double GetMaximumNoteDuration() const;

    /**
     * Gets the ticks per quarter note of the MIDI file.
     *
     * \return Ticks per qurater note.
     */
    int GetTicksPerQuarterNote() const;

    /**
     * Returns the unique MIDI notes in the song.
     *
     * \return Unique MIDI notes.
     */
    std::vector<int> GetUniqueMidiNotes() const;

    /**
     * Initialises the class.
     *
     * \param file_name MIDI file to open.
     *
     * \return true for success. false indicates failure.
     */
    bool Init(const std::string& file_name);

    /**
     * Determines whether or not the reader is at the end of the MIDI file.
     *
     * \return True if the reader is at EOF. False otherwise.
     */
    bool IsEof();

    /**
     * Advances the reader by the time difference specified.
     *
     * \param delta The time difference to advance the reader by.
     */
    void Tick(int delta);

 private:
    static const int MAX_MIDI_CHANNELS = 16;
    static const int MAX_MIDI_TRACKS = 128;

    bool IsWanted(const smf::MidiEvent* mev) const;  //!< Determines if we want
                                                    //!< to store a MIDI message

    bool channels_[MAX_MIDI_CHANNELS];  //!< The channels to read from. Each
            //!< index represents a channel. Only read from channels with true.
    smf::MidiFile file_;  //!< Underlying MIDI file instance
    int index_;  //!< Index of event in track
    int time_;  //!< The time index of the reade
    bool tracks_[MAX_MIDI_TRACKS];  //!< The tracks to read from. Each index
                      //!< represents a track. Only read from tracks with true.
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIFILEIN_H_
