#include <sstream>
#include "CAbstractPlayer.h"
#define DrawCounter 50
CBoard CAbstractPlayer::m_board(true);
unsigned int CAbstractPlayer::m_counter = 0;
ECGameState CAbstractPlayer::m_lastMoveGameState;

CAbstractPlayer::CAbstractPlayer(EColor Color) : m_lastMoveGameStateForSave(NO_STATE), m_counterForSave(0), piecesColor(Color), capturedPieces(0) {
    m_counter = 0;
    m_lastMoveGameState = NO_STATE;
}

const ChessBoard &CAbstractPlayer::getBoard() const {
    return m_board.getBoard();
}

EColor CAbstractPlayer::getColorOfPieces() const {
    return piecesColor;
}

SPieceMove CAbstractPlayer::moveDuringCheck(CVisualization &file) {
    SPieceMove move = chooseMove(file);
    while(isMoveInCheck(move)){
        file.paste("Cannot play this move. It's a CHECK.\n");
        move = chooseMove(file);
    }
    return move;
}

bool CAbstractPlayer::isMoveInCheck(SPieceMove &move) {
    CBoard boardTmp(m_board);
    boardTmp.makeMove(move, false);
    return boardTmp.getGameState(piecesColor, true) == CHECK;
}

bool CAbstractPlayer::isStaleMate() const {
    CAI AIForState(piecesColor);
    CCoordinates kingCoordinates = m_board.getKingPos(piecesColor);
    CBoard tmpBoard(m_board);
    SPieceMove move = AIForState.getMovementFromAI(m_board);
    tmpBoard.makeMove(move, false);
    if(tmpBoard.getGameState(piecesColor, false) == NO_STATE){
        return false;
    }
    const auto kingMoves = m_board.getBoard()[kingCoordinates.getRow()][kingCoordinates.getColumn()]->getMoves(kingCoordinates, m_board.getChessBoard(), m_board.getLastMoveMade());
    if(kingMoves.empty()){
        return false;
    }
    for(const auto & kingMove : kingMoves){
        tmpBoard = m_board;
        tmpBoard.makeMove(kingMove, false);
        ECGameState state = tmpBoard.getGameState(piecesColor, 0);
        if(state == NO_STATE){
            return false;
        }
    }
    return  true;
}

std::string CAbstractPlayer::getColorInString(EColor color) const {
    if(color == BLACK){
        return "Black";
    }
    else return "White";
}

int CAbstractPlayer::getCapturedCount() const {
    return capturedPieces;
}


void CAbstractPlayer::writeMove(const SPieceMove &move, CVisualization &file, std::vector<std::string> &moves) const {
    file.paste("Move for ");
    file.paste(getColorInString(piecesColor));
    file.paste(" pieces is: ");
    file.pasteEndOfLine(saveMoveString(move, moves));
}

ECGameState CAbstractPlayer::play(CVisualization &file, std::vector<std::string> &moves) {
    SPieceMove move;
    m_board.updateRealMoves();
    checkStaleMate(file);
    m_board.updateRealMoves();
    try{
        move = getMove(file);
    }
    catch (int i) {
        if (i != 0) {
            throw i;
        }
    }
 /*       if(m_board.getChessBoard().getOpponentsPieces(piecesColor).size() + m_board.getChessBoard().getPlayersPieces(piecesColor).size() < 25){
            if(checkDraw(move, true)){
                file.pasteEndOfLine("We are at draw/check. Thank you for game.");
                throw 3;
            }
        }
        else {
            file.pasteEndOfLine("Draw not accepted.");
            goto NEXTROUND;
        }
    }*/
    if(nonCompleteDraw(move.m_points)){
        //Zjednodusena draw
        file.pasteEndOfLine("We are at draw/check. No piece was taken last 50 moves."
                            "Thank you for game.");
        throw 3;
    }
    if(!m_board.checkKing(move)){
        file.paste("CHECKMATE.");
        file.paste("Winner: ");
        file.pasteEndOfLine(getColorInString(getColorOfPieces()));
        writeMove(move, file, moves);
        throw 3;
    }
    if(m_board.makeMove(move, true)) capturedPieces++;
    writeMove(move, file, moves);
    m_lastMoveGameState = m_board.getGameState(CBoard::getOtherColor(piecesColor), false);
    return m_lastMoveGameState;
}


