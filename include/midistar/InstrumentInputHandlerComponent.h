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

#ifndef MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_
#define MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_

#include <SFML/Graphics.hpp>

#include "midistar/Component.h"

namespace midistar {

/**
 * The InstrumentInputHandlerComponent handles input for instruments.
 *
 * More specifically, it polls keyboard and MIDI input port events and
 * activates the instrument when applicable. While active, the instrument
 * plays a MIDI note and interacts with falling song notes on the screen.
 */
class InstrumentInputHandlerComponent : public Component {
 public:
     /**
      * Constructor.
      *
      * \param key The keyboard key to bind this instrument to.
      * \param ctrl Indicates whether or not the control key must be pressed
      * in conjunction with the key binding.
      * \param shift Indicates whether or not the shift key must be pressed
      * in conjunction with the key binding.
      */
     InstrumentInputHandlerComponent(
             sf::Keyboard::Key key
            , bool ctrl
            , bool shift);

     /**
      * Indicates if a note has been played by this instrument this tick.
      *
      * \returns bool True indicates a note has been played. False indicates
      * otherwise.
      */
     bool GetNotePlayed();

     /**
      * Allows other components to activate instrument.
      *
      * \param active True activates instrument. False leaves instrument
      * unchanged.
      */
     void SetActive(bool active);

     /**
      * Indicates if a note has been played by this instrument this tick.
      *
      * \param note_played True indicates a note has been played. False
      * indicates otherwise.
      */
     void SetNotePlayed(bool note_played);

     /**
      * \copydoc Component::Update()
      */
     virtual void Update(Game* g, GameObject* o, int delta);


 private:
     const bool ctrl_;  //!< Determines if the 'control' modifier has to be
                                  //!< pressed in conjunction with key binding
     const sf::Keyboard::Key key_;  //!< The key bound to this instrument
     bool key_down_;  //!< Determines if the instrument is currently activated
     bool note_played_;  //!< Indicates if a note has been played within the
                                                                  //!< last tick
     bool set_active_;  //!< Determines if the instrument has been activated
                                                                //!< externally
     const bool shift_;  //!< Determines if the 'shift' modifier has to be
                                  //!< pressed in conjunction with key binding
     bool was_active_;  //!< Determines if the instrument was active last tick
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_
