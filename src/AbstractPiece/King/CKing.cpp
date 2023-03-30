#include "CKing.h"


char CKing::pieceChar() const {
    return 'K';
}

CKing::CKing(EColor Color) : CAbstractPiece(Color, {{1,1}, {-1,1}, {1,-1}, {-1,-1},
                                                  {1,0},{-1,0}, {0,1}, {0,-1}}, false) {}

int CKing::getValue() const {
    return KING_VALUE;
}

std::shared_ptr<CAbstractPiece> CKing::cloneShared() const {
    return std::make_shared<CKing>(*this);
}

std::vector<SPieceMove>
CKing::getKingMoves(const CCoordinates &from, const CChessBoard &chessBoard, const SPieceMove &lastMove) const {
    std::vector<SPieceMove> validMoves = generateMoves(from, chessBoard.getBoard());
    if(m_colorOfPiece == WHITE){
        checkCastling({7, 0}, {7, 7}, from, chessBoard, validMoves, lastMove);
    }
    else {
        checkCastling({0, 0}, {0, 7}, from, chessBoard, validMoves, lastMove);
    }
    return validMoves;
}

void CKing::checkCastling(const CCoordinates &rook1, const CCoordinates &rook2, const CCoordinates &from,
                          const CChessBoard &board, std::vector<SPieceMove> &validMoves,
                          const SPieceMove &lastMove) const {
    if (board.getBoard()[rook1.getRow()][rook1.getColumn()] &&
            board.getBoard()[rook1.getRow()][rook1.getColumn()]->canCastle()) {
        if (tilesAreEmpty(rook1, from, board.getBoard())) {
            if (checkKingIsNotInCheck(from.operator+({0, -2}), from, board, lastMove)) {
                validMoves.emplace_back(from, from.operator+({0, -2}),100, KING, CASTLING);
            }
        }
    }
    if (board.getBoard()[rook2.getRow()][rook2.getColumn()] &&
            board.getBoard()[rook2.getRow()][rook2.getColumn()]->canCastle()) {
        if (tilesAreEmpty(from, rook2, board.getBoard())) {
            if (checkKingIsNotInCheck(from, from.operator+({0, +2}), board, lastMove)) {
                validMoves.emplace_back(from, from.operator+({0, +2}),  100, KING, CASTLING);
            }
        }
    }
}
    bool CKing::tilesAreEmpty(const CCoordinates &from, const CCoordinates &to,
                              const std::array<std::array<std::shared_ptr<CAbstractPiece>, 8>, 8> &board) const  {
        for(auto pos = from.operator+({0,1}); pos < to; pos = pos.operator+({0,1})) {
            if(board[pos.getRow()][pos.getColumn()]){
                return false;
            }
        }
        return true;
    }

bool CKing::checkKingIsNotInCheck(const CCoordinates &fromKingPos, const CCoordinates &toKingPos, const CChessBoard &chessBoard,
                                  const SPieceMove &lastMove) const {
    for(auto pos = fromKingPos; !(toKingPos < pos); pos = pos.operator+({0,1})) {
        if(isCheck(pos, chessBoard, lastMove)){
            return false;
        }
    }
    return true;
}

bool CKing::isCheck(const CCoordinates &coordinatesOfKing, const CChessBoard &board, const SPieceMove &lastMove) const {
//    m_board.getBoard()[coordinates.getRow()][coordinates.getColumn()]->getMoves(coordinates, m_board.getChessBoard(), true);
    std::vector<SPieceMove> checkPieces;
    for(const auto & piece : board.getOpponentsPieces(m_colorOfPiece)){
        if(!piece.first->isKing()) {
            if(board.getBoard()[piece.second.getRow()][piece.second.getColumn()])
                for (const auto &pos : piece.first->getMoves(piece.second, board, lastMove))
                    if (coordinatesOfKing == pos.m_to) {
                        return true;
                    }
        }
        else{
            for (const auto &pos : board.getBoard()[piece.second.getRow()][piece.second.getColumn()]->generateMoves(piece.second, board.getBoard()))
                if (coordinatesOfKing == pos.m_to) {
                    return true;
                }
        }
    }
    return false;
}

bool CKing::isKing() const {
    return true;
}