std::string CAbstractPlayer::saveMoveString(const SPieceMove &move, std::vector<std::string> &moves) const {
    std::string tmp;
    tmp.resize(11);
    tmp[0] = m_board.getBoard()[move.m_to.getRow()][move.m_to.getColumn()]->pieceChar();
    tmp[1] = ' ';
    tmp[2] = move.m_from.getColumn() + 65;
    tmp[3] = move.m_from.getRow() + 49;
    tmp[4] = ' ';
    tmp[5] = 't';
    tmp[6] = 'o';
    tmp[7] = ' ';
    tmp[8] = move.m_to.getColumn() + 65;
    tmp[9] = move.m_to.getRow() + 49;
    tmp[10] = '\n';
    moves.emplace_back(tmp);
    return tmp;
}


bool CAbstractPlayer::readPos(CVisualization &file, CCoordinates &move, std::stringstream &str, bool noMessage) const {
    std::string pos;
    str >> std::skipws >> pos;
    if(!move.savePosition(pos)){
        errorOutput(noMessage, "Wrong tile on board, please, try again." , file);
        return false;
    }
    return true;
}

bool
CAbstractPlayer::readPiece(CVisualization &file, const CCoordinates &from, std::string &piece, bool noMessage) const {
    if(m_board.getBoard()[from.getRow()][from.getColumn()] &&
            m_board.getBoard()[from.getRow()][from.getColumn()]->pieceChar() == toupper(piece[0])){
        return true;
    }
    errorOutput(noMessage, "Incorrect piece.", file);
    return false;
}

bool CAbstractPlayer::isCorrectMove(SPieceMove &move, CVisualization &file, bool noMessage) const {
    if(m_board.getBoard()[move.m_from.getRow()][move.m_from.getColumn()] &&
       m_board.getBoard()[move.m_from.getRow()][move.m_from.getColumn()]->getColor() != piecesColor){
        errorOutput(noMessage, "Wrong position or not your piece, please try again.", file);
        return false;
    }
    else if (!m_board.validMove(move.m_from, move.m_to, move)) {
        errorOutput(noMessage, "Not correct move of the piece. Please, try again.", file);
        return false;
    }
    return true;
}

EPiece CAbstractPlayer::getPieceEnum(const std::string &piece) const {
    char pieceChar = toupper(piece[0]);
    for(size_t i = 0; i < pieces.size(); ++i){
        if(pieces[i] == pieceChar){
            return static_cast<EPiece>(i);
        }
    }
    return NO_PIECE;
}
void CAbstractPlayer::errorOutput(bool noMessage, const std::string &errorLine, CVisualization & file) const {
    if(noMessage){
        throw std::invalid_argument(errorLine);
    }
    file.pasteEndOfLine(errorLine);
}

void CAbstractPlayer::checkStaleMate(CVisualization &file) const {
    if(m_lastMoveGameState == NO_STATE) {
        if (isStaleMate()) {
            file.pasteEndOfLine("We are at stalemate. Thank you for game.");
            throw 3;
        }
    }
}

SPieceMove CAbstractPlayer::getMove(CVisualization &file) {
    if(m_lastMoveGameState == CHECKMATE){
        file.paste(getColorInString(CBoard::getOtherColor(piecesColor)));
        file.paste("pieces won.");
        throw 3;

    }
    else return moveDuringCheck(file);
}

void CAbstractPlayer::promotionOfPawn(SPieceMove &move, CVisualization &file, const std::string & piecePromotion) const {
    EPiece enumPiece;
    if(piecePromotion == " ") {
        enumPiece = playerPromotion(file);
    }
    else {
        enumPiece = getPieceEnum(piecePromotion);
        if(enumPiece == NO_PIECE || !(enumPiece == QUEEN || enumPiece == ROOK || enumPiece == KNIGHT ||
                                enumPiece == BISHOP)){
            throw std::invalid_argument("Invalid piece for promotion.");
        }
    }
    move.m_piece = enumPiece;
}

