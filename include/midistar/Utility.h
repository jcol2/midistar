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

#ifndef MIDISTAR_UTILITY_H_
#define MIDISTAR_UTILITY_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace midistar {

/**
 * The Utility class provides static functionality that may be useful to
 * multiple classes or does not belong anywhere else.
 */
class Utility {
 public:
    /**
     * Darkens a colour.
     *
     * \param c The colour to darken.
     * \return A darker colour.
     */
    static const sf::Color Utility::DarkenColour(sf::Color c);

    /**
     * Gets a list of keyboard keys in QWERTY order.
     *
     * \return Keyboard keys in QWERTY order.
     */
    static const std::vector<sf::Keyboard::Key>& GetQwertyKeys();

    /**
     * Transforms a colour by a given multiplier.
     *
     * \param c The colour to transform.
     * \param t The factor to multiply R, G, and B values by.
     * \return A transformed colour.
     */
    static const sf::Color Utility::TransformColour(sf::Color c, double t);

 private:
     static constexpr float COLOUR_DARKEN_MULTIPLIER = 0.4f;  //!< Multiple R,
               //!< G, and B colour channels by this multiplier during darkening

    static const std::vector<sf::Keyboard::Key> qwerty_keys_;  //!< Holds a list
                                                   //!< of keys in QWERTY order
};

}  // End namespace midistar


#endif   // MIDISTAR_UTILITY_H_
