#ifndef PETRIPAT_CBOARD_H
#define PETRIPAT_CBOARD_H

#include "../AbstractPiece/King/CKing.h"
#include "../AbstractPiece/Pawn/CPawn.h"
#include "../Visualization/CVisualization.h"
#include "ECGameState.h"


class CAbstractPiece;

/**
 * @brief CBoard class represents m_board as whole with methods such as move piece.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CBoard {
    CChessBoard m_board; /** class to which is CBoard friend class with m_board made of shared pointers to pieces and
     *  two vectors of all black and white pieces */
    /**
     * Resets pieces to desired tiles.
     * @param Color - m_colorOfPieces of pieces to be set up
     * @param row - row at which start
     * @param plus - row + plus at which end
     */
    void setBoard(EColor Color, int row, int plus);
    SPieceMove m_lastMove; /**last move done on m_board*/
    CCoordinates m_kingBlackPos; /**coordinates of black king*/
    CCoordinates m_kingWhitePos; /**coordinates of white king*/
    /**
     * Method that updates position of king.
     * @param color - m_colorOfPieces of king to be updated
     * @param coordinates - coordinates to update position of king to
     */
    void updateKingPos(EColor color, const CCoordinates &coordinates);
    /**
     * Checks if tile is empty or piece is at the space
     * @param pos
     * @return
     */
    bool tileIsEmpty(const CCoordinates &pos) const;
    /**
     * Moves piece on m_board.
     * @param from - coordinates of position to move piece from
     * @param to - coordinates of position to move piece to
     */
    void movePiece(const CCoordinates &from, const CCoordinates &to);
    /**
     * Based on move promotes pawn to chosen piece.
     * @param move - move of pawn with move.move == PROMOTION and move.piece as desired promotion
     */
    void promotion(const SPieceMove &move);
    /**
     * Based on move of king, moves Rook to desired position
     * @param move - move of King
     */
    void moveRookDuringCastling(const SPieceMove &move);
    /**
     * Function called in constructor meant to set up piecesOpponent and pieces.
     * @param from - coordinates of starting position of piece
     * @param to - coordinates of ending position of piece
     * @param in - vector to save all pieces in
     */
    void copyPiecesOnBoard(const CCoordinates &from, const CCoordinates &to,
                           std::vector<std::pair<std::shared_ptr<CAbstractPiece>, CCoordinates>> &in);
    /**
   * Method that checks if king is in check at all positions(possible moves) around him.
   * @param coordinates - coordinates of king
   * @return true -  king is in check during every move
   *          false - king is not in check during every move
   */
    bool checkCheckAroundKing(const CCoordinates &coordinates) const;
    /**
     * Method that checks if piece that is holding king in check can by destoyed by players pieces.
     * @param colorOfPlayer - m_colorOfPieces of playerPieces playing
     * @param checkPiece - position of endangering piece
     * @return true - piece that can destroy endangering king exists
     *          false - piece that can destroy endangering king does not exists
     */
    bool checkForKiller(EColor colorOfPlayer, const SPieceMove &checkPiece) const;
    /**
     * Method that checks if there is piece that can move in front of check and save king.
     * @param colorOfPlayer - m_colorOfPieces of playerPieces playing
      * @return true - scapegoat to save king exists
      *         false - no scapegoat, king is still in check
     */
    bool checkForScapegoat(EColor colorOfPlayer) const;
    /**
     * Method that makes move to empty tile and checks all moves possible at empty tile - castling, en passant, promotion.
     * @param move - move to be made
     * @return true if piece was taken
     *          false - no piece was taken during move
     */
