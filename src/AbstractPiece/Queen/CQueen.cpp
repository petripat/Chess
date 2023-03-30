#include "CQueen.h"


CQueen::CQueen(EColor Color): CAbstractPiece(Color, {{1,1}, {-1,1}, {1,-1}, {-1,-1},
                                                     {1,0},{-1,0}, {0,1}, {0,-1}}) {}

int CQueen::getValue() const {
    return QUEEN_VALUE;
}

std::shared_ptr<CAbstractPiece> CQueen::cloneShared() const {
    return std::make_shared<CQueen>(*this);
}

char CQueen::pieceChar() const {
    return 'Q';
}

