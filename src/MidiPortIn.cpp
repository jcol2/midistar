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

#include "midistar/MidiPortIn.h"

#include <vector>

namespace midistar {

MidiPortIn::MidiPortIn()
        : midi_in_{nullptr} {
}

bool MidiPortIn::Init() {
    midi_in_ = new RtMidiIn();

    try {
        midi_in_->openPort(0, "midistar Input");
    } catch (...) {
        std::cerr << "Warning: error opening MIDI input port. MIDI input "
            << "disabled.\n";
    }
    midi_in_->ignoreTypes(false, false, false);
    return midi_in_;
}

void MidiPortIn::Tick() {
    if (!midi_in_) {
        return;
    }

    std::vector<unsigned char> message;
    while (true) {
        double stamp = midi_in_->getMessage(&message);
        if (message.size() == 0) {
            break;
        }
        AddMessage({message, stamp});
    }
}

}  // End namespace midistar
