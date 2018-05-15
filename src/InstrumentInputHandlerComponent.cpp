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

#include "midistar/InstrumentInputHandlerComponent.h"

#include "midistar/Config.h"
#include "midistar/Game.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"

namespace Midistar {

InstrumentInputHandlerComponent::InstrumentInputHandlerComponent()
        : Component(Component::INSTRUMENT_INPUT_HANDLER_COMPONENT)
        , graphics_{nullptr}
        , key_{sf::Keyboard::Key::Unknown}
        , key_down_{false} {
}

void InstrumentInputHandlerComponent::Update(Game* g, GameObject* o) {
    auto note = o->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO_COMPONENT);
    if (!note) {
        return;
    }

    auto other_graphics = o->GetComponent<GraphicsComponent>(
                Component::GRAPHICS_COMPONENT);

    for (const auto& e : g->GetSfEvents()) {
        // We want to ignore Unknown keys as we use this as a sentinel value
        if (e.key.code == sf::Keyboard::Key::Unknown) {
            continue;
        }

        if (e.type == sf::Event::KeyPressed
                && key_ == sf::Keyboard::Key::Unknown) {
            sf::Keyboard::Key needed = Config::GetInstance().
                MidiNoteToKeyboardKey(note->GetKey(), e.key.control
                        , e.key.shift);
            if (needed == e.key.code) {
                key_ = e.key.code;
                key_down_ = true;
            }
        } else if (e.type == sf::Event::KeyReleased && e.key.code == key_) {
            key_ = sf::Keyboard::Key::Unknown;
            key_down_ = false;
        }
    }

    for (const auto& mev : g->GetMidiPortInEvents()) {
        if ((mev.isNoteOn() || mev.isNoteOff()) && mev[1] == note->GetKey()) {
            key_down_ = mev.isNoteOn();
        }
    }

    if (key_down_) {
        if (!other_graphics && graphics_) {
            o->SetComponent(graphics_);
            o->SetComponent(new MidiNoteComponent{
                    true
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()});
       }
    } else if (other_graphics) {
        graphics_ = other_graphics;
        o->RemoveComponent(Component::GRAPHICS_COMPONENT);
        o->SetComponent(new MidiNoteComponent{
                false
                , note->GetChannel()
                , note->GetKey()
                , note->GetVelocity()});
    }
}

}  // End namespace Midistar
