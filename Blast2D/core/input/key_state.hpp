#ifndef KEY_STATE_HPP
#define KEY_STATE_HPP

namespace Blast2D {
    enum class KeyState : unsigned int {
        Release = 0,
        Press = 1,
        Repeat = 2,
        Hold = 4,
    };
}



#endif



