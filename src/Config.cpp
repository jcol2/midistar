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

#include "midistar/Config.h"

#include <iostream>

namespace midistar {

Config Config::instance_;

Config& Config::GetInstance() {
    return instance_;
}

Config::Config()
        : audio_driver_{""}
        , auto_play_{false}
        , full_screen_{false}
        , game_mode_{""}
        , keyboard_first_note_{-1}
        , max_frames_per_second_{-1}
        , midi_file_channels_{}
        , midi_file_name_{""}
        , midi_file_repeat_{false}
        , midi_file_tracks_{}
        , screen_height_{-1}
        , screen_width_{-1}
        , soundfont_path_{""} {
}

const std::string Config::GetAudioDriver() {
    return audio_driver_;
}

bool Config::GetAutomaticallyPlay() {
    return auto_play_;
}

bool Config::GetFullScreen() {
    return full_screen_;
}

const std::string Config::GetGameMode() {
    return game_mode_;
}

int Config::GetMaximumFramesPerSecond() {
    return max_frames_per_second_;
}

std::vector<int> Config::GetMidiFileChannels() {
    return midi_file_channels_;
}

const std::string Config::GetMidiFileName() {
    return midi_file_name_;
}

bool Config::GetMidiFileRepeat() {
    return midi_file_repeat_;
}

int Config::GetMidiFileTicksPerUnitOfSpeed() {
    return MIDI_FILE_TICKS_PER_SPEED;
}

std::vector<int> Config::GetMidiFileTracks() {
    return midi_file_tracks_;
}

int Config::GetMidiOutVelocity() {
    return MIDI_OUT_VELOCITY;
}

double Config::GetNoteFallSpeed() {
    return note_fall_speed_;
}

int Config::GetScreenHeight() {
    return screen_height_;
}

void Config::GetScreenSize(int* width, int* height) {
    *width = GetScreenWidth();
    *height = GetScreenHeight();
}

int Config::GetScreenWidth() {
    return screen_width_;
}

const std::string Config::GetSoundFontPath() {
    return soundfont_path_;
}

int Config::ParseOptions(int argc, char** argv) {
    CLI::App app {};
    InitCliApp(&app);

    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        app.exit(e);
        return 1;
    }
    return 0;
}

void Config::InitCliApp(CLI::App* app) {
    app->option_defaults()->required();
    app->add_option("--audio_driver", audio_driver_, "The audio driver to use "
            "for MIDI output.");
    app->add_option("--auto_play", auto_play_, "Determines whether or not to "
            "automatically play song notes.");
    app->set_config("--config", "config.cfg", "Read a config file.")->required(
            false);
    app->add_option("--game_mode", game_mode_, "Determines the game mode.");
    app->add_option("--full_screen", full_screen_, "Determines whether or not "
           "to enable full-screen mode.");
    app->add_option("--keyboard_first_note", keyboard_first_note_, "The first "
            "MIDI note to bind to the keyboard.");
    app->add_option("--max_fps", max_frames_per_second_, "The maximum number "
            "of times the game will update in one second.");
    app->add_option("--midi_file", midi_file_name_, "The MIDI file to play.");
    app->add_option("--midi_file_channels", midi_file_channels_, "The MIDI "
            "channels to read notes from. -1 will enable all channels.");
    app->add_option("--midi_file_repeat", midi_file_repeat_, "Determines "
            "whether or not to continuously repeat the MIDI file.");
    app->add_option("--midi_file_tracks", midi_file_tracks_, "The MIDI tracks "
            "to read notes from. -1 will enable all tracks.");
    app->add_option("--note_fall_speed", note_fall_speed_, "Determines the "
            "falling speed of notes on the screen. Fall speed is also "
            "dependent on the speed of the MIDI file being played.");
    app->add_option("--screen_height", screen_height_, "The screen height.");
    app->add_option("--screen_width", screen_width_, "The screen width.");
    app->add_option("--soundfont_path", soundfont_path_, "The SoundFont file "
            "to use for MIDI output.");
}

}  // End namespace midistar
