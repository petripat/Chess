#include "CPawn.h"


CPawn::CPawn(EColor Color) : CAbstractPiece(Color, {}, false) {
    if(Color == WHITE) front = -1;
    else front = 1;
    move = {front, 0};
}

std::vector<SPieceMove> CPawn::getPawnMoves(const CCoordinates &from,
                                            const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                                            const SPieceMove &lastMove) const {
    std::vector<SPieceMove> validMoves;
    if (checkMoveForward(from + move, board, validMoves, from) && m_startPos) {
        (checkMoveForward(from + move + move, board, validMoves, from));
    }
    checkEnPassant(lastMove, from, validMoves, board);
    checkMoveDiagonal(from.operator+({front, 1}), board, validMoves, from);
    checkMoveDiagonal(from.operator+({front, -1}), board, validMoves, from);
    return validMoves;
}

int CPawn::getValue() const {
    return PAWN_VALUE;
}

bool CPawn::checkMoveForward(const CCoordinates &moveTo, const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                             std::vector<SPieceMove> &validMoves, const CCoordinates &from) const {
    if(moveTo.getRow() >= 0 && moveTo.getRow() < ROWS && moveTo.getColumn() >= 0 && moveTo.getColumn() < COL) {
        if(board[moveTo.getRow()][moveTo.getColumn()]){
            return false;
        }
        else {
            if(front == 1 && moveTo.getRow() == 7){
                saveTransformation(from, moveTo, validMoves);
            }
            else if(front == -1 && moveTo.getRow() == 0){
                saveTransformation(from, moveTo, validMoves);
            }
            else validMoves.emplace_back(from, moveTo, 0);
        }
        return true;
    }
    return false;
}

void CPawn::saveTransformation(const CCoordinates &from, const CCoordinates &to, std::vector<SPieceMove> &validMoves) const {
    validMoves.emplace_back(from, to, BISHOP_VALUE + PAWN_VALUE/2, BISHOP,  PROMOTION);
    validMoves.emplace_back(from, to, KNIGHT_VALUE + PAWN_VALUE/2, KNIGHT, PROMOTION);
    validMoves.emplace_back(from, to, ROOK_VALUE + PAWN_VALUE/2, ROOK,  PROMOTION);
    validMoves.emplace_back(from, to,QUEEN_VALUE + PAWN_VALUE/2, QUEEN,  PROMOTION);
}

void CPawn::checkMoveDiagonal(CCoordinates moveTo,
                              const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board,
                              std::vector<SPieceMove> &validMoves, const CCoordinates &from) const {
    if(moveTo.getRow() >= 0 && moveTo.getRow() < ROWS && moveTo.getColumn() >= 0 && moveTo.getColumn() < COL) {
        if(board[moveTo.getRow()][moveTo.getColumn()]){
            if(board[moveTo.getRow()][moveTo.getColumn()]->getColor() != m_colorOfPiece){
                validMoves.emplace_back(from, moveTo, board[moveTo.getRow()][moveTo.getColumn()]->getValue());
            }
        }
    }
}

std::shared_ptr<CAbstractPiece> CPawn::cloneShared() const {
    return std::make_shared<CPawn>(*this);
}

void CPawn::checkEnPassant(const SPieceMove &lastMove, const CCoordinates &from, std::vector<SPieceMove> &validMoves,
                           const ChessBoard &board) const {
    if(from.operator+({0,1}) == lastMove.m_to && abs(lastMove.m_from.getRow() - lastMove.m_to.getRow()) == 2 &&
       lastMove.m_from.getColumn() - lastMove.m_to.getColumn() == 0 &&
       board[lastMove.m_to.getRow()][lastMove.m_to.getColumn()]->pieceChar() == 'P'){
        validMoves.emplace_back(from, lastMove.m_to.operator+({front, 0 }), PAWN_VALUE, PAWN, ENPASSANT);
    }
    else if(from.operator+({0,-1}) == lastMove.m_to && abs(lastMove.m_from.getRow() - lastMove.m_to.getRow()) == 2
            && lastMove.m_from.getColumn() - lastMove.m_to.getColumn() == 0 &&
            board[lastMove.m_to.getRow()][lastMove.m_to.getColumn()]->pieceChar() == 'P'){
        validMoves.emplace_back(from, lastMove.m_to.operator+({front, 0}), PAWN_VALUE, PAWN, ENPASSANT);
    }
}

char CPawn::pieceChar() const {
    return 'P';
}

