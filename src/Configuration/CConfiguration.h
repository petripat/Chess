#ifndef PETRIPAT_CONFIGURATION_H
#define PETRIPAT_CONFIGURATION_H

#include <memory>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include "../Visualization/CVisualization.h"
#include "../AbstractPlayer/Computer/CComputer.h"
#include "../AbstractPlayer/Player/CPlayer.h"

/**
 * @brief Class CConfiguration sets up game before starting.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CConfiguration {

    /**
     * Function to find out if game will be playing 2 players or playerPieces against computer and sets players up.
     * @param player1 - playerPieces with white pieces
     * @param player2 - playerPieces with black pieces
     * @param file - CVisualization class for communication
     * @param moves - saves chosen action
     */
    void setUpPlayers(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2,
                      CVisualization &file, std::vector<std::string> &moves);
    /**
     * Function to find out m_colorOfPieces of computer pieces.
     * @param file - CVisualization class for communication
     * @param moves - saves chosen action
     */
    EColor setUpColor(CVisualization &file, std::vector<std::string> &moves);
    /**
    * If one playerPieces is CComputer this function is called to set up difficulty of AI.
    * @param file - CVisualization class for communication
    * @param player - player to set up difficulty for
     * @param moves - saves chosen action
     */
    void setUpComputerDifficulty(CVisualization &file, std::unique_ptr<CAbstractPlayer> &player,
                                 std::vector<std::string> &moves);
                                 /**
     * Sets up player based on given playerCount
     * @param playerCount  - numbre of players given
     * @param player1 - white player
     * @param player2  - black player
     * @param file - CVisualization file for communication
     * @param moves  - vector of move
     */
     void playersCountSetUp(int playerCount, std::unique_ptr<CAbstractPlayer> &player1,
                                                        std::unique_ptr<CAbstractPlayer> &player2, CVisualization &file,
                                                        std::vector<std::string> &moves);
     /**
     * Sets up players with computer in white color.
     * @param player1
     * @param player2
     */
     void setUpComputerIsWhite(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2);
     /**
      * Sets up players with computer in black color.
      * @param player1
      * @param player2
      */
     void setUpComputerIsBlack(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2);
     /**
      * Sets up difficulty of computer
      * @param diff - string of difficulty
      * @param player - computer player
      * @return true - difficulty set up
      */
     bool computerDifficulty(std::string &diff, std::unique_ptr<CAbstractPlayer> &player);
     /**
      * Sets up two players.
      * @param player1 - white player
      * @param player2 - black player
      */
     void setPlayers(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2);
public:
    /**
     * Implicit constructor for configuration. Only for already set up games.
     */
    CConfiguration() = default;
    /**
     * Sets up game for play. Finds out number of players, m_colorOfPieces of computer if its playing and difficulty of play.
     * @param player1 - first player to be set up with white pieces, if 1 playerPieces is playing, then computer is player1
     *                   when opponentPieces choose black
     * @param player2 - second player to be set up with black pieces, if 1 playerPieces is playing, then computer is player2
     *                   when opponentPieces choose white
     * @param file - file for communication
     * @param moves - saves chosen action
     */
    CConfiguration(std::unique_ptr<CAbstractPlayer> &player1, std::unique_ptr<CAbstractPlayer> &player2,
                   CVisualization &file, std::vector<std::string> &moves);


/**
     * Constructor to set up game from ifstream.
     * @param inFile - stream to set up game from
     * @param counter - m_counter for number of lines read
     * @param player1 - player 1 to be set up
     * @param player2 - player 2 to be set up
     */
    CConfiguration(std::ifstream &inFile, int &counter, std::unique_ptr<CAbstractPlayer> &player1,
                   std::unique_ptr<CAbstractPlayer> &player2, CVisualization &file,
                   std::vector<std::string> &moves);
    std::string getInput(CVisualization &file) const;
};
#endif //PETRIPAT_CONFIGURATION_H

