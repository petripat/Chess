#include "CRook.h"

CRook::CRook(EColor Color) : CAbstractPiece(Color, {{1,0},{-1,0}, {0,1}, {0,-1}}) {}

int CRook::getValue() const {
    return ROOK_VALUE;
}

std::shared_ptr<CAbstractPiece> CRook::cloneShared() const {
    return std::make_shared<CRook>(*this);
}

char CRook::pieceChar() const {
    return 'R';
}

