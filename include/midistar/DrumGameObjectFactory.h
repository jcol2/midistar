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

#ifndef MIDISTAR_DRUMGAMEOBJECTFACTORY_H_
#define MIDISTAR_DRUMGAMEOBJECTFACTORY_H_

#include <set>
#include <vector>
#include <SFML/Window.hpp>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The DrumGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class DrumGameObjectFactory : public GameObjectFactory {
 public:
    /**
     * Constructor
     *
     * \param note_speed The falling speed of notes.
     * \param song_notes Unique MIDI notes in the song.
     */
    explicit DrumGameObjectFactory(
            double note_speed
            , const std::set<int>& song_notes);

    /**
     * \copydoc GameObjectFactory::CreateNotePlayEffect()
     */
    virtual GameObject* CreateNotePlayEffect(GameObject* note);

    /**
     * \copydoc GameObjectFactory::CreateInstrument()
     */
    virtual std::vector<GameObject*> CreateInstrument();

    /**
     * \copydoc GameObjectFactory::CreateSongNote()
     */
    virtual GameObject* CreateSongNote(
            int track
            , int chan
            , int note
            , int vel
            , double duration);

    /**
     * \copydoc GameObjectFactory::Init()
     */
    virtual bool Init();

 private:
    static const sf::Color BACKGROUND_COLOUR;  //!< Background colour
    static const int NUM_MIDI_KEYS = 128;  //!< Maximum MIDI key
    static const int INSTRUMENT_HEIGHT = 25;  //!< Instrument height
    static constexpr float INSTRUMENT_HOVER_PERCENTAGE = 0.1f;  //!< The
             //!< percentage of the screen height that instruments will hover

    GameObject* CreateInstrumentNote(int midi_key);  //!< Creates a note for
                                 //!< the instrument with the given MIDI key
    static void GetInstrumentKeyBinding(int midi_key, sf::Keyboard::Key* key,
            bool* ctrl, bool* shift);  //!< Gets instrument key binding

    double note_width_;  //!< Holds the width of song notes
    std::set<int> song_notes_;  //!< Unique MIDI notes in the song
};

}  // End namespace midistar

#endif  // MIDISTAR_DRUMGAMEOBJECTFACTORY_H_
