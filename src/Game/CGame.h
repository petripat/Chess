#ifndef PETRIPAT_CGAME_H
#define PETRIPAT_CGAME_H
#include <map>
#include <string>
#include "../Chess/CChess.h"
#define TMP_SAVE_TEXT "a9z6q.03.d4fgw.6I7?SeW)"

class CGame {
    std::map<std::string, CChess> savedGames; /**Map of all saved games.*/
    std::string currentGame; /**string name - key in map of currently played game*/
    CVisualization file; /** CVisualization class for communication*/
public:
    CGame() : savedGames(), currentGame(), file() {}
private:
    /**
     * Saves game under new name.
     * @param nameOfGame - name of game to save game under
     * @return TMP_SAVE_TEXT for new game
     */
    std::string saveGame(std::string & nameOfGame);
    /**
     * Method that returns valid name of game based on input.
     * @return name of game at least 2 letters long
     */
    std::string getNameOfGame();
    /**
     * Writes out list of all saved games.
     */
    void pasteSavedGames();

    /**
     * Loads game from list that method prints out - based on number.
     */
    void loadGame();
    /**
     * Checks if it is possible to load game - if any game is saved yet.
     * @return true - yes, there are games to load
     *          no - no other games than currently played
     */
    bool canLoadGame();
    /**
     * Starts new game.
     */
    void startGame();
    /**
     * Method to ask user if he wants to play new game or old, after saving current game. If user wants to continue
     * with other game, it finds out with which.
     * @return true - yes, I want to start new game
     *          false - no, I want to continue in old game
     */
    bool newGame();
    /**
     * Deletes old game from map and sets up new game.
     * @return
     */
   bool gameDone();
    /**
     * Start up method to load game from file.
     * @return true - game successfully set up
     */
    bool loadFromFile();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
    /**
     * Method to save game to file.
     * @return true - game successfully saved
     */
    bool saveToFile();
    /**
     * Ask if player wants to load old game.
     * @param file  - CVisualization game for communication
     * @return  - value of start
     */
    bool askLoadBeforeStart(CVisualization &file);
    /**
     * Method that starts different game after save.
     * @return - value of start
     */
    bool afterSave();
    /**
     * Method that load game from file.
     * @return true - value of start
     */
    bool loadGameFile();
    /**
     * Asks yes or no question.
     * @param file - Cvisualization file for communication
     * @return true - player said yes
     */
    bool yesMethod(CVisualization &file);
public:
/**
     * All exceptions:
     *  char * "quit" - quiting game and catching exception in main
     *  throw 0 = draw FROM CPlayer readMove - getInput
     *      catching in CAbstractPlayer play - parent class, parent method and solving problem
     * throw 1 save game FROM CPlayer readMove - getInput
     * throw 2 load game FROM CPlayer readMove - getInput
     * throw 3 in case of CHECKMATE or STALEMATE as end of currently played game
     * throw 4 in case of saving outside game - !save
     * throw 5 in case of loading outside game - !load
     */
    [[noreturn]] void start();
#pragma clang diagnostic pop

};


#endif //PETRIPAT_CGAME_H
