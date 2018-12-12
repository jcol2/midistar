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

#include "midistar/InvertColourComponent.h"

namespace midistar {

InvertColourComponent::InvertColourComponent(char inv)
        : Component{INVERT_COLOUR}
        , inv_{inv} {
}

InvertColourComponent::InvertColourComponent()
        : InvertColourComponent{DEFAULT_INVERSION} {
}

void InvertColourComponent::Update(Game*, GameObject* o, int) {
    sf::Color colour;
    auto* rect = o->GetDrawformable<sf::RectangleShape>();    
    if (rect) {
        colour = rect->getFillColor();
    }

    auto* circle = o->GetDrawformable<sf::CircleShape>();
    if (circle) {
        colour = circle->getFillColor();
    }
        
    for (auto &b : {&colour.r, &colour.g, &colour.b}) {
        *b ^= inv_;
    }
    
    if (rect) {
        rect->setFillColor(colour);
    }
    if (circle) {
        circle->setFillColor(colour);
    }

    o->DeleteComponent(GetType());
}

}   // End namespace midistar
