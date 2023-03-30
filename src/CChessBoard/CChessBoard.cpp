#include "CChessBoard.h"


const ChessBoard &CChessBoard::getBoard() const {
    return tiles;
}

const piecesVector & CChessBoard::getPlayersPieces(EColor color) const{
    if(color == WHITE) {
        return piecesWhite;
    }
    else return piecesBlack;
}

const piecesVector &CChessBoard::getOpponentsPieces(EColor color) const {
    if(color == BLACK) {
        return piecesWhite;
    }
    else return piecesBlack;
}

void CChessBoard::updateArrays(SPieceMove lastMove) {
    if(checkArray(piecesWhite, lastMove)) {
        if (lastMove.m_move == CASTLING){
            if(lastMove.m_to.operator==({lastMove.m_to.getRow(), 2})){
                checkArray(piecesWhite, SPieceMove({lastMove.m_to.getRow(), 0}, {lastMove.m_to.getRow(), 3}));
            }
            else {
                checkArray(piecesWhite, SPieceMove({lastMove.m_to.getRow(), 7}, {lastMove.m_to.getRow(), 5}));
            }
        }
        checkArrayDeletePiece(piecesBlack, lastMove.m_to);
        if (lastMove.m_move == ENPASSANT){
            checkArrayDeletePiece(piecesBlack, {lastMove.m_from.getRow(), lastMove.m_to.getColumn()});
        }
        return;
    }
    checkArray(piecesBlack, lastMove);
    if (lastMove.m_move == CASTLING){
        if(lastMove.m_to.operator==({lastMove.m_to.getRow(), 2})){
            checkArray(piecesBlack, SPieceMove({lastMove.m_to.getRow(), 0}, {lastMove.m_to.getRow(), 3}));
        }
        else {
            checkArray(piecesBlack, SPieceMove({lastMove.m_to.getRow(), 7}, {lastMove.m_to.getRow(), 5}));
        }
    }
    checkArrayDeletePiece(piecesWhite, lastMove.m_to);
    if (lastMove.m_move == ENPASSANT){
        checkArrayDeletePiece(piecesWhite, {lastMove.m_from.getRow(), lastMove.m_to.getColumn()});
    }
}

bool CChessBoard::checkArray(std::vector<std::pair<std::shared_ptr<CAbstractPiece>, CCoordinates>> &pieces, const SPieceMove &lastMove)  const {
    for(auto & piece : pieces){
        if(lastMove.m_from == piece.second){
            piece.second = lastMove.m_to;
            return true;
        }
    }
    return false;
}

void CChessBoard::checkArrayDeletePiece(std::vector<std::pair<std::shared_ptr<CAbstractPiece>, CCoordinates>> &pieces,
                                   const CCoordinates& position) const {
    for(auto start = pieces.begin(), end = pieces.end(); start != end; start++){
        CCoordinates test = position;
        if(start->second == test){
            pieces.erase(start);
            return;
        }
    }
}

CChessBoard &CChessBoard::operator=(const CChessBoard &rhs) {
    if(&rhs == this){
        return *this;
    }
    piecesBlack.clear();
    for(const auto & a : rhs.piecesBlack){
        piecesBlack.emplace_back(a);
    }
    piecesWhite.clear();
    for(const auto & a : rhs.piecesWhite){
        piecesWhite.emplace_back(a);
    }
    return *this;
}

CChessBoard::CChessBoard(const CChessBoard &rhs) {
    if(&rhs == this){
        return;
    }
    *this = rhs;
}

piecesVector &CChessBoard::getPlayersPieces(EColor color) {
    if(color == WHITE) {
        return piecesWhite;
    }
    else return piecesBlack;
}
