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

#include "midistar/InstrumentAutoPlayComponent.h"

#include "midistar/Config.h"
#include "midistar/InstrumentInputHandlerComponent.h"
#include "midistar/NoteInfoComponent.h"

namespace midistar {

InstrumentAutoPlayComponent::InstrumentAutoPlayComponent(
    CollisionCriteria criteria)
        : CollisionHandlerComponent{Component::INSTRUMENT_AUTO_PLAY}
        , collision_criteria_{criteria}
        , colliding_note_{nullptr} {
}

InstrumentAutoPlayComponent::InstrumentAutoPlayComponent()
        : InstrumentAutoPlayComponent(CollisionCriteria::NONE) {
}

void InstrumentAutoPlayComponent::HandleCollisions(
        Game*
        , GameObject* o
        , std::vector<GameObject*> colliding_with) {
    // We only use this component for handling AUTO PLAY, so check if it is
    // enabled
    if (!Config::GetInstance().GetAutomaticallyPlay()) {
        return;
    }

    // Get instrument input handler and note info
    auto inpt_handler = o->GetComponent<InstrumentInputHandlerComponent>(
            Component::INSTRUMENT_INPUT_HANDLER);
    if (!inpt_handler) {
        return;
    }
    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return;
    }

    // Check each collision for collision with a song note
    if (!colliding_note_) {
        for (auto& collider : colliding_with) {
            if (!collider->HasComponent(Component::SONG_NOTE)) {
                continue;
            }
            auto other_note = collider->GetComponent<NoteInfoComponent>(
                    Component::NOTE_INFO);
            if (!other_note) {
                continue;
            }
            if (note->GetKey() == other_note->GetKey()) {
                if (collision_criteria_ == CollisionCriteria::NONE
                    || (collision_criteria_ == CollisionCriteria::CENTRE &&
                        IsInCentre(o, collider))) {
                    colliding_note_ = collider;
                }
            }
        }
    }

    // Check that we are still colliding with the same note.
    // If we don't differentiate between notes, we will ignore and not play
    // overlapping notes.
    if (std::find(colliding_with.begin(), colliding_with.end()
                , colliding_note_) == colliding_with.end()) {
        colliding_note_ = nullptr;
    }

    // If we have a collision with a note, activate instrument
    inpt_handler->SetActive(colliding_note_);
}

bool InstrumentAutoPlayComponent::IsInCentre(
        GameObject* o
        , GameObject* collider) {
    // Get position and size info
    double inst_x, inst_y, inst_w, inst_h;
    o->GetPosition(&inst_x, &inst_y);
    o->GetSize(&inst_w, &inst_h);

    double note_x, note_y, note_w, note_h;
    collider->GetPosition(&note_x, &note_y);
    collider->GetSize(&note_w, &note_h);

    // Check that note is vertically centred in the instrument
    return (note_y >= inst_y
        && ((note_y - inst_y) >= ((inst_h - note_h) / 2.0)));
}

}  // End namespace midistar
