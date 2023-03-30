//#pragma once
#include "../CAbstractPlayer.h"
#include <sstream>

class CPlayer : public CAbstractPlayer {
    /**
     * Main method for communication with player and choosing playerPieces's next valid move.
     * @param file - CVisualization class for communication
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    SPieceMove chooseMove(CVisualization &file) const override;
    /**
     * Method for reading next move.
     * @param file - CVisualization class for communication
     * @return
     */
    SPieceMove readMove(CVisualization &file) const;
public:
    /**
    * Constructor for CPlayer.
    * @param Color - m_colorOfPieces of players pieces
    */
    explicit CPlayer(EColor Color);
    /**
     * Default destructor for CPlayer.
     */
    ~CPlayer() override = default;

    static std::string getInput(CVisualization &file);
    /**
     * Creates unique pointer to instance of CComputer.
     */
    std::unique_ptr<CAbstractPlayer> cloneUnique() const override;
};
