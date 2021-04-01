

//---------------------------------
//include
//---------------------------------
#include "Game.hpp"

//---------------------------------
//Macro definition(not revealed)
//---------------------------------

//---------------------------------
//Type definition(not revealed)
//---------------------------------

//---------------------------------
//global variable definition
//---------------------------------


//---------------------------------
//function definition
//---------------------------------


//---------------------------------
//main　function
//---------------------------------

int main(int argc, char** argv){
    Game game;
    bool init_success = game.Initialize();
    if(init_success){
        game.RunLoop();
    }
    game.Shutdown();

    return 0;
}