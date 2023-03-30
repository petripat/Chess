#ifndef PETRIPAT_CQUEEN_H
#define PETRIPAT_CQUEEN_H

#include "../CAbstractPiece.h"
#define QUEEN_VALUE 900

/**
 * @brief Class CQueen is child class of CAbstractPiece and represents queen piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */
class CQueen : public CAbstractPiece {
public:
    /**
     * Constructor for piece, sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CQueen(EColor Color);
    /**
    * @return 'Q' - pieces name on m_board
    */
    char pieceChar() const override;
    /**
     * Virtual method for value of piece on m_board based on strenght of movement and importance of piece.
     * @return int value of piece
     */
    int getValue() const override;
    /**
     * Cloning function for CBishop.
     * @return std::make_shared<CKing> hidden in std::shared_ptr<CAbstractPiece>
     */
    std::shared_ptr<CAbstractPiece> cloneShared() const override;
    /**
     * Default destructor for piece.
     */
    ~CQueen() override = default;

};


#endif //PETRIPAT_CQUEEN_H