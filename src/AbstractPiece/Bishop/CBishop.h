#ifndef PETRIPAT_CBISHOP_H
#define PETRIPAT_CBISHOP_H

#include "../CAbstractPiece.h"

#define BISHOP_VALUE 300

/**
 * @brief Class CBishop is child class of CAbstractPiece and represents bishop piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CBishop : public CAbstractPiece {

public:
    /**
    * @return 'B' - pieces name on m_board
    */
    char pieceChar() const override;
    /**
     * Constructor for piece, , sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CBishop(EColor Color);
    /**
     * Virtual method for value of piece on m_board based on strenght of movement and importance of piece.
     * @return int value of piece
     */
    int getValue() const override;
    /**
     * Cloning function for CBishop.
     * @return std::make_shared<CBishop> hidden in std::shared_ptr<CAbstractPiece>
     */
    std::shared_ptr<CAbstractPiece> cloneShared() const override;
    /**
     * Default destructor for piece.
     */
    ~CBishop() override = default;

};



#endif //PETRIPAT_CBISHOP_H
