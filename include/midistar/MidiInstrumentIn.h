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

#ifndef MIDISTAR_MIDIINSTRUMENTIN_H_
#define MIDISTAR_MIDIINSTRUMENTIN_H_

#include "midistar/MidiMessage.h"
#include "midistar/MidiPortIn.h"

namespace midistar {

/**
 * The MidiIn class provides an interface for MIDI stream readers.
 */
class MidiInstrumentIn : public MidiPortIn {
 public:
    /**
     * \copydoc MidiPortIn.GetMessage(MidiMessage*)
     */
    virtual bool GetMessage(MidiMessage* message);
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIINSTRUMENTIN_H_
