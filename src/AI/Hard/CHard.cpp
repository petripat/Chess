#include "CHard.h"
#define HARD_DIFFICULTY 5

CHard::CHard(EColor Color): CAI(Color) {}

SPieceMove CHard::getMovementFromAI(const CBoard &board) const {
        return chooseMove(board, HARD_DIFFICULTY, m_colorOfPieces);
}

std::unique_ptr<CAI> CHard::cloneUnique() const {
    return std::make_unique<CHard>(*this);
}
