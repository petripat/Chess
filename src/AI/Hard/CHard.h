#ifndef PETRIPAT_CHARD_H
#define PETRIPAT_CHARD_H
#include "../CAI.h"

/**
 * @brief Child class to AL with HARD level of intelligence.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CHard : public CAI {
public:
    /**
     * Constructor of CHard that sets up parent class.
     * @param Color - m_colorOfPieces of AI's pieces
     */
    CHard(EColor Color);
    /**
    * Method that starts up recursion with depth of 3.

    * @param board - m_board on which game is at
    * @return chosen move represented by struct SPieceMove from SPieceMove.h
    */
    SPieceMove getMovementFromAI(const CBoard &board) const override;
    /**
     * Default destructor for class.
     */
    ~CHard() override = default;
    /**
     * Creates unique pointer to instance of CHard in std::unique_ptr<CAI>.
     */
    std::unique_ptr<CAI> cloneUnique() const override;
};

#endif //PETRIPAT_CHARD_H