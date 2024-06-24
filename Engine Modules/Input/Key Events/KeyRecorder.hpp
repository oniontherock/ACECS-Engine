#ifndef __KEY_RECORDER_H__
#define __KEY_RECORDER_H__

#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>
#include <tuple>

#include "SFML/Window/Event.hpp"

#include "KeyEventDefinitions.hpp"


// records input and assigns it a transition type
namespace KeyRecorder {

    // set of keys from the previous frame
    std::unordered_set<KeyName> keyNamesPrev;
    // set of keys from the current frame
    std::unordered_set<KeyName> keyNames;
    std::set<KeyName> registeredKeyNames;

    float mouseWheelMoveAmount;

    KeySet keyEvents{};

    std::unordered_map<KeyName, sf::Keyboard::Key> nameToKeyMap{
        { "Unknown", sf::Keyboard::Unknown },
        { "A", sf::Keyboard::A },
        { "B", sf::Keyboard::B },
        { "C", sf::Keyboard::C },
        { "D", sf::Keyboard::D },
        { "E", sf::Keyboard::E },
        { "F", sf::Keyboard::F },
        { "G", sf::Keyboard::G },
        { "H", sf::Keyboard::H },
        { "I", sf::Keyboard::I },
        { "J", sf::Keyboard::J },
        { "K", sf::Keyboard::K },
        { "L", sf::Keyboard::L },
        { "M", sf::Keyboard::M },
        { "N", sf::Keyboard::N },
        { "O", sf::Keyboard::O },
        { "P", sf::Keyboard::P },
        { "Q", sf::Keyboard::Q },
        { "R", sf::Keyboard::R },
        { "S", sf::Keyboard::S },
        { "T", sf::Keyboard::T },
        { "U", sf::Keyboard::U },
        { "V", sf::Keyboard::V },
        { "W", sf::Keyboard::W },
        { "X", sf::Keyboard::X },
        { "Y", sf::Keyboard::Y },
        { "Z", sf::Keyboard::Z },
        { "Num0", sf::Keyboard::Num0 },
        { "Num1", sf::Keyboard::Num1 },
        { "Num2", sf::Keyboard::Num2 },
        { "Num3", sf::Keyboard::Num3 },
        { "Num4", sf::Keyboard::Num4 },
        { "Num5", sf::Keyboard::Num5 },
        { "Num6", sf::Keyboard::Num6 },
        { "Num7", sf::Keyboard::Num7 },
        { "Num8", sf::Keyboard::Num8 },
        { "Num9", sf::Keyboard::Num9 },
        { "Escape", sf::Keyboard::Escape },
        { "LControl", sf::Keyboard::LControl },
        { "LShift", sf::Keyboard::LShift },
        { "LAlt", sf::Keyboard::LAlt },
        { "LSystem", sf::Keyboard::LSystem },
        { "RControl", sf::Keyboard::RControl },
        { "RShift", sf::Keyboard::RShift },
        { "RAlt", sf::Keyboard::RAlt },
        { "RSystem", sf::Keyboard::RSystem },
        { "Menu", sf::Keyboard::Menu },
        { "LBracket", sf::Keyboard::LBracket },
        { "RBracket", sf::Keyboard::RBracket },
        { "SemiColon", sf::Keyboard::SemiColon },
        { "Comma", sf::Keyboard::Comma },
        { "Period", sf::Keyboard::Period },
        { "Quote", sf::Keyboard::Quote },
        { "Slash", sf::Keyboard::Slash },
        { "BackSlash", sf::Keyboard::BackSlash },
        { "Tilde", sf::Keyboard::Tilde },
        { "Equal", sf::Keyboard::Equal },
        { "Dash", sf::Keyboard::Dash },
        { "Space", sf::Keyboard::Space },
        { "Return", sf::Keyboard::Return },
        { "BackSpace", sf::Keyboard::BackSpace },
        { "Tab", sf::Keyboard::Tab },
        { "PageUp", sf::Keyboard::PageUp },
        { "PageDown", sf::Keyboard::PageDown },
        { "End", sf::Keyboard::End },
        { "Home", sf::Keyboard::Home },
        { "Insert", sf::Keyboard::Insert },
        { "Delete", sf::Keyboard::Delete },
        { "Add", sf::Keyboard::Add },
        { "Subtract", sf::Keyboard::Subtract },
        { "Multiply", sf::Keyboard::Multiply },
        { "Divide", sf::Keyboard::Divide },
        { "Left", sf::Keyboard::Left },
        { "Right", sf::Keyboard::Right },
        { "Up", sf::Keyboard::Up },
        { "Down", sf::Keyboard::Down },
        { "Numpad0", sf::Keyboard::Numpad0 },
        { "Numpad1", sf::Keyboard::Numpad1 },
        { "Numpad2", sf::Keyboard::Numpad2 },
        { "Numpad3", sf::Keyboard::Numpad3 },
        { "Numpad4", sf::Keyboard::Numpad4 },
        { "Numpad5", sf::Keyboard::Numpad5 },
        { "Numpad6", sf::Keyboard::Numpad6 },
        { "Numpad7", sf::Keyboard::Numpad7 },
        { "Numpad8", sf::Keyboard::Numpad8 },
        { "Numpad9", sf::Keyboard::Numpad9 },
        { "F1", sf::Keyboard::F1 },
        { "F2", sf::Keyboard::F2 },
        { "F3", sf::Keyboard::F3 },
        { "F4", sf::Keyboard::F4 },
        { "F5", sf::Keyboard::F5 },
        { "F6", sf::Keyboard::F6 },
        { "F7", sf::Keyboard::F7 },
        { "F8", sf::Keyboard::F8 },
        { "F9", sf::Keyboard::F9 },
        { "F10", sf::Keyboard::F10 },
        { "F11", sf::Keyboard::F11 },
        { "F12", sf::Keyboard::F12 },
        { "F13", sf::Keyboard::F13 },
        { "F14", sf::Keyboard::F14 },
        { "F15", sf::Keyboard::F15 },
        { "Pause", sf::Keyboard::Pause },
    };
    std::unordered_map<sf::Keyboard::Key, KeyName> keyToNameMap;


