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

#include "midistar/MidiFileIn.h"

#include <iostream>

#include "midistar/Config.h"

namespace midistar {

MidiFileIn::MidiFileIn()
        : channels_{0}
        , index_{0}
        , time_{0}
        , tracks_{0} {
}

MidiFileIn::~MidiFileIn() {
}

double MidiFileIn::GetMaximumNoteDuration() const {
    double max = 0;
    for (int i = 0; i < file_[0].size(); ++i) {
        if (IsWanted(&file_[0][i])) {
            max = std::max(max, file_[0][i].getDurationInSeconds());
        }
    }
    return max;
}

int MidiFileIn::GetTicksPerQuarterNote() const {
    return file_.getTicksPerQuarterNote();
}

std::vector<int> MidiFileIn::GetUniqueMidiNotes() const {
    std::set<int> notes;
    for (int i=0; i < file_[0].size(); ++i) {
        if (file_[0][i].isNote()) {
            notes.insert(file_[0][i][1]);
        }
    }
    return std::vector<int>{notes.begin(), notes.end()};
}

bool MidiFileIn::Init(const std::string& file_name) {
    // We use a bool array to turn on channels / tracks
    for (int c : Config::GetInstance().GetMidiFileChannels()) {
        if (c == -1) {
            for (bool& b : channels_) {
                b = true;
            }
            break;
        }

        if (c >= 0 && c < MAX_MIDI_CHANNELS) {
            channels_[c] = true;
        }
    }
    for (int t : Config::GetInstance().GetMidiFileTracks()) {
        if (t == -1) {
            for (bool& b : tracks_) {
                b = true;
            }
            break;
        }

        if (t >= 0 && t < MAX_MIDI_TRACKS) {
            tracks_[t] = true;
        }
    }

    file_.read(file_name);
    bool success = file_.status();
    file_.joinTracks();
    file_.linkNotePairs();
    file_.doTimeAnalysis();
    if (!success) {
        std::cerr << "Error! Could not load MIDI file \"" << file_name << "\""
        << ".\n";
    }
    return success;
}

bool MidiFileIn::IsEof() {
    return index_ >= file_[0].size();
}

void MidiFileIn::Tick(int delta) {
    time_ += delta;

    smf::MidiEvent* mev;
    while (!IsEof() && file_.getTimeInSeconds((mev = &file_[0][index_])->tick)
                * 1000 <= time_) {
        if (IsWanted(mev)) {
            MidiMessage msg{
                *mev
                , mev->getDurationInSeconds()
                , static_cast<double>(mev->tick)
                , mev->track};
            AddMessage(msg);
        }
        ++index_;
    }

    // If MIDI file repeat is enabled, reset index when we encounter EOF
    if (IsEof() && Config::GetInstance().GetMidiFileRepeat()) {
        index_ = 0;
        time_ = 0;
    }
}

bool MidiFileIn::IsWanted(const smf::MidiEvent* mev) const {
    if (!mev->isNoteOn() && !mev->isNoteOff()) {
        return false;
    }

    // We can lookup wanted tracks in the tracks_ bool array
    int track = mev->track;
    if (track < 0 || track >= MAX_MIDI_TRACKS || !tracks_[track]) {
        return false;
    }

    // We can lookup wanted channels in the channels_ bool array
    int channel = mev->getChannel();
    if (channel < 0 || channel >= MAX_MIDI_CHANNELS || !channels_[channel]) {
        return false;
    }
    return true;
}

}  // End namespace midistar
