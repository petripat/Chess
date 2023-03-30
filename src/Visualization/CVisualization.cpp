#include "CVisualization.h"

CVisualization::CVisualization(std::istream &in, std::ostream &out) : m_in(in), m_out(out) {}

void CVisualization::paste(std::string & str) {
    m_out << str;
}

bool CVisualization::read(std::string &read) {
    m_in >> std::skipws >> read;
    return m_in.good();
}

void CVisualization::paste(const std::string str) {
    m_out << str;
}

void CVisualization::printBoard(const ChessBoard &board) {
    bool white = false;
    char number = '1';
    pasteEndOfLine("    A   B   C   D   E   F   G   H ");
    for(const auto & row : board){
        pasteEndOfLine("  ---------------------------------");
        paste(number);
        paste(" ");
        //printEmptyRow(white);
        for(const auto & col : row){
            paste("|");
            if( col /*&& col->isActive()*/){
                if(white) paste(BLACK_SQUARE);
                else paste(WHITE_SQUARE);
                printPiece(col);
                if(white) paste(BLACK_SQUARE);
                else paste(WHITE_SQUARE);
            }
            else {
                if(white) {
                    paste(BLACK_SQUARE);
                    paste(BLACK_SQUARE);
                    paste(BLACK_SQUARE);
                }
                else {
                    paste(WHITE_SQUARE);
                    paste(WHITE_SQUARE);
                    paste(WHITE_SQUARE);
                }
            }
            white = !white;

        }
        white = !white;
        paste("|");
        paste(" ");
        paste(number);
        pasteEndOfLine("");
        number++;
    }
    pasteEndOfLine("  ---------------------------------");
    pasteEndOfLine("    A   B   C   D   E   F   G   H \n");
}


void CVisualization::paste(char character) {
    m_out << character;
}

void CVisualization::printPiece(const std::shared_ptr<CAbstractPiece> &piece) {
    if(piece->getColor() == WHITE){
        pasteColoredBlue(piece->pieceChar());
    }
    else pasteColoredMagenta(tolower(piece->pieceChar()));
}

bool CVisualization::getLineInLower(std::string &line) {
    if(!readLine(line))
        return false;
    std::transform(line.begin(), line.end(), line.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return true;
}

void CVisualization::pasteEndOfLine(const std::string str) {
    m_out << str << std::endl;
}

void CVisualization::pasteColoredMagenta(const char str) {
    const std::string magenta("\033[1;31m");
    const std::string reset("\033[0m");
    m_out << magenta << str << reset;
}

void CVisualization::pasteColoredBlue(const char str) {
    const std::string magenta("\033[1;32m");
    const std::string reset("\033[0m");
    m_out << magenta << str << reset;
}

void CVisualization::pasteNumber(int n) {
    m_out << n;
}

std::string CVisualization::getNameOfGame() {
    std::string tmp;
    pasteEndOfLine("Write name under which you want to save game as and confirm with enter. Saving is case-insensitive.");
    pasteEndOfLine("If you want to cancel saving and return to game, write cancel.");
    while(true){
        if(!getLineInLower(tmp) || tmp == "q" || tmp == "quit"){
            throw "quit";
        }
        else if(!tmp.empty()){
            return tmp;
        }
        pasteEndOfLine("Try again.");
    }
}

bool CVisualization::getLineRegular(std::string &line) {
    if(!readLine(line))
        return false;
    return true;
}

bool CVisualization::readLine(std::string &line) {
    m_in.clear();
    if(!getline(m_in, line, '\n'))
        return false;
    if(line.size() > 1) {
        removeWhiteSpace(line);
    }
    return true;
}

void CVisualization::removeWhiteSpace(std::string &line){
    line.erase(line.find_last_not_of((" \n\r\t\f\v")) + 1);
    line.erase(0, line.find_first_not_of((" \n\r\t\f\v")));
}

void CVisualization::getLineForString(std::ifstream &inFile, std::string &line, int &counter) {
    counter++;
    if(!getline(inFile, line)){
        throw std::invalid_argument("No text");
    }
    removeWhiteSpace(line);
}

