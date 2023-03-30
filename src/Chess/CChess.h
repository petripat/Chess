#ifndef PETRIPAT_CCHESS_H
#define PETRIPAT_CCHESS_H

#include <memory>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "../Configuration/CConfiguration.h"


class CChess {
    std::unique_ptr<CAbstractPlayer> player1; /** pointer to playerPieces with white pieces*/
    std::unique_ptr<CAbstractPlayer> player2; /** pointer to playerPieces with black pieces*/
    static std::vector<std::string> moves; /**vector of moves done during game*/
    CConfiguration settings; /** CConfiguration class for set up of game*/
    static int lastPlayed; /*y* last played player was player1*/
    int lastPlayedForSave; /*last played variable to use for saving*/
//    std::vector<std::string> movesForSave; /**vector of moves to use for saving*/
    ECGameState state; /* game state */
    /**
     * Playing cyclus for game catch up.
     * @param inFile - stream to read moves from
     * @param counter - m_counter of lines read
     * @param player1OnPlay - true - player1 is currently playing
     * @param file - CVisualization class for communication
     */
    void playingCyclus(std::ifstream &inFile, int &counter, bool player1OnPlay, CVisualization &file);
    /**
     * Player on rows game. Prints m_board, how many pieces are taken from both players and check state.
     * In case of CHECKMATE prints m_board and state and then throws "quit" exception.
     * @param file - CVisualisation file for communication
     */
    void playPlayer(CVisualization &file, std::unique_ptr<CAbstractPlayer> &player, std::vector<std::string> &moves);
    /**
     * Check what state it is and ends game or writes out state.
     * @param state - enum EGameState representing state of game from ECGameState.h
     * @return true - state is CHECKMATE
     *       false - state is NO-STATE, CHECK
     */
    bool checkCheckMate(CVisualization &file, const std::string &color);
    /**
     * Prints count of captured pieces for each pointer in sentence 'Color' captured: 'number of captured pieces'
     */
    void printCounterOfPieces(CVisualization & file);
public:
    /**
     * Sets up chess from given file. If error was made during set up writes out what and line and then throws invalid argument.
     * @param inFile - file to read moves from
     * @param file - CVisualization class for communication
     */
    CChess(std::ifstream & inFile, CVisualization & file);
    /**
     * Copy constructor for set up game - does not use settings to set up game.
     * @param rhs - game to copy
     */
    CChess(const CChess &rhs);
    /**
     * Sets up game in settings - playerPieces and his EColor or players.
     */
    CChess(CVisualization & file) : player1(), player2(), settings(player1, player2, file, moves), lastPlayedForSave(0), state(NO_STATE) {
        lastPlayed = 0;
    }
    ~CChess() = default;
     /**
     * Sets up game in settings - playerPieces and his EColor or players.
     */
     CChess() : player1(), player2(), settings(), lastPlayedForSave(0), state(NO_STATE) {
         lastPlayed = 0;
     }
      /**
       * Run method. Ends only with exception-viz CGame start method.
       * @param file - CVisualisation file for communication
       */
      void run(CVisualization & file);

    /**
     * Method to continue game from saved games. Checks who played last and then continues to run.
     * @param file - CVisualisation file for communication
     */
    void continueGame(CVisualization & file);

    /**
     * Sets up game for saving.
     */
    void setForSaving();
    /**
     * Saves made moves to file and in case of mistakes writes out what happened.
     * @param file - CVisualization class for communication
     * @param filename - name of file to save game to
     * @return true - saving successful
     */
    bool saveToFile(CVisualization & file, std::string & filename) const;
    /**Clear vector of moves played.*/
    void clearMoves() {
        moves.clear();
    }
};

#endif //PETRIPAT_CCHESS_H