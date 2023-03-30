#include "CPlayer.h"

CPlayer::CPlayer(EColor Color) : CAbstractPlayer(Color) {}

std::string CPlayer::getInput(CVisualization &file) {
    std::string tmp;
    if(!file.getLineInLower(tmp) || tmp == "q" || tmp == "quit"){
        throw "quit";
    }
    if(tmp == "draw" || tmp == "check"){
        throw 0;
    }
    if(tmp == "save"){
        throw 1;
    }
    if(tmp == "load"){
        throw 2;
    }
    if(tmp == "!save"){
        throw 4;
    }
    if(tmp == "!load"){
        throw 5;
    }
    return tmp;
}
SPieceMove CPlayer::readMove(CVisualization &file) const {
    SPieceMove currentMove;
    file.pasteEndOfLine("Please, write your move.");
    std::stringstream str;
    std::string tmp = getInput(file);
    while(true) {
        if(tmp.length() == 0) {}
        else if (tmp.length() < 10) {
            file.pasteEndOfLine(
                    "Missing piece, move from or move to. Please write move like this:\n\t(abbreviation of piece) old_position(letter, number) to new_position\t-\t"
                    "For example: k D1 to C1");
        }
        else {
            if(splitMove(tmp, currentMove, file)){
                return currentMove;
            }
             else {
                file.pasteEndOfLine("Please, write your move.");
            }
        }
        tmp = getInput(file);
    }
}

SPieceMove CPlayer::chooseMove(CVisualization &file) const {
    SPieceMove currentMove = readMove(file);
    while(!isCorrectMove(currentMove, file)){
        currentMove = readMove(file);
    }
    if(currentMove.m_move == PROMOTION){
        promotionOfPawn(currentMove, file);
    }
    return currentMove;
}

std::unique_ptr<CAbstractPlayer> CPlayer::cloneUnique() const {
    return std::make_unique<CPlayer>(*this);
}

