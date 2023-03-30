#include "CComputer.h"

CComputer::CComputer(EColor Color) : CAbstractPlayer(Color) {}

SPieceMove CComputer::chooseMove(CVisualization &file) const {
//    file.pasteEndOfLine("Thinking .. ");
    return AI->getMovementFromAI(m_board);
}

void CComputer::setAIHard() {
    AI = std::make_unique<CHard>(piecesColor);
}

void CComputer::setAIMedium() {
    AI = std::make_unique<CMedium>(piecesColor);
}

void CComputer::setAIEasy() {
    AI = std::make_unique<CEasy>(piecesColor);
}