public:
    /**
     * Constuctor that sets up empty m_board.
     */
    explicit CBoard(bool setUp = true);
    /**
     * Copy constructor that sets up m_board with pieces at same position as has m_board
     * @param board - m_board to copy from
     */
    CBoard(const CBoard & board);
    /**
     * Method that checks if move of piece is correct
     * @param from - position to move from
     * @param to - position to move to
     * @param moveOriginal - original move to check its correctness
     * @return true - move is ok
     *         false - move is incorrect for piece
     */
    bool validMove(CCoordinates &from, CCoordinates &to, SPieceMove &moveOriginal) const;
    /**
    * @return const instance of CChessBoard (defined in CChessBoard.h)
    */
    const CChessBoard & getChessBoard () const;
    /**
     * @return const instance of m_board made of 2D arrays with shared_ptr for pieces
     */
    const ChessBoard & getBoard () const;
    /**
     * Method that moves with piece on m_board based on move.
     * @param move - move to be made represented by struct SPieceMove defined in SPieceMove.h
     * @param realMove - when true move is taken as real and not used by AI and is
     * called method moved for piece which sets piece as used
     * @return true - move destroyed one of opponents pieces
     *         false - no piece was destroyed during move
     */
    bool makeMove(const SPieceMove &move, bool realMove);
    /**
     * @return last move made on m_board
     * @return last move made on m_board
     */
    SPieceMove getLastMoveMade() const;
    /**
     * Copy operator for m_board
     * @param rhs - CBoard to be copied
     * @return instance of new copied rhs
     */
    CBoard& operator=(const CBoard & rhs);
    /**
     * Gets current position of king
     * @param color - m_colorOfPieces of desired king position - enum ECColor from ECColor.h
     * @return CCoordinates of king's position
     */
    CCoordinates getKingPos(EColor color) const;
    /**
     * Method that returns game state enum defined in EGameState .
     * @param colorOfPlayer - m_colorOfPieces of playerPieces playing
     * @return enum EGameState representing state of game from ECGameState.h
     */
     ECGameState getGameState(EColor colorOfPlayer, bool playerOnRow) const;
    /**
     * Method that returns game state.
     * @param coordinatesOfKing - coordinates of king
     * @param saveMove - bool asking if all check position should be returned
     * @return vector of structs SPieceMove representing all moves to check positions of king
     */
    std::vector<SPieceMove> isCheck(const CCoordinates &coordinatesOfKing, bool saveMove) const;
    /**
     * Takes care of move to empty tile.
     * @param move - move to be made
     * @return true - piece was taken (enPassant)
     */
    bool makeMoveToEmptyTile(const SPieceMove &move);
    /**
     * From given color returns other color -
     * @param color - color from which return other color
     * @return color opposite to given color aka color = white -> return black
     */
    static EColor getOtherColor(EColor color);
    /**
     * Method that checks if taken piece is king.
     * @param move - move to be made
     * @param file - file for communication
     * @return true - king is OK
     *         false - king is taken
     */
    bool checkKing(const SPieceMove &move) const;
    /**
     * Checks if piece is threat to king or piece at position of coordinatesOfKing
     * @param coordinatesOfKing
     * @param threatPiece - piece possibly capturing king
     * @return true - piece is not threat
     *         false - piece has move with which it can reach coordinatesOfKing
     */
    bool isThreat(const CCoordinates &coordinatesOfKing, const CCoordinates &threatPiece) const;
    /**
     * Methods that updates if piece moved during the game - needed always after AI.
     */
    void updateRealMoves();
    /**
     * Method that checks if piece at position coordinatesOfKing can be reached by knights at m_board.
     * @param coordinatesOfKing
     * @param checkPieces
     */
    void checkKnights(const CCoordinates &coordinatesOfKing, std::vector<SPieceMove> &checkPieces, bool saveMove) const;
    /**
     * Makes copy of current board to boardForSave.
     * @param boardForSave
     */
    void makeCopyTo(CBoard & boardForSave);
    /**
     * Reset boards to initial piece setting.
     */
    void resetBoard();
    void updateTo(const CBoard &boardOriginal, const SPieceMove &move);
};


#endif //PETRIPAT_CBOARD_H
