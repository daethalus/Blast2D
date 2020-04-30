#include "game.hpp"

#include <core/logging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

using namespace Blast2D;

int main() {
    Blast2D::Game game;
    game.run();
}
