#ifndef PETRIPAT_CPAWN_H
#define PETRIPAT_CPAWN_H

#include "../CAbstractPiece.h"
#include "../Bishop/CBishop.h"
#include "../Knight/CKnight.h"
#include "../Queen/CQueen.h"
#include "../Rook/CRook.h"


#define PAWN_VALUE 100

/**
 * @brief Class CPawn is child class of CAbstractPiece and represents pawn piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */


class CPawn : public CAbstractPiece  {
    int front; /** int represantation of front of piece - +1 if piece is on position a7-h7 and -1  if piece is on position a2-h2 */
    CCoordinates move; /** Pawn specific move upfront based on front variable*/
    /**
         *  Method that checks possibility of En Passant move.
         * @param lastMove - m_lastMove
         * @param from - position from which is piece moving
         * @param validMoves - vector represented of struct SPieceMove from SPieceMove.h with saved valid movements of pawn
         * @param board - class with ChessBoard and vectors of white and black pieces
         */
    void checkEnPassant(const SPieceMove &lastMove, const CCoordinates &from, std::vector<SPieceMove> &validMoves,
                        const ChessBoard &board) const;
    /**
     * Saves possible transformations of pawn during promotion - queen, rook, bishop, knight
     * @param from - position from which is piece moving
     * @param to - position to which is piece moving
     * @param validMoves  - vector represented of struct SPieceMove() from SPieceMove.h with saved valid movements of pawn
     */
    void saveTransformation(const CCoordinates &from, const CCoordinates &to, std::vector<SPieceMove> &validMoves) const;
    /**
     * Check if pawn can go upfront - no piece is on tile and saves move.
     * @param moveTo - position piece wants to move on
     * @param board - m_board on which is piece moving
     * @param validMoves - vector represented of struct SPieceMove() from SPieceMove.h with saved valid movements of pawn
     * @param from - position from which is piece moving
     * @return true if move can be done forward
     */
    bool checkMoveForward(const CCoordinates &moveTo, const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                          std::vector<SPieceMove> &validMoves, const CCoordinates &from) const;
    /**
     * Method to check if opponentPieces piece is diagonally from piece and saves move..
     * @param moveTo - position piece wants to move on
     * @param board - m_board on which is piece moving
     * @param validMoves - vector represented of struct SPieceMove() from SPieceMove.h with saved valid movements of pawn
     * @param from - position from which is piece moving
     */
    void checkMoveDiagonal(CCoordinates moveTo, const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                           std::vector<SPieceMove> &validMoves, const CCoordinates &from) const;
public:
    /**
     * Constructor for piece, sets up moves and its repeating in parent.
     * @param Color - m_colorOfPieces of piece
     */
    CPawn(EColor Color);
    /**
    * @return 'P' - pieces name on m_board
    */
    char pieceChar() const override;
    /**
     * Method that checks possibility of first movement two tiles to the front,
       * transformation and En Passant.
     * @param from - position of pawn
     * @param board - m_board on which are pieces moving
     * @param lastMove - last move made on m_board
     * @return all posible moves of pawn in vector represented by struct SPieceMove from SPieceMove.h
     */
    std::vector<SPieceMove> getPawnMoves(const CCoordinates &from, const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                                         const SPieceMove &lastMove) const;
    /**
     * Virtual method for value of piece on m_board based on strenght of movement and importance of piece.
     * @return int value of piece
     */
    int getValue() const override;

    /**
     * Cloning function for CBishop.
     * @return std::make_shared<CPawn> hidden in std::shared_ptr<CAbstractPiece>
     */
    std::shared_ptr<CAbstractPiece> cloneShared() const override;
    /**
     * Default destructor for piece.
     */
    ~CPawn() override = default;

};

#endif //PETRIPAT_CPAWN_H