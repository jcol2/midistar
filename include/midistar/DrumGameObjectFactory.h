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
            , const std::vector<int>& song_notes);

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
    static const int DRUM_HEIGHT = 50;     //!< Drum height
    static constexpr float DRUM_PADDING_PERCENT = 0.1;  //!< Padding percentage
    static const sf::Color INSTRUMENT_FILL_COLOUR;  //!< Drum fill colour
    static constexpr float INSTRUMENT_HOVER_PERCENTAGE = 0.1f;  //!< The
             //!< percentage of the screen height that instruments will hover
    static constexpr float INSTRUMENT_OUTLINE_THICKNESS = -10.0f;  //!< Outline 
                                                        //!< thickness of drums
    static const int MAX_DRUM_WIDTH = 200;  //!< Max drum width
    static const int NUM_DRUM_COLOURS = 6;  //!< Num drum colours
    static const int MAX_NOTE_HEIGHT = 30;  //!< Max note height
    static const int NOTE_HEIGHT_MULTIPLIER = 200;  //!< Determines note height
    static constexpr float NOTE_OUTLINE_THICKNESS = -3.0f;  //!< Outline 
                                                    //!< thickness of notes
    static const int NUM_MIDI_KEYS = 128;  //!< Maximum MIDI key
    static const sf::Color OUTLINE_COLOUR;  //!< Outline colour

    static const sf::Color DRUM_COLOURS[NUM_DRUM_COLOURS];  //!< Holds drum
                                                                  //!< colours

    GameObject* CreateInstrumentNote(int midi_key);  //!< Creates a note for
                                 //!< the instrument with the given MIDI key
    void GetInstrumentKeyBinding(int midi_key, sf::Keyboard::Key* key,
            bool* ctrl, bool* shift);  //!< Gets instrument key binding
    int GetNoteUniqueIndex(int note);  //!< Gets MIDI note index in list of
                                                 //!< unique notes for the song
    double GetXPosition(int note);  //!< Gets the X position of a song
                                                         //!< note / instrument

    double centred_;
    double note_width_;  //!< Holds the width of song notes
    std::vector<int> song_notes_;  //!< Unique MIDI notes in the song
};

}  // End namespace midistar

#endif  // MIDISTAR_DRUMGAMEOBJECTFACTORY_H_
