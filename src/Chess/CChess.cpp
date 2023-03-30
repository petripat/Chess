#include "CChess.h"

int CChess::lastPlayed;
std::vector<std::string> CChess::moves;
void CChess::run(CVisualization & file) {
//    int i = 0;
    while(true) { ///catch and return exception
        lastPlayed = 2;
        playPlayer(file, player1, moves);
        lastPlayed = 1;
        playPlayer(file, player2, moves);
//        if(i == 5) {
//            getchar();
//            i = 0;
//        }
//        i++;
    }
}

bool CChess::checkCheckMate(CVisualization &file, const std::string &color) {
    if(state == CHECK){
        file.pasteEndOfLine("CHECK");
    }
    else if(state == CHECKMATE){
        file.pasteEndOfLine("CHECKMATE");
        file.pasteEndOfLine("Winner is:");
        file.pasteEndOfLine(color);
        file.pasteEndOfLine("Thank you for game.");
        return true;
    }
    return false;
}

void CChess::printCounterOfPieces(CVisualization & file) {
    file.paste(player1->getColorInString(player1->getColorOfPieces()));
    file.paste(" captured: ");
    file.pasteNumber(player1->getCapturedCount());
    file.paste("\n");
    file.paste(player2->getColorInString(player2->getColorOfPieces()));
    file.paste(" captured: ");
    file.pasteNumber(player2->getCapturedCount());
    file.paste("\n");
}

void
CChess::playPlayer(CVisualization &file, std::unique_ptr<CAbstractPlayer> &player, std::vector<std::string> &moves) {
    file.printBoard(player->getBoard());
    printCounterOfPieces(file);
    state = player->play(file, moves);
    if(checkCheckMate(file, player->getColorInString(player->getColorOfPieces()))){
        file.printBoard(player->getBoard());
        throw 3;
    }
}

void CChess::continueGame(CVisualization &file) {
    lastPlayed = lastPlayedForSave;
//    moves = std::move(movesForSave);
//    movesForSave.erase(movesForSave.begin(), movesForSave.end());
    if(lastPlayed == 1){
        player2->updateGame();
        playPlayer(file, player2, moves);
        run(file);
    }
    else{
        player1->updateGame();
        run(file);
    }
}

void CChess::playingCyclus(std::ifstream &inFile, int &counter, bool player1OnPlay, CVisualization &file) {
    std::string line1, line2;
    file.getLineForString(inFile, line1, counter);
    while (1) {
        file.getLineForString(inFile, line2, counter);
        if (!line2.empty() && line2.size() < 2) {
            std::string line3;
            file.getLineForString(inFile, line3, counter);
            bool last;
            if(line3 == "END"){
                last = true;
            }
            else last = false;
            if (player1OnPlay) {
                player1->catchUpGame(file, moves, line1, last, line2);
                player1OnPlay = false;
            } else {
                player2->catchUpGame(file, moves, line1, last, line2);
                player1OnPlay = true;
            }
            line2 = line3;
        } else if (line2 == "END") {
            if (player1OnPlay) {
                player1->catchUpGame(file, moves, line1, true);
                lastPlayed = 1;
                return;
            } else {
                player2->catchUpGame(file, moves, line1, true);
                lastPlayed = 2;
                return;
            }
        }
        else {
            if (player1OnPlay) {
                player1->catchUpGame(file, moves, line1);
                player1OnPlay = false;
            } else {
                player2->catchUpGame(file, moves, line1);
                player1OnPlay = true;
            }
        }
        line1 = line2;
    }
}

CChess::CChess(const CChess &rhs) {
    player1 = rhs.player1->cloneUnique();
    player2 = rhs.player2->cloneUnique();
    lastPlayedForSave = rhs.lastPlayedForSave;
    state = rhs.state;
    moves = rhs.moves;
}

void CChess::setForSaving() {
    lastPlayedForSave = lastPlayed;
//    movesForSave = std::move(moves);
//    moves.erase(moves.begin(), moves.end());
    if(lastPlayed == 1){
        player2->saveGame();
    }
    else{
        player1->saveGame();
    }
}

bool CChess::saveToFile(CVisualization &file, std::string &filename) const {
    std::ofstream outFile(filename, std::ofstream::trunc);
    if ( !outFile ) {
        file.paste("Cannot open file.");
        return false;
    }
    for(const auto & move : moves) {
        std::copy(move.begin(), move.end(), std::ostreambuf_iterator<char>(outFile));
    }
    outFile << "END\n";
    outFile.flush();
    outFile.close();
    if ( !outFile.good() ) {
        file.paste( "Error occured at writing/reading time." );
        return false;
    }
    return true;
}

CChess::CChess(std::ifstream &inFile, CVisualization &file) : player1(), player2(), settings(inFile, lastPlayed, player1,
                                                                                             player2, file, moves), lastPlayedForSave(0), state(NO_STATE) {
    player1->resetBoard();
    int counter = lastPlayed;
    lastPlayed = 0;
//    player1->resetBoard();
    bool player1OnPlay = true;
    try {
        playingCyclus(inFile, counter, player1OnPlay, file);
    }
    catch(std::invalid_argument & ex){
        file.paste(ex.what());
        file.paste("\n");
        file.paste("Error at line: ");
        file.pasteNumber(counter);
        file.paste("\n");
        moves.clear();
        throw std::invalid_argument("Error");
    }
}










