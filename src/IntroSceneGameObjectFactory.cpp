/*
 * midistar
 * Copyright (C) 2018-2019 Jeremy Collette.
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

#include "midistar/IntroSceneGameObjectFactory.h"

#include <filesystem>
#include <string>

#include "midistar/DrumSceneFactory.h"
#include "midistar/Game.h"
#include "midistar/KeepAliveComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuFactory.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/MenuItemComponent.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/TextFactory.h"
#include "midistar/Version.h"

namespace fs = std::experimental::filesystem;

namespace midistar {

// TODO(@jeremy): this should be in the scene factory
IntroSceneGameObjectFactory::IntroSceneGameObjectFactory() {
}

std::vector<GameObject*> IntroSceneGameObjectFactory::CreateGameObjects(
        sf::RenderWindow* window) {
    // TODO(@jeremy): add font to project
    // TODO(@jeremy): resize based on screen size

    // Create menu
    auto font = new sf::Font();
    if (!font->loadFromFile("PixelMiners-KKal.otf")) {
        throw "Could not load font!";
    }

    auto factory = MenuFactory{ *font, window };
    auto piano_menu = factory.CreateMenu("Song selection", 25.0f)
        .SetTitleFontSize(35);
    auto drum_menu = factory.CreateMenu("Song selection", 25.0f)
        .SetTitleFontSize(35);

    // TODO(@jeremy): add subtitle functionality to menu builder
    auto scanning_game_object = CreateScanningTextGameObject(*font);
    piano_menu.GetGameObject()->AddChild(scanning_game_object);
    drum_menu.GetGameObject()->AddChild(scanning_game_object);

    // Add menu items
    auto menu_item_text = std::vector<std::string*>{ };
    std::string path = ".";
    for (const auto & entry : fs::directory_iterator(path)) {
        auto path_string = entry.path().string();
        if (path_string.find(".mid") != std::string::npos) {
            piano_menu.AddMenuItem(
                factory.CreateMenuItem(path_string)
                    .SetOnSelect(([path_string](Game* g, GameObject*, int) {
                        Scene* new_scene = nullptr;
                        auto piano_scene_factory = PianoSceneFactory{
                            path_string };
                        if (!piano_scene_factory.Create(
                            g
                            , &g->GetWindow()
                            , &new_scene)) {
                            throw "Scene creation failed";
                        }
                        g->SetScene(new_scene);
                    }))
                    .SetFontSize(20));

            drum_menu.AddMenuItem(
                factory.CreateMenuItem(path_string)
                .SetOnSelect(([path_string](Game* g, GameObject*, int) {
                    Scene* new_scene = nullptr;
                    auto drum_scene_factory = DrumSceneFactory{ path_string };
                    if (!drum_scene_factory.Create(
                        g
                        , &g->GetWindow()
                        , &new_scene)) {
                        throw "Scene creation failed";
                    }
                    g->SetScene(new_scene);
                }))
                .SetFontSize(20));
        }
    }

    auto main_menu =
        factory.CreateMenu("midistar", 35.0f)
        .SetTitleColour(sf::Color::Green)
        .AddMenuItem(factory.CreateMenuItem("1. Piano")
            .SetOnSelect(piano_menu))
        .AddMenuItem(factory.CreateMenuItem("2. Drums")
            .SetOnSelect(drum_menu))
        .AddMenuItem(factory.CreateMenuItem("0. Exit")
            .SetOnSelect([](Game* g, GameObject*, int) {
                g->Exit();
            }))
        .SetTitleFontSize(50);

    auto copyright = CreateCopyrightTextGameObject(*font);
    main_menu.GetGameObject()->AddChild(copyright);

    auto version = CreateVersionTextGameObject(*font);
    main_menu.GetGameObject()->AddChild(version);

    auto game_objects = std::vector<GameObject*>{ main_menu.GetGameObject() };
    return game_objects;
}

GameObject* IntroSceneGameObjectFactory::CreateScanningTextGameObject(
        const sf::Font& font) {
    auto subtitle_string = new std::string{ "Scanning directory "
        + fs::current_path().string() };
    TextFactory text_builder{ *subtitle_string, font };
    text_builder.SetFontSize(20);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::MIN);
    text_builder.SetYPosition(TextFactory::MIN, 80);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneGameObjectFactory::CreateCopyrightTextGameObject(
        const sf::Font& font) {
    auto copyright_string = new std::string{
        "Copyright (c) Jeremy Collette 2018-2020" };
    TextFactory text_builder{ *copyright_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::CENTER);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneGameObjectFactory::CreateVersionTextGameObject(
        const sf::Font& font) {
    auto version_string = new std::string{ MIDISTAR_VERSION };
    TextFactory text_builder{ *version_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::MAX);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

}  // End namespace midistar
