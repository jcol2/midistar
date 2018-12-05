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

#ifndef MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_
#define MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"

namespace midistar {

/**
 * The InstrumentAutoPlayComponent class adds auto play functionality to 
 * instruments.
 */
class InstrumentAutoPlayComponent : public CollisionHandlerComponent {
 public:
     enum class CollisionCriteria {
         NONE = 0,
         CENTRE = 1
     };

     /**
      * Constructor.
      *
      * \param criteria The collision criteria that must be met to start auto 
      * playing a note.
      */
     InstrumentAutoPlayComponent(CollisionCriteria criteria);

     /**
     * Default constructor.
     */
     InstrumentAutoPlayComponent();

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , std::vector<GameObject*> colliding_with);

 private:
    static constexpr double CENTRE_EPSILON = 2.0;

    void HandleCollision(Game* g, GameObject* o, GameObject* collider);
                                                     //!< Handles a collision
    bool IsInCentre(GameObject* o, GameObject* collider);  //!< Checks if a
                                            //!< collision is in the centre of o

    CollisionCriteria collision_criteria_;  //!< Indicates collision criteria to
      //!< that needs to be met before auto play will begin for a specific note.
    GameObject* colliding_note_;  //!< Holds the note we are colliding with. We
                     //!< need to keep track of this to play overlapping notes.
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_
