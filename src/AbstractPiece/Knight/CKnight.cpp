#include "CKnight.h"


CKnight::CKnight(EColor Color) : CAbstractPiece(Color,  {{-2,1}, {-2,-1},{2,-1}, {2,1},
                                                         {-1,2}, {-1,-2},{1,-2}, {1,2}}, false) {}

int CKnight::getValue() const {
    return KNIGHT_VALUE;
}

std::shared_ptr<CAbstractPiece> CKnight::cloneShared() const {
    return std::make_shared<CKnight>(*this);
}

char CKnight::pieceChar() const {
    return 'N';
}