    std::unordered_map<KeyName, sf::Mouse::Button> nameToButtonMap{
        { "Mouse Left", sf::Mouse::Left },
        { "Mouse Middle", sf::Mouse::Middle },
        { "Mouse Right", sf::Mouse::Right },
    };
    std::unordered_map<sf::Mouse::Button, KeyName> buttonToNameMap;

    inline void setupButtonToNameMap() {
        for (const auto& nameButtonPair : nameToButtonMap) {
            buttonToNameMap.insert({ nameButtonPair.second, nameButtonPair.first });
        }

    }

    inline void setupKeyToNameMap() {
        for (const auto& nameKeyPair : nameToKeyMap) {
            keyToNameMap.insert({ nameKeyPair.second, nameKeyPair.first });
        }
    }

    // sets an InputEvent's transitionType,
    inline KeyEvent getKeyEvent(const KeyName& key) {

        bool activePrev = keyNamesPrev.count(key);
        bool activeNow = keyNames.count(key);

        // we get the keyTransition by getting the difference in key presses between now and last frame
        // this works because:
        // 0 - 1 = -1|Released
        // 1 - 1 = 0|Held
        // 1 - 0 = 1|Pressed
        uint8_t keyTransition = (activeNow - activePrev) + 1;

        return KeyEvent(key, static_cast<KeyTransition>(keyTransition));
    }

    inline bool isKeyNameActiveKeyboard(KeyName name) {
        return sf::Keyboard::isKeyPressed(nameToKeyMap[name]);
    }
    inline bool isKeyNameActiveMouse(KeyName name) {
        return sf::Mouse::isButtonPressed(nameToButtonMap[name]);
    }


    // records every input in "event"
    inline void updateKeys() {

        keyEvents.clear();

        keyNamesPrev = keyNames;
        keyNames.clear();

        for (const KeyName& curRegisteredKeyName : registeredKeyNames) {

            bool keyNameIsActive = false;

            if (nameToKeyMap.count(curRegisteredKeyName) > 0) {
                keyNameIsActive = isKeyNameActiveKeyboard(curRegisteredKeyName);
            }
            else {
                keyNameIsActive = isKeyNameActiveMouse(curRegisteredKeyName);
            }

            if (keyNameIsActive) {
                keyNames.insert(curRegisteredKeyName);;
            }
        }

        std::unordered_set<KeyName> inputsAll = keyNames;
        inputsAll.insert(keyNamesPrev.begin(), keyNamesPrev.end());

        for (const KeyName& curInput : inputsAll) {
            keyEvents.insert(getKeyEvent(curInput));
        }
    }

    inline void registerKeyName(const KeyName& name) {
        registeredKeyNames.insert(name);
    }

    inline void registerKeySet(const KeySet& keySet) {
        for (const KeyEvent& curKeyEvent : keySet) {
            registeredKeyNames.insert(curKeyEvent.keyName);
        }
    }

    inline const KeySet& getKeys() {
        return keyEvents;
    }
}


#endif