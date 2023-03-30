#ifndef PETRIPAT_CEASY_H
#define PETRIPAT_CEASY_H

#include "../CAI.h"

/**
 * @brief Child class to AL with EASY level of intelligence.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CEasy : public CAI {
public:
    /**
     * Constructor of CEasy that sets up parent class.
     * @param Color - m_colorOfPieces of AI's pieces
     */
    CEasy(EColor Color);
    /**
     * Method that starts up recursion with depth = 1.
     * @param board - m_board on which game is at
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    SPieceMove getMovementFromAI(const CBoard &board) const override;
    /**
     * Default destructor for class.
     */
    ~CEasy() override = default;
    /**
     *Creates unique pointer to instance of CEasy in std::unique_ptr<CAI>.
     */
    std::unique_ptr<CAI> cloneUnique() const override {
        return std::make_unique<CEasy>(*this);
    }
};

#endif //PETRIPAT_CEASY_H