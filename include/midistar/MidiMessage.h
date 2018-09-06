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

#ifndef MIDISTAR_MIDIMESSAGE_H_
#define MIDISTAR_MIDIMESSAGE_H_

#include <vector>

namespace midistar {

/**
 * The MidiMessage class represents MIDI messages.
 */
class MidiMessage {
 public:
    /**
     * Constructor. Leaves object in an empty state.
     */
    MidiMessage();

    /**
     * Constructor for MIDI messages from a MIDI file that represent a MIDI note-
     * on command and have an associated duration.
     *
     * \param data The underlying MIDI message data.
     * \param duration The duration of the note.
     * \param time Timestamp of the message.
     * \param track The MIDI track of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double duration
            , double time
            , int track);

    /**
     * Constructor for MIDI messages from a MIDI file.
     *
     * \param data The underlying MIDI message data.
     * \param time Timestamp of the message.
     * \param track The MIDI track of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double time
            , int track);

    /**
     * Constructor for MIDI messages from a MIDI stream.
     *
     * \param data The underlying MIDI message data.
     * \param time Timestamp of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double time);

    /**
     * Constructor for general MIDI messages.
     *
     * \param data The underlying MIDI message data.
     */
    explicit MidiMessage(std::vector<unsigned char> data);

    /**
     * Gets the MIDI channel (if applicable).
     *
     * \return If applicable, returns MIDI channel. Otherwise -1.
     */
    int GetChannel() const;

    /**
     * Gets underlying MIDI message data.
     *
     * \return Underlying MIDI data.
     */
    const std::vector<unsigned char>& GetData() const;

    /**
     * Gets the duration if this MIDI message is a note-on event and the
     * duration is available.
     *
     * \return Note duration if available. Otherwise -1.
     */
    double GetDuration() const;

    /**
     * Gets the MIDI key if this MIDI message is a note event.
     *
     * \return MIDI key if available. Otherwise -1.
     */
    int GetKey() const;

    /**
     * Gets the MIDI timestamp if it is available.
     *
     * \return MIDI timestamp if available. Otherwise -1.
     */
    double GetTime() const;

    /**
     * Gets the MIDI track if it is available.
     *
     * \return MIDI track if available. Otherwise -1.
     */
    int GetTrack() const;

    /**
     * Gets the MIDI velocity if this MIDI message is a note-on event.
     *
     * \return MIDI velocity if available. Otherwise -1.
     */
    int GetVelocity() const;

    /**
     * Determines whether or not this MIDI message is a note-on / note-off
     * event.
     *
     * \return True if the MIDI message is a note-on / note-off event. False
     * otherwise.
     */
    bool IsNote() const;

    /**
     * Determines whether or not this MIDI message is a note-off event.
     *
     * \return True if the MIDI message is a note-on event. False otherwise.
     */
    bool IsNoteOff() const;

    /**
     * Determines whether or not this MIDI message is a note-on event.
     *
     * \return True if the MIDI message is a note-off event. False otherwise.
     */
    bool IsNoteOn() const;

    /**
     * Sets the MIDI key of the message.
     *
     * \param note The MIDI key.
     */
    void SetKey(int key);

 private:
    static const unsigned char CHANNEL_MASK = 0x0f;  //!< Mask for channel
    static const unsigned char COMMAND_MASK = 0xf0;  //!< Mask for command
    static const unsigned char NOTE_OFF_COMMAND = 0x80;  //!< MIDI note off
    static const unsigned char NOTE_ON_COMMAND = 0x90;  //!< MIDI note on

    std::vector<unsigned char> data_;  //!< MIDI data
    double duration_;  //!< Holds duration for MIDI note on messages
    double time_;  //!< Message timestamp for messages from MIDI file
    int track_;  //!< Message track for messages from MIDI file
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIMESSAGE_H_
