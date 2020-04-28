#ifndef BLAST2D_INPUT_HPP
#define BLAST2D_INPUT_HPP

#include "key_state.hpp"
#include "keys.hpp"
#include <core/logging/easylogging++.h>
#include <functional>

namespace Blast2D{

    class Input {
    private:
        std::map<Keys, KeyState> keyStates;
        std::map<Keys, KeyState> keyStatesCache;
        std::function<KeyState(Keys key)> keyListener;
        Input() {
            keyListener = [](Keys key) {
                LOG(INFO) << "ALERT! No key listener registered";
                return KeyState::Release;
            };
        }
    public:
        Input(const Input&) = delete;
        Input operator=(const Input&) = delete;

        static Input& getInstance() {
            static Input input;
            return input;
        }
        bool isActionPressed(std::string action) {

        }

        bool isActionHolding(std::string action) {

        }

        bool isKeyPressed(Keys key) {
            return getKeyState(key) == KeyState::Press;
        }
        bool isKeyHolding(Keys key) {
            return getKeyState(key) == KeyState::Press || getKeyState(key) == KeyState::Hold;
        }

        KeyState getKeyState(Keys key) {
            auto lastState = keyStates[key];
            auto state = keyListener(key);
            keyStatesCache[key] = state;
            if (lastState == KeyState::Press && state == KeyState::Press) {
                return KeyState::Hold;
            }
            return state;
        }

        void registerKeyListener(std::function<KeyState(Keys key)> _keyListener) {
            keyListener = _keyListener;
        }
    };

    static Input &input = Input::getInstance();
}

#endif
