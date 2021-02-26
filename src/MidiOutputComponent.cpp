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

#include "midistar/MidiOutputComponent.h"

namespace midistar {

MidiOutputComponent::MidiOutputComponent(MidiOut* midi_out)
        : Component{ Component::MIDI_OUTPUT }
        , midi_out_{ midi_out } {
}

MidiOutputComponent::~MidiOutputComponent() {
    delete midi_out_;
}

void MidiOutputComponent::TurnMidiNoteOff(int chan, int note) {
    midi_out_->SendNoteOff(note, chan);
}

void MidiOutputComponent::TurnMidiNoteOn(int chan, int note, int vel) {
    midi_out_->SendNoteOn(note, chan, vel);
}

void MidiOutputComponent::Update(Game*, GameObject*, int delta) {
    midi_out_->Update(delta);
}

}   // End namespace midistar
