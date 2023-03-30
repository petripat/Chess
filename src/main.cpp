#include "Game/CGame.h"

int main() {
    srand(time(nullptr));
    try{
        CGame game;
        game.start();
    }
    catch (const char* exception) {
    }
    std::cout << "Exiting application..." << std::endl;
    return 0;
}
