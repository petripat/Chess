#include "CMedium.h"
#define MEDIUM_DIFFICULTY 3

CMedium::CMedium(EColor Color) : CAI(Color) {}

SPieceMove CMedium::getMovementFromAI(const CBoard &board) const {
    return chooseMove(board, MEDIUM_DIFFICULTY, m_colorOfPieces);
}
