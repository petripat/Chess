#include "CAbstractPiece.h"
#include "Pawn/CPawn.h"
#include "King/CKing.h"


CAbstractPiece::CAbstractPiece(EColor Color, std::vector<CCoordinates> &&possibleMoves, bool repeatsMoves)
                                            : m_colorOfPiece(Color), m_repeat(repeatsMoves), m_movesOfPiece(std::move(possibleMoves)), m_startPos(true), m_realStartPos(true) {}

std::vector<SPieceMove>
CAbstractPiece::getMoves(const CCoordinates &from, const CChessBoard &chessBoard, const SPieceMove &lastMoveOnBoard/*,
                         EColor m_colorOfPieces*/) const {
    CPawn * pawn = dynamic_cast<CPawn*> (&*chessBoard.getBoard()[from.getRow()][from.getColumn()]);
    if(pawn){
        return pawn->getPawnMoves(from, chessBoard.getBoard(), lastMoveOnBoard);
    }
    else if(chessBoard.getBoard()[from.getRow()][from.getColumn()] && !chessBoard.getBoard()[from.getRow()][from.getColumn()]->pieceWasMoved()){
        CKing * king = dynamic_cast<CKing*> (&*chessBoard.getBoard()[from.getRow()][from.getColumn()]);
        if(king)
            return king->getKingMoves(from, chessBoard, lastMoveOnBoard);
    }
    return generateMoves(from, chessBoard.getBoard());
}

EColor CAbstractPiece::getColor() const {
    return m_colorOfPiece;
}

std::vector<SPieceMove> CAbstractPiece::generateMoves(const CCoordinates &from,
                                                      const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                                                      bool outsideRepeat) const {
    std::vector<SPieceMove> validMoves;
    CCoordinates tmpPos = from;
    if(!board[from.getRow()][from.getColumn()]){
        return validMoves;
    }
    for(const auto & pos : m_movesOfPiece){
        tmpPos += pos;
        if(m_repeat || outsideRepeat){
            reccuringMoves(tmpPos, board, validMoves, pos, from);
        }
        else {
            if(tmpPos.getRow() >= 0 && tmpPos.getRow() < ROWS && tmpPos.getColumn() >= 0 && tmpPos.getColumn() < COL) {
                insertMove(board, tmpPos, validMoves, from);
            }
        }
        tmpPos = from;
    }
    return validMoves;
}

void CAbstractPiece::reccuringMoves(CCoordinates position,
                                    const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                                    std::vector<SPieceMove> &validMoves, const CCoordinates &move,
                                    const CCoordinates &from) const {
    for(; position.getRow() >= 0 && position.getRow() < ROWS && position.getColumn() >= 0 && position.getColumn() < COL; position += move){
        if(insertMove(board, position, validMoves, from)){
            break;
        }
    }
}

bool CAbstractPiece::insertMove(const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                                CCoordinates &to,
                                std::vector<SPieceMove> &validMoves, const CCoordinates &from) const {
    if(board[to.getRow()][to.getColumn()]){
        if(board[to.getRow()][to.getColumn()]->getColor() == m_colorOfPiece) {}
        else {
            if(board[from.getRow()][from.getColumn()] && board[from.getRow()][from.getColumn()]->isKing()){
                validMoves.emplace_back(from, to, (board[to.getRow()][to.getColumn()]->getValue()));
            }
            validMoves.emplace_back(from, to, board[to.getRow()][to.getColumn()]->getValue());
        }
        return true;
    }
    else {
        if(board[from.getRow()][from.getColumn()] && board[from.getRow()][from.getColumn()]->isKing()){
            validMoves.emplace_back(from, to, -1);
        }
        else validMoves.emplace_back(from, to, 0);
        return false;
    }
}

void CAbstractPiece::moved() {
    m_startPos = false;
}

bool CAbstractPiece::pieceWasMoved() const {
    return !m_startPos;
}

void CAbstractPiece::RealMove() {
    m_realStartPos = false;
}

void CAbstractPiece::updateMoved() {
    m_startPos = m_realStartPos;
}

bool CAbstractPiece::isKing() const {
    return false;
}






