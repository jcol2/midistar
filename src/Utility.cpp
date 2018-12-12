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

#include "midistar/Utility.h"

namespace midistar {

const std::vector<sf::Keyboard::Key> Utility::qwerty_keys_{
        sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2
        , sf::Keyboard::Key::Num3, sf::Keyboard::Key::Num4
        , sf::Keyboard::Key::Num5, sf::Keyboard::Key::Num6
        , sf::Keyboard::Key::Num7, sf::Keyboard::Key::Num8
        , sf::Keyboard::Key::Num9, sf::Keyboard::Key::Num0
        , sf::Keyboard::Key::Dash, sf::Keyboard::Key::Equal
        , sf::Keyboard::Key::Q, sf::Keyboard::Key::W, sf::Keyboard::Key::E
        , sf::Keyboard::Key::R, sf::Keyboard::Key::T, sf::Keyboard::Key::Y
        , sf::Keyboard::Key::U, sf::Keyboard::Key::I, sf::Keyboard::Key::O
        , sf::Keyboard::Key::P, sf::Keyboard::Key::LBracket
        , sf::Keyboard::Key::RBracket, sf::Keyboard::Key::A
        , sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::F
        , sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::J
        , sf::Keyboard::Key::K, sf::Keyboard::Key::L
        , sf::Keyboard::Key::SemiColon, sf::Keyboard::Key::Quote
        , sf::Keyboard::Key::Z, sf::Keyboard::Key::X, sf::Keyboard::Key::C
        , sf::Keyboard::Key::V, sf::Keyboard::Key::B, sf::Keyboard::Key::N
        , sf::Keyboard::Key::M, sf::Keyboard::Key::Comma
        , sf::Keyboard::Key::Period, sf::Keyboard::Key::Slash
        , sf::Keyboard::Key::Numpad0, sf::Keyboard::Key::Numpad1
        , sf::Keyboard::Key::Numpad2, sf::Keyboard::Key::Numpad3
        , sf::Keyboard::Key::Numpad4, sf::Keyboard::Key::Numpad5
        , sf::Keyboard::Key::Numpad6, sf::Keyboard::Key::Numpad7
        , sf::Keyboard::Key::Numpad8, sf::Keyboard::Key::Numpad9
};

const std::vector<sf::Keyboard::Key>& Utility::GetQwertyKeys() {
    return qwerty_keys_;
}

const sf::Color Utility::DarkenColour(sf::Color c) {
    return Utility::TransformColour(c, Utility::COLOUR_DARKEN_MULTIPLIER);
}

const sf::Color Utility::TransformColour(sf::Color c, double t) {
    c.r *= t;
    c.g *= t;
    c.b *= t;
    return c;
}


}  // End namespace midistar
