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

#ifndef MIDISTAR_GAME_H_
#define MIDISTAR_GAME_H_

#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"
#include "midistar/MidiFileIn.h"
#include "midistar/MidiMessage.h"
#include "midistar/MidiOut.h"
#include "midistar/MidiInstrumentIn.h"

namespace midistar {

/**
 * The Game class is the class that drives Midistar.
 */
class Game {
 public:
    /**
     * Constructor.
     */
    Game();

    /**
     * Destructor.
     */
    ~Game();

    /**
     * Adds a new object to the game.
     *
     * \param obj The object to add.
     */
    void AddGameObject(GameObject* obj);

    /**
     * Gets the GameObjectFactory instance in use.
     *
     * \return GameObjectFactory instance.
     */
    GameObjectFactory& GetGameObjectFactory();

    /**
     * Gets all GameObjects.
     *
     * \return All GameObjects.
     */
    const std::vector<GameObject*>& GetGameObjects();

    /**
     * Gets MIDI input port messages for the last tick.
     *
     * \return MIDI messages.
     */
    const std::vector<MidiMessage>& GetMidiInMessages();

    /**
     * Gets SFML events for the last tick.
     *
     * \return SFML events.
     */
    const std::vector<sf::Event>& GetSfEvents();

    /**
     * Gets the SFML window being used for rendering.
     *
     * \return SFML window.
     */
    sf::RenderWindow& GetWindow();

    /**
     * Initializes the game.
     *
     * \return true for success. false for failure.
     */
    bool Init();

    /**
     * Runs the game.
     */
    void Run();

    /**
     * Turns off a MIDI note on the MIDI out port.
     *
     * \param chan MIDI channel.
     * \param note MIDI note.
     */
    void TurnMidiNoteOff(int chan, int note);

    /**
     * Turns on a MIDI note on the MIDI out port.
     *
     * \param chan MIDI channel.
     * \param note MIDI note.
     * \param vel MIDI velocity.
     */
    void TurnMidiNoteOn(int chan, int note, int vel);

 private:
    bool CheckSongNotes();  //!< Determines if the Game has valid song notes
    void CleanUpObjects();  //!< Deletes all GameObjects and their components
    void DeleteObject(GameObject* o);  //!< Deletes a GameObject
    void FlushNewObjectQueue();  //!< Adds new objects to object buffer

    GameObjectFactory* object_factory_;  //!< Holds GameObjectFactory instance
    MidiFileIn midi_file_in_;  //!< MIDI file in instance
    std::vector<MidiMessage> midi_in_buf_;  //!< MIDI input port notes buffer
    MidiOut midi_out_;  //!< MIDI port out instance
    MidiInstrumentIn midi_instrument_in_;  //!< MIDI instrument input
    std::queue<GameObject*> new_objects_;  //!< New GameObjects buffer
    std::vector<GameObject*> objects_;  //!< GameObjects buffer
    std::vector<sf::Event> sf_events_;  //!< SFML events buffer
    sf::RenderWindow window_;  //!< SFML window instance
};

}   // End namespace midistar

#endif  // MIDISTAR_GAME_H_
