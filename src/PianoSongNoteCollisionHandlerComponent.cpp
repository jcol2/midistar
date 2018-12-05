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

#include "midistar/PianoSongNoteCollisionHandlerComponent.h"

#include <algorithm>

#include "midistar/Config.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

PianoSongNoteCollisionHandlerComponent::PianoSongNoteCollisionHandlerComponent()
        : CollisionHandlerComponent{Component::NOTE_COLLISION_HANDLER}
        , grinding_{nullptr} {
}

void PianoSongNoteCollisionHandlerComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , std::vector<GameObject*> colliding_with) {
    // Handle each collision
    GameObject* valid_collider = nullptr;
    for (auto& collider : colliding_with) {
         if (HandleCollision(g, o, collider)) {
            valid_collider = collider;
        }
    }

    // If we are being played, let's add a grinding effect
    if (valid_collider) {
        if (grinding_) {
            return;
        }
        grinding_ = g->GetGameObjectFactory().CreateNotePlayEffect(
                valid_collider);
        g->AddGameObject(grinding_);
    } else if (grinding_) {  // Otherwise remove the grinding effect
        grinding_->SetRequestDelete(true);
        grinding_ = nullptr;
    }
}

bool PianoSongNoteCollisionHandlerComponent::HandleCollision(
        Game* g
        , GameObject* o
        , GameObject* collider) {
    // We only want to handle collisions with instruments
    if (!collider->HasComponent(Component::INSTRUMENT)) {
        return false;
    }

    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return false;
    }
    auto other_note = collider->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
    // Check it's the correct instrument - we may collide with
    // neighbouring instruments if they overlap on the screen.
    if (!other_note || other_note->GetKey() != note->GetKey()) {
        return false;
    }

    // Get position and size info
    double x, y, width, height;
    o->GetPosition(&x, &y);
    o->GetSize(&width, &height);
    double inst_x, inst_y, inst_w, inst_h;
    collider->GetPosition(&inst_x, &inst_y);
    collider->GetSize(&inst_w, &inst_h);

    // Check if the note is in the playable part of the insrtument.
    if (y > inst_y + NOTE_COLLISION_CUTOFF) {
        return false;
    }

    // If the bottom of the note is outside the playable part, separate the
    // part below the cutoff in to a different (unplayable) note. This section
    // of the note has been missed.
    if (y + height > inst_y + NOTE_COLLISION_CUTOFF) {
        auto note = o->GetComponent<NoteInfoComponent>(
                Component::NOTE_INFO);
        if (!note) {
            return true;
        }

        GameObject* half = g->GetGameObjectFactory().CreateSongNote(
                    note->GetTrack()
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()
                    , 0.1);

        // We don't want complete note behaviour - this is an
        // unplayable note
        half->DeleteComponent(Component::NOTE_COLLISION_HANDLER);
        half->SetPosition(x, inst_y + NOTE_COLLISION_CUTOFF);
        half->SetSize(width, (y + height) - (inst_y
                    + NOTE_COLLISION_CUTOFF));
        g->AddGameObject(half);
    }

    // Now we are guaranteed to have a note that ends before the bottom
    // of the instrument (see above).
    //
    // If the top of the note is before the instrument:
    if (y < inst_y) {
        // Resize the note so that it is intersecting with the instrument by
        // one pixel
        o->SetComponent(new ResizeComponent{width, inst_y-y + 1});
    } else {  // Otherwise 'o' is now purely within the instrument and
             // can be removed.
        o->SetComponent(new ResizeComponent{0, 0});
    }
    return true;
}

}  // End namespace midistar
