#ifndef PETRIPAT_CKNIGHT_H
#define PETRIPAT_CKNIGHT_H

#include "../CAbstractPiece.h"
#define KNIGHT_VALUE 300

/**
 * @brief Class CKnight is child class of CAbstractPiece and represents knight piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CKnight : public CAbstractPiece {
public:
    /**
     * Constructor for piece, sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CKnight(EColor Color);
    /**
    * @return 'N' - piece's name on m_board
    */
    char pieceChar() const override;
    /**
     * Virtual method for value of piece on m_board based on strenght of movement and importance of piece.
     * @return int value of piece
     */
    int getValue() const override;
    /**
     * Cloning function for CBishop.
     * @return std::make_shared<CKnight> hidden in std::shared_ptr<CAbstractPiece>
     */
    std::shared_ptr<CAbstractPiece> cloneShared() const override;
    /**
 * Default destructor for piece.
 */
    ~CKnight() override = default;
};



#endif //PETRIPAT_CKNIGHT_H