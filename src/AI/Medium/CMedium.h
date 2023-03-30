#ifndef PETRIPAT_CMEDIUM_H
#define PETRIPAT_CMEDIUM_H
#include "../CAI.h"

/**
 * @brief Child class to AL with MEDIUM level of intelligence.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CMedium : public CAI {
public:
    /**
     * Method that starts up recursion with depth = 2.
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    SPieceMove getMovementFromAI(const CBoard &board) const override;
    /**
    * Constructor of CMedium that sets up parent class.
    * @param Color - m_colorOfPieces of AI's pieces
    */
    CMedium(EColor Color);
    /**
     * Default destructor for class.
     */
    ~CMedium() override = default;
    /**
     * Creates unique pointer to instance of CMedium in std::unique_ptr<CAI>.
     */
    std::unique_ptr<CAI> cloneUnique() const override {
        return std::make_unique<CMedium>(*this);
    }
};

#endif //PETRIPAT_CMEDIUM_H