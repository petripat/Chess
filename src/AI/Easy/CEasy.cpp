#include "CEasy.h"
#define EASY_DIFFICULTY 2

CEasy::CEasy(EColor Color) : CAI(Color) {}

SPieceMove CEasy::getMovementFromAI(const CBoard &board) const {
    return chooseMove(board, EASY_DIFFICULTY, m_colorOfPieces);
}
