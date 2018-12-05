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

#include "midistar/DrumSongNoteCollisionHandlerComponent.h"

#include <algorithm>

#include "midistar/Config.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

DrumSongNoteCollisionHandlerComponent::DrumSongNoteCollisionHandlerComponent()
        : CollisionHandlerComponent{ Component::NOTE_COLLISION_HANDLER } {
}

void DrumSongNoteCollisionHandlerComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , std::vector<GameObject*> colliding_with) {
    // Handle each collision
    for (auto& collider : colliding_with) {
        HandleCollision(g, o, collider);
    }
}

bool DrumSongNoteCollisionHandlerComponent::HandleCollision(
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

    // Check if the top or bottom edge of the note is inside the instrument
    if ((y > inst_y && y < inst_y + inst_h)
        || (y + height > inst_y && y + height < inst_y + inst_h)) {
        // Make the note invisible (it has been played)
        o->SetComponent(new ResizeComponent{0, 0});
        o->DeleteComponent(GetType());
    }
    return true;
}

}  // End namespace midistar