bool CAbstractPlayer::catchUpGame(CVisualization &file, std::vector<std::string> &moves, std::string &line, bool lastMove, const std::string & move2) {
    m_board.updateRealMoves();
    SPieceMove move;
    splitMove(line, move, file, true);
    if(!isCorrectMove(move, file)){
        throw std::invalid_argument("Incorrect Move");
    }
    if(!m_board.checkKing(move)){
        throw std::invalid_argument("King is taken");
    }
    if(m_lastMoveGameState == CHECK && isMoveInCheck(move)){
        throw std::invalid_argument("Move during check");
    }
    if(move2 != " " && move.m_move == PROMOTION){
        move.m_piece = getPieceEnum(move2);
        if(move.m_piece == NO_PIECE){
            throw std::invalid_argument("Incorrect Move");
        }
    }
    if(m_board.makeMove(move, true)) {
        m_counter = 0;
        capturedPieces++;
    }
    else m_counter++;
    m_lastMoveGameState = m_board.getGameState(CBoard::getOtherColor(piecesColor), 0);
    if(m_lastMoveGameState == CHECKMATE){
        m_lastMoveGameState = m_board.getGameState(CBoard::getOtherColor(piecesColor), 0);
        throw std::invalid_argument("Checkmate");
    }
    if(lastMove){
        writeMove(move, file, moves);
        if(m_lastMoveGameState == CHECK){
            file.pasteEndOfLine("CHECK");
        }
    }
    else saveMoveString(move, moves);
    return false;
}

EPiece CAbstractPlayer::playerPromotion(CVisualization &file) const {
    file.pasteEndOfLine("Choose piece you want promote pawn to: q, r, b, n");
    std::string piece;
    EPiece pieceEnum;
    if (!file.read(piece) || piece == "quit") {
        throw "quit";
    }
    pieceEnum = getPieceEnum(piece);
    while (pieceEnum == NO_PIECE || !(pieceEnum == QUEEN || pieceEnum == ROOK ||
                                    pieceEnum == KNIGHT || pieceEnum == BISHOP)) {
        if (!file.read(piece)) {
            throw "quit";
        }
        pieceEnum = getPieceEnum(piece);
    }
    return pieceEnum;
}

bool CAbstractPlayer::splitMove(std::string &line, SPieceMove &currentMove, CVisualization &file, bool noMessage) const {
    std::stringstream str(line);
    std::string piece;
    str >> std::skipws >> piece;
    if (readPos(file, currentMove.m_from, str, noMessage)) {
        std::string tmp;
        str >> tmp;
        if (readPos(file, currentMove.m_to, str, noMessage)) {
            if(readPiece(file, currentMove.m_from, piece, noMessage)){
                return true;
            }
        }
    }
    return false;
}

void CAbstractPlayer::saveGame() {
    m_board.updateRealMoves();
    m_counterForSave = m_counter;
    m_lastMoveGameStateForSave = m_lastMoveGameState;
    m_board.makeCopyTo(m_boardForSave);
    m_board.resetBoard();
}

void CAbstractPlayer::updateGame() {
    m_boardForSave.makeCopyTo(m_board);
    m_counter = m_counterForSave;
    m_lastMoveGameState = m_lastMoveGameStateForSave;
}

bool CAbstractPlayer::nonCompleteDraw(int points) {

    if (points > 0) {
        m_counter = 0;
        return false;
    } else m_counter++;
    if(m_counter < DrawCounter){
        return false;
    }
    else return true;
}
/*

bool CAbstractPlayer::canSkipDraw(bool forcedCheck, int points) {
    if(forcedCheck){
        m_counter = DrawCounter;
    }
    else {
        if (points > 0) {
            m_counter = 0;
            return true;
        } else m_counter++;
        if(m_counter < DrawCounter){
            return true;
        }
    }
    return false;
}

 bool CAbstractPlayer::checkDraw(const SPieceMove &move, bool forcedCheck) {
    CAI AIForState(piecesColor);
    if(canSkipDraw(forcedCheck, move.points) || (m_board.getChessBoard().getPlayersPieces(piecesColor).size() < 3 && m_board.getChessBoard().getOpponentsPieces(piecesColor).size() > 24)){
        return false;
    }
    if(m_board.getChessBoard().getPlayersPieces(piecesColor).size() < 3 && m_board.getChessBoard().getOpponentsPieces(piecesColor).size() < 4){
        return true;
    }
    if(m_board.getChessBoard().getPlayersPieces(piecesColor).size() < 4 && m_board.getChessBoard().getOpponentsPieces(piecesColor).size() < 3){
        return true;
    }
    if(m_counter == DrawCounter){
        m_counter = 0;
        bool checkDraw = true;
        int depth = 3;
        if(m_board.getChessBoard().getPlayersPieces(piecesColor).size() < 3 || m_board.getChessBoard().getOpponentsPieces(piecesColor).size() < 3){
            --depth;
        }
        AIForState.chooseMove(m_board, depth, -500, 25000, checkDraw, piecesColor, true);
        if(checkDraw) {
            AIForState.chooseMove(m_board, depth, -500, 25000, checkDraw, m_board.getOtherColor(piecesColor), true);
            if(checkDraw){
                return true;
            }
        }
    }
    return false;
}*/
