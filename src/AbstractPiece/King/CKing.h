#ifndef PETRIPAT_CKING_H
#define PETRIPAT_CKING_H

#include "../CAbstractPiece.h"

#define KING_VALUE 800

/**
 * @brief Class CKing is child class of CAbstractPiece and represents king piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CKing : public CAbstractPiece {
public:
    /**
     * @return true
     */
    bool isKing() const override;
    /**
    * @return 'K' - piece's name on m_board
    */
    char pieceChar() const override;
    /**
     * Constructor for piece, sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CKing(EColor Color);
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
    ~CKing() override = default;
    /**
     * Method for all king moves - uses method generateMoves from parent and checks for possibility of castling
     * @param from - position of piece on m_board
     * @param chessBoard - class with ChessBoard and vectors of white and black pieces
     * @param lastMove - m_lastMove made on m_board
     * @return vector of structs SPieceMove representing all possible moves of king
     */
    std::vector<SPieceMove> getKingMoves(const CCoordinates &from, const CChessBoard &chessBoard, const SPieceMove &lastMove) const ;

private:
    /**
     * Method checking possibility of castling move.
     * @param rook1 - position of first rook
     * @param rook2  - position of second rook
     * @param from - original position of king
     * @param board - m_board on which is piece moving
     * @param validMoves  - vector represented of struct SPieceMove from SPieceMove.h with saved valid movements of piece
     * @param lastMove  - m_lastMove made on m_board
     */
    void checkCastling(const CCoordinates &rook1, const CCoordinates &rook2, const CCoordinates &from,
                       const CChessBoard &board, std::vector<SPieceMove> &validMoves, const SPieceMove &lastMove) const;

    /**
     * Method checking if all tiles between from and to are empty.
     * @param from - position to check from
     * @param to - position to check to
     * @param board - m_board on which pieces are on
     * @return true for no pieces are between
     *         false - piece is on m_board between from to to
     */
    bool tilesAreEmpty(const CCoordinates &from, const CCoordinates &to,
                           const ChessBoard &board) const ;
    /**
     * Method that checks is king will be during castling movement in check.
     * @param fromKingPos - position king is on
     * @param toKingPos - position for king to be moved in
     * @param chessBoard - class with ChessBoard and vectors of white and black pieces
     * @param lastMove - m_lastMove on chessBoard
     * @return true for king was not in check
     *          false at at least one tile, king was in check
     */
    bool checkKingIsNotInCheck(const CCoordinates &fromKingPos, const CCoordinates &toKingPos, const CChessBoard &chessBoard,
                               const SPieceMove &lastMove) const;
    /**
     * Method for control of check check of king on specific position.
     * @param coordinatesOfKing - position king is on
     * @param board - class with ChessBoard and vectors of white and black pieces
     * @param lastMove
     * @return true if king is in check
     *          false king is not in check
     */
    bool isCheck(const CCoordinates &coordinatesOfKing, const CChessBoard &board, const SPieceMove &lastMove) const;


};

#endif //PETRIPAT_CKING_H
