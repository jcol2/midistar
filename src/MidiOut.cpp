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

#include <unistd.h>

#include "midistar/MidiOut.h"

#include "midistar/Config.h"

#include <smartpiano/serial/SerialClientImplementation.hpp>
#include <serial/serial.h>

namespace midistar {

MidiOut::MidiOut()
        : a_driver_{nullptr}
        , settings_{nullptr}
        , synth_{nullptr}
        , smart_piano_{nullptr} {
}

MidiOut::~MidiOut() {
    if (a_driver_) {
        delete_fluid_audio_driver(a_driver_);
    }

    if (synth_) {
        delete_fluid_synth(synth_);
    }

    if (settings_) {
        delete_fluid_settings(settings_);
    }

    if (smart_piano_) {
        //delete smart_piano_;
    }
}

bool MidiOut::Init() {
    settings_ = new_fluid_settings();
    fluid_settings_setstr(settings_, "audio.driver"
            , Config::GetInstance().GetAudioDriver().c_str());
    synth_ = new_fluid_synth(settings_);
    if (!synth_) {
        std::cerr << "Error: could not create synth!\n";
    }

    a_driver_ = new_fluid_audio_driver(settings_, synth_);
    if (!a_driver_) {
        std::cerr << "Error: could not initialise audio driver!\n";
    }

    s_font_id_ = fluid_synth_sfload(synth_,
            Config::GetInstance().GetSoundFontPath().c_str(), 1);
    if (s_font_id_ == -1) {
        std::cerr << "Error: could not load SoundFont file!\n";
    }

    auto instrument_mappings = Config::GetInstance()
        .GetMidiOutputInstrumentMapping();
    for (auto kvp : instrument_mappings) {
#ifdef DEBUG
        std::cout << "Setting channel " << kvp.first << " instrument to "
            << kvp.second << "...\n";
#endif

        if (fluid_synth_program_change(synth_, kvp.first, kvp.second)
                == FLUID_FAILED) {
            std::cerr << "Setting channel " << kvp.first << " instrument to "
                << kvp.second << "failed!\n";
        }
    }

    unsigned long baud = 115200;
    auto serial = new serial::Serial("/dev/ttyACM0", baud, serial::Timeout::simpleTimeout(1000));

    std::cout << "Initializing...\n";
    auto serial_client = new smartpianoclient::SerialClientImplementation{ serial };
    if (serial_client->Init())
    {
        std::cerr << "Error initializing serial client!\n";
        throw 1;
    }

    smart_piano_ = new smartpianoclient::SmartPianoClientImplementation { serial_client };
    if (smart_piano_->Init())
    {
        std::cerr << "Error initializing smartpiano client!\n";
        throw 2;
    }
    std::cout << "Waiting for smartpianoclient...\n";
    sleep(10);

    return synth_ && a_driver_ && s_font_id_ != -1;
}

void MidiOut::SendNoteOff(int note, int chan) {
    fluid_synth_noteoff(synth_, chan, note);

    if (smart_piano_) {
        /*
        uint8_t buf[256];
        while (smart_piano_->GetMessage(buf, 256))
        {
            std::cout << "Message: " << buf << "\n";
        }
        */

        smart_piano_->ClearLedColor(note);
        smart_piano_->UpdateLeds();
    }
}

void MidiOut::SendNoteOn(int note, int chan, int velocity) {
    fluid_synth_noteon(synth_, chan, note, velocity);

    if (smart_piano_) {
        /*
        uint8_t buf[256];
        while (smart_piano_->GetMessage(buf, 256))
        {
            std::cout << "Message: " << buf << "\n";
        }
        */

        uint8_t r, g, b, w;
        r = 0;
        g = 0;
        b = 0xff;
        w = 0;

        smart_piano_->SetLedColor(note, r, g, b, w);
        smart_piano_->UpdateLeds();
    }
}

}  // End namespace midistar

