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

#ifndef MIDISTAR_DELETEOFFSCREENCOMPONENT_H_
#define MIDISTAR_DELETEOFFSCREENCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The DeleteOffscreenComponent class requests the deletion of its owner when
 * the owner's position is off-screen past some threshold.
 */
class DeleteOffscreenComponent : public Component {
 public:
    /**
     * Constructor.
     */
    DeleteOffscreenComponent();

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    static const int THRESHOLD = 500;  //!< X/Y off-screen threshold
};

}   // End namespace midistar

#endif  // MIDISTAR_DELETEOFFSCREENCOMPONENT_H_
