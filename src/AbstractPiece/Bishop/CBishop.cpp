#include "CBishop.h"

CBishop::CBishop(EColor Color) : CAbstractPiece(Color,  {{1,1}, {-1,1}, {1,-1}, {-1,-1}}  ) {}

int CBishop::getValue() const {
    return BISHOP_VALUE;
}

std::shared_ptr<CAbstractPiece> CBishop::cloneShared() const {
    return std::make_shared<CBishop>(*this);
}

char CBishop::pieceChar() const {
    return 'B';
}



