#ifndef PETRIPAT_CROOK_H
#define PETRIPAT_CROOK_H
#include "../CAbstractPiece.h"

#define ROOK_VALUE 500

/**
 * @brief Class CRook is child class of CAbstractPiece and represents rook piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */
class CRook : public CAbstractPiece {
public:
    /**
    * @return 'R' - pieces name on m_board
    */
    char pieceChar() const override;
    /**
     * Constructor for piece, sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CRook(EColor Color);
    /**
    * Virtual method for value of piece on m_board based on strenght of movement and importance of piece.
    * @return int value of piece
    */
    int getValue() const override;
    /**
     * Cloning function for CBishop.
     * @return std::make_shared<CRook> hidden in std::shared_ptr<CAbstractPiece>
     */
    std::shared_ptr<CAbstractPiece> cloneShared() const override;
    /**
    * Default destructor for piece.
    */
    ~CRook() override = default;
    /**
     * @return rook did not move during game
     */
    bool canCastle() const override {
        return m_realStartPos;
    }

};
#endif //PETRIPAT_CROOK_H