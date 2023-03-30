//#pragma once
#include "../CAbstractPlayer.h"
#include "../../AI/Easy/CEasy.h"
#include "../../AI/Medium/CMedium.h"
#include "../../AI/Hard/CHard.h"


/**
 * @brief Class CComputer is child class CAbstractPlayer representing computer playerPieces.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CComputer : public CAbstractPlayer {
    std::unique_ptr<CAI> AI; /** pointer to AI with computer's difficulty */
public:
    CComputer(const CComputer & rhs) : CAbstractPlayer(rhs) {
        AI = rhs.AI->cloneUnique();
    }    /**
     * Method that chooses move from AI.
     * @param file - CVisualization class for communication
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    SPieceMove chooseMove(CVisualization &file) const override;
    /**
     * Constructor for CComputer that sets up AI and saves m_colorOfPieces of playerPieces pieces.
     * @param Color - m_colorOfPieces of players pieces
     * at used for AI set up
     */
    explicit CComputer(EColor Color);
    /**
     * Default destructor for CComputer.
     */
    ~CComputer() override = default;
    /**
     * Method for setting easy difficulty of AI
     */
    void setAIEasy();
    /**
     * Method for setting medium difficulty of AI
     */
    void setAIMedium();
    /**
     * Method for setting hard difficulty of AI
     */
    void setAIHard();
    /**
     * Creates unique pointer to instance of CComputer.
     */
    std::unique_ptr<CAbstractPlayer> cloneUnique() const override {
        return std::make_unique<CComputer>(*this);
    }

};

