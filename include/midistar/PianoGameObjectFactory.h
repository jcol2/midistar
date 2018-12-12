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

#ifndef MIDISTAR_PIANOGAMEOBJECTFACTORY_H_
#define MIDISTAR_PIANOGAMEOBJECTFACTORY_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The PianoGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class PianoGameObjectFactory : public GameObjectFactory {
 public:
   /**
    * Constructor
    *
    * \param note_speed Used to calculate the falling speed of notes.
    */
    explicit PianoGameObjectFactory(double note_speed);

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
    static constexpr float BLACK_WIDTH_MULTIPLIER = 0.5f;  //!< Black keys and
                        //! notes have a different width to white counterparts
    static const int GRINDING_FRAMES_PER_SECOND = 18;  //!< Grinding sprite FPS
    static const sf::Color GRINDING_SPRITE_COLOUR;  //!< Grinding sprite colour
    static constexpr float GRINDING_SPRITE_SIZE = 64.0f;  //!< Sprite size
    static constexpr float KEY_HOVER_PERCENTAGE = 0.1f;  //!< Percentage of the
                                  //!< screen height that the piano will hover
    static constexpr float NOTE_OUTLINE_THICKNESS = -2.0f;  //!< Note outline
    static const char NOTES_PER_OCTAVE = 12;  //!< Notes in an octave
    static const char NUM_BLACK_KEYS = 36;  //!< Num black keys on a piano
    static const char NUM_PIANO_KEYS = 88;  //!< Total num keys on a piano
    static const char NUM_TRACK_COLOURS = 6;  //!< Number of track colours
    static const char NUM_WHITE_KEYS = NUM_PIANO_KEYS - NUM_BLACK_KEYS;
                                                //!< Num white keys on a piano
    static const bool OCTAVE_BLACK_KEYS[NOTES_PER_OCTAVE];  //!< Black key
                                                      //!< lookup in an octave
    static const char OCTAVE_KEY_TO_WHITE_KEY[NOTES_PER_OCTAVE];  //!< Converts
                                      //!< a key index to the closest white key
    static const char PIANO_FIRST_MIDI_KEY = 21;  //!< First MIDI key on a
                                                                    //!< piano
    static const int WHITE_KEY_HEIGHT = 150;  //!< White key height
    static constexpr float WHITE_KEY_OUTLINE_THICKNESS = -1.0f;  //!< Key
                                                                  //!< outline
    static const char WHITE_KEYS_PER_OCTAVE = 7;  //!< White keys in an octave

    // These are out of order because they depend on other constants
    static constexpr float BLACK_KEY_OUTLINE_THICKNESS =
        WHITE_KEY_OUTLINE_THICKNESS / 2.0;  //!< Black key outline thickness
    static const int BLACK_KEY_HEIGHT = WHITE_KEY_HEIGHT * 0.65f;  //!< Black
                                                      //!< key height in pixels
    static constexpr const char* GRINDING_TEXTURE_PATH = "assets/grinding.png";
                                            //!< Path to metal grinding texture
    static const sf::Color MIDI_TRACK_COLOURS[NUM_TRACK_COLOURS];  //!< Holds
                                                        //!< MIDI track colours

    static sf::Color GetTrackColour(int midi_track);  //!< Get colour for track
    static void GetInstrumentKeyBinding(int midi_key, sf::Keyboard::Key* key,
            bool* ctrl, bool* shift);  //!< Gets instrument key binding
    static int GetWhiteKeyIndex(int midi_key);  //!< Gets the index of the
                                    //!< closest white piano key to a MIDI key
    static bool IsBlackKey(int midi_key);  //!< Determines if a MIDI key
                                        //!< correlates with a black piano key

    double CalculateXPosition(int midi_key);  //!< Calculates note / instrument
                                                                //!< X position
    GameObject* CreateInstrumentNote(int midi_key);  //!< Creates a note for
                                                                 //!< the piano

    sf::Texture grinding_texture_;  //!< Holds texture to represent metal grind
    double white_width_;  //!< Holds the width of white keys and notes
};

}  // End namespace midistar

#endif  // MIDISTAR_PIANOGAMEOBJECTFACTORY_H_
