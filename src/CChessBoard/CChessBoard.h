#ifndef PETRIPAT_CCHESSBOARD_H
#define PETRIPAT_CCHESSBOARD_H
#include "../Chess/ECColor.h"
#include "../Coordinates/CCoordinates.h"
#include "../PieceMove/SPieceMove.h"
#include <array>
#include <memory>
#include <vector>
#define ROWS 8
#define COL 8
class CAbstractPiece;
class CBoard;
using ChessBoard = std::array<std::array<std::shared_ptr<CAbstractPiece>, COL>, ROWS>;
using piecesVector = std::vector<std::pair<std::shared_ptr<CAbstractPiece>, CCoordinates>>;

/**
* @brief Class that defines member variable of CBoard tiles with data type as ChessBoard = 2D array
*          with shared_ptr for CAbstractPieces. Also defines number of rows and colums in game => 8.
*          Friend of CBoard which can access and change tiles, or vectors of pieces. Other classes always can
*          access tiles and vectors of pieces, but cannot change situation on m_board.
 *
*               Detailed description follows here.
                @author P. Petriľáková
                @date May 2021
 */

class CChessBoard {
    ChessBoard tiles; /**2D array of shared pointers of CAbstractPiece */
    piecesVector piecesBlack; /** vector of pairs shared pointer on black CAbstractPiece and CCoordinates of piece*/
    piecesVector piecesWhite; /** vector of pairs shared pointer on white CAbstractPiece and CCoordinates of piece*/
    friend CBoard;
public:
    /**
     * Default constructor.
     */
    CChessBoard() = default;
    /**
     * @return const reference to tiles of Chessboard - 2D array of shared pointers of CAbstractPiece
     */
    const ChessBoard& getBoard() const;
    /**
     * Based on m_colorOfPieces of playerPieces from parameter, returns opponents pieces
     * @param color - m_colorOfPieces of playerPieces  - enum ECColor from ECColor.h
     * @return vector of pieces represented by pair share_ptr<CAbstractPiece> and class CCoordinates
     */
    const piecesVector &getOpponentsPieces(EColor color) const;
public:
    /**
     * Based on m_colorOfPieces of playerPieces from parameter, returns players pieces
     * @param color - m_colorOfPieces of playerPieces  - enum ECColor from ECColor.h
     * @return vector of pieces represented by pair share_ptr<CAbstractPiece> and class CCoordinates
     */
    const piecesVector &getPlayersPieces(EColor color) const;
private:
    /**
     * Private, can update vector pieces. Based on m_colorOfPieces of playerPieces from parameter, returns players pieces
     * @param color - m_colorOfPieces of playerPieces  - enum ECColor from ECColor.h
     * @return vector of pieces represented by pair share_ptr<CAbstractPiece> and class CCoordinates
     */
    piecesVector &getPlayersPieces(EColor color);
public:
    /**
    * Checks if pieces or opponentsPieces are needed to be updated based on m_lastMove.
    * @param pieces - pieces to be updated
    * @param lastMove - last move made on m_board
    * @return true - pieces were updated
    *          false - no change was done
    */
    bool checkArray(piecesVector &pieces, const SPieceMove &lastMove)  const;
    /**
     * If playerPieces during last move destroyed opponents pieces, this method deletes it from opponentPieces pieces.
     * @param pieces - pieces to delete piece from
     * @param position - position of destroyed piece
     */
    void checkArrayDeletePiece(piecesVector &pieces,
                               const CCoordinates& position) const;
    /**
     * Update pieces and opponentPieces pieces based on last move.
     * @param lastMove - last move made on ChessBoard
     */
    void updateArrays(SPieceMove lastMove);
    /**
     * Copy constructor.
     * @param rhs - another CChessBoard to be copied
     */
    CChessBoard(const CChessBoard & rhs);
    /**
     * @param rhs - another CChessBoard to be copied
     * @return reference to new copied instance
     */
    CChessBoard& operator=(const CChessBoard & rhs);

};
#endif //PETRIPAT_CCHESSBOARD_H