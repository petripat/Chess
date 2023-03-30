#ifndef PETRIPAT_CABSTRACTPIECE_H
#define PETRIPAT_CABSTRACTPIECE_H

#include <vector>
#include <string>
#include "../CChessBoard/CChessBoard.h"


/**
 * @brief Class CAbstractPiece is parent class to all pieces on m_board.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CAbstractPiece {
    //std::vector<char> pieces = {'K', 'Q', 'R', 'N', 'B', 'P', ' '};  /** vector of written format of pieces */
protected:
    EColor m_colorOfPiece; /** color of piece */
    bool m_repeat; /** represents repeating movement of piece - for example queen moves one tile up front or
 * two and so on */
    const std::vector<CCoordinates> m_movesOfPiece; /** all one tile moves of pieces on m_board represented by
 * class coordinates */
    bool m_startPos; /** is piece on starting position or was it moved with - for AI, needs to be updated*/
    bool m_realStartPos; /** is piece on starting position or was it moved with */
public:
    /**
     * Returns false for everyone except rook if rook has not moved during game.
     */
    virtual bool canCastle() const {
        return false;
    }
    /**
     * Method split between generating single moves or recurring moves. Cannot be used for Pawn or King due
     * to moves such as casting, transformation and En Passant.
     * @param from - starting position of piece
     * @param board - m_board on which is piece moving
     * @param outsideRepeat - set to true if moves of a piece are to be repeated - defaul value false
     * @return vector of possible moves of piece represented by struct SPieceMove from SPieceMove.h
     */
    std::vector<SPieceMove> generateMoves(const CCoordinates &from,
                                          const ChessBoard &board,
                                          bool outsideRepeat = false) const;

    /**
     * @return true - piece is king
     */
    virtual bool isKing() const;
    /**
     * @return piece's name used on board for visualisation, for example for king returns 'K'
     */
    virtual char pieceChar() const = 0;
    /**
     * Constructer for pieces.
     * @param Color - m_colorOfPieces of piece
     * @param possibleMoves - vector represented by coordinates of possible moves
     * @param repeatsMoves  - bool saying if moves in vector possible moves are repeating
     */
    explicit CAbstractPiece(EColor Color, std::vector<CCoordinates> &&possibleMoves, bool repeatsMoves = true);
    /**
     * virtual default constructor
     */
    virtual ~CAbstractPiece() = default;
    /**
     * Value of piece on m_board based on strength of movement and importance of piece.
     * @return int value of piece
     */
    virtual int getValue() const = 0;
    /**
     * Function asking if piece is not in starting position and did not move during game.
     * @return true for piece is not in starting position,
     *          false - piece is in starting position
     */
    bool pieceWasMoved() const;
    /**
     *  Generates possible moves from any piece at any position.
     * @param from - position where to start from
     * @param chessBoard - - class with ChessBoard and vectors of white and black pieces
     * @param lastMoveOnBoard - last move made on m_board, if none send dafault value of last move aka SPieceMove()
     *                        - needed for En passant
     * @return all posible moves of piece in vector represented by struct SPieceMove from SPieceMove.h
     */
    std::vector<SPieceMove> getMoves(const CCoordinates &from, const CChessBoard &chessBoard, const SPieceMove &lastMoveOnBoard) const;
    /**
     * @return m_colorOfPieces of piece - enum ECColor from ECColor.h
     */
    EColor getColor() const;
    /**
     * Function setting m_startPos to false. Piece was moved with.
     */
    void moved();
    /**
     * Due to AI testing movements can change if piece moved. This method corrects this.
     */
    void updateMoved();
    /**
     * For real move use this method to set piece as moved with.
     */
    void RealMove();
    /**
     * Virtual cloning function for any piece.
     * @return shared_ptr of cloned piece
     */
    virtual std::shared_ptr<CAbstractPiece> cloneShared() const = 0;
private:
    /**
     * Method generating moves for pieces with repeating move true.
     * @param position - position the piece is on
     * @param board - m_board on which is piece moving
     * @param validMoves - vector represented of struct SPieceMove from SPieceMove.h with saved valid movements of piece
     * @param move - move of piece to be repeated
     * @param from - position from which is piece moving
     */
    void reccuringMoves(CCoordinates position,
                        const ChessBoard &board,
                        std::vector<SPieceMove> &validMoves, const CCoordinates &move, const CCoordinates &from) const;
    /**
         * If move is fulfilling condition of correct move, it is inserted in vector validMoves.
         * @param board - m_board on which is piece moving
         * @param to - position of piece to be moved in
         * @param validMoves  - vector represented of struct SPieceMove() from SPieceMove.h with saved valid movements of piece
         * @param from - position of piece to be moved from
         * @return true if inserting is done
         *          false if in the same direction can be more moves
         */
    bool insertMove(const ChessBoard &board, CCoordinates &to,
                    std::vector<SPieceMove> &validMoves, const CCoordinates &from) const;protected:
};

#endif //PETRIPAT_CABSTRACTPIECE_H