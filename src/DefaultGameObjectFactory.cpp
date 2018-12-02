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

#include "midistar/DefaultGameObjectFactory.h"

#include <cassert>

#include "midistar/CollidableComponent.h"
#include "midistar/Config.h"
#include "midistar/DeleteOffscreenComponent.h"
#include "midistar/Game.h"
#include "midistar/InstrumentCollisionHandlerComponent.h"
#include "midistar/InstrumentComponent.h"
#include "midistar/InstrumentInputHandlerComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/PhysicsComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/SongNoteCollisionHandlerComponent.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/Utility.h"
#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

const sf::Color DefaultGameObjectFactory::BACKGROUND_COLOUR{0, 0, 0};

DefaultGameObjectFactory::DefaultGameObjectFactory(double note_speed)
        : GameObjectFactory{note_speed, BACKGROUND_COLOUR}
        , note_width_{Config::GetInstance().GetScreenWidth() /
            static_cast<double>(NUM_MIDI_KEYS)} {
}

GameObject* DefaultGameObjectFactory::CreateNotePlayEffect(GameObject*) {
    // NOTE: This feature is not implemented for the DefaultGameObjectFactory.
    auto* rect = new sf::RectangleShape{};
    return new GameObject{rect, 0, 0, 0, 0};
}

std::vector<GameObject*> DefaultGameObjectFactory::CreateInstrument() {
    std::vector<GameObject*> result;
    for (int key = 0; key < NUM_MIDI_KEYS; ++key) {
        result.push_back(CreateInstrumentNote(key));
    }
    return result;
}

GameObject* DefaultGameObjectFactory::CreateSongNote(
        int track
        , int chan
        , int note
        , int vel
        , double duration) {
    // Create underlying shape
    double x = note * note_width_;
    double height = duration * 1000 * GetNoteSpeed();
    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            note_width_), static_cast<float>(height)}};

    // Create GameObject
    // Height is derived by note duration and speed (note should move its
    // entire height over its duration).
    auto song_note = new GameObject{rect, x, -height, note_width_, height};

    // Add components
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new CollidableComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, chan, note, vel});
    song_note->SetComponent(new PhysicsComponent{0, GetNoteSpeed()});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new VerticalCollisionDetectorComponent{});
    song_note->SetComponent(new SongNoteCollisionHandlerComponent{});
    return song_note;
}

GameObject* DefaultGameObjectFactory::CreateInstrumentNote(int note) {
    // Create underlying shape
    double x = note * note_width_;
    double y = Config::GetInstance().GetScreenHeight() - INSTRUMENT_HEIGHT -
        (Config::GetInstance().GetScreenHeight() * INSTRUMENT_HOVER_PERCENTAGE);
    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            note_width_), static_cast<float>(INSTRUMENT_HEIGHT)}};;
    rect->setFillColor(sf::Color::Red);

    // Create GameObject
    auto ins_note = new GameObject{rect, x, y, note_width_, static_cast<float>(INSTRUMENT_HEIGHT)};

    // Get key binding
    sf::Keyboard::Key key;
    bool ctrl, shift;
    GetInstrumentKeyBinding(note, &key, &ctrl, &shift);

    // Add components
    ins_note->SetComponent(new InstrumentComponent{});
    ins_note->SetComponent(new NoteInfoComponent{-1, 0, note
            , Config::GetInstance().GetMidiOutVelocity()});
    ins_note->SetComponent(new InstrumentInputHandlerComponent{key, ctrl
            , shift});
    ins_note->SetComponent(new VerticalCollisionDetectorComponent{});
    ins_note->SetComponent(new InstrumentCollisionHandlerComponent{});
    return ins_note;
}

void DefaultGameObjectFactory::GetInstrumentKeyBinding(
        int midi_key
        , sf::Keyboard::Key* key
        , bool* ctrl
        , bool* shift) {
    const std::vector<sf::Keyboard::Key>& keys = Utility::GetQwertyKeys();
    int num_keys = keys.size();

    // We don't have enough unique keys to assign each instrument one key, so
    // we break the key bindings up in to three equal sections. The first
    // section bindings use a key plus the ctrl modifier. The second section
    // bindings use just a key. The third section bindings use a key plus the
    // shift modifier. This way we can cover every single MIDI note with the
    // QWERTY keys (alphanumeric and a few punctuation keys).
    assert(num_keys * 3 >= NUM_MIDI_KEYS);

    // Get the key
    *key = keys[midi_key % num_keys];
    // Determine if we are in the first section
    *ctrl = midi_key < num_keys;
    // Determine if we are in the third section
    *shift = midi_key >= num_keys * 2;
}

bool DefaultGameObjectFactory::Init() {
    // We have nothing to initialise...
    return true;
}

}  // End namespace midistar
