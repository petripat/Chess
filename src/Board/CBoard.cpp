#include "CBoard.h"

bool CBoard::validMove(CCoordinates &from, CCoordinates &to, SPieceMove &moveOriginal) const {
    std::vector<SPieceMove> possibleMoves = m_board.tiles[from.getRow()][from.getColumn()]->getMoves(from, m_board, m_lastMove);
    for(const auto & move : possibleMoves){
        if(to == move.m_to){
            moveOriginal.m_move = move.m_move;
            return true;
        }
    }
    return false;
}

bool CBoard::tileIsEmpty(const CCoordinates &pos) const {
    if(m_board.tiles[pos.getRow()][pos.getColumn()] == nullptr){
        return true;
    }
    return false;
}

void CBoard::setBoard(EColor Color, int row, int plus){
    m_board.tiles[row][0] = std::make_shared<CRook>(CRook(Color));
    m_board.tiles[row][1] = std::make_shared<CKnight>(CKnight(Color));
    m_board.tiles[row][2] = std::make_shared<CBishop>(CBishop(Color));
    m_board.tiles[row][3] = std::make_shared<CQueen>(CQueen(Color));
    m_board.tiles[row][4] = std::make_shared<CKing>(CKing(Color));
    updateKingPos(Color, {row, 4});
    m_board.tiles[row][5] = std::make_shared<CBishop>(CBishop(Color));
    m_board.tiles[row][6] = std::make_shared<CKnight>(CKnight(Color));
    m_board.tiles[row][7] = std::make_shared<CRook>(CRook(Color));

    m_board.tiles[row + plus][0] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][1] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][2] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][3] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][4] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][5] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][6] = std::make_shared<CPawn>(CPawn(Color));
    m_board.tiles[row + plus][7] = std::make_shared<CPawn>(CPawn(Color));
}
CBoard::CBoard(bool setUp) : m_lastMove() {
    if(setUp) {
        resetBoard();
    }
}

void CBoard::copyPiecesOnBoard(const CCoordinates &from, const CCoordinates &to,
                               std::vector<std::pair<std::shared_ptr<CAbstractPiece>, CCoordinates>> &in) {
    for(int i = from.getRow(); i <= to.getRow(); i++ ){
        for(int j = from.getColumn(); j <= to.getColumn(); j++){
            in.emplace_back(m_board.getBoard()[i][j]->cloneShared(), CCoordinates(i, j));
        }
    }
}

bool CBoard::makeMove(const SPieceMove &move, bool realMove) {
    m_lastMove = move;
    m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->moved();
    if(realMove)
        m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->RealMove();
    m_board.updateArrays(m_lastMove);
    if(tileIsEmpty(move.m_to)){
        return makeMoveToEmptyTile(move);
    }
    if(m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()] && m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->isKing()){
        updateKingPos(m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->getColor(), move.m_to);
    }
    m_lastMove.m_points = m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]->getValue();
    movePiece(move.m_from, move.m_to);
    return true;
}

void CBoard::movePiece(const CCoordinates &from, const CCoordinates &to) {
    m_board.tiles[to.getRow()][to.getColumn()].reset();
    m_board.tiles[to.getRow()][to.getColumn()] = m_board.tiles[from.getRow()][from.getColumn()];
    m_board.tiles[from.getRow()][from.getColumn()].reset();
}

SPieceMove CBoard::getLastMoveMade() const {
    return m_lastMove;
}

CBoard::CBoard(const CBoard & board) {
    *this = board;
}

void CBoard::updateKingPos(EColor color, const CCoordinates &coordinates) {
    if(color == WHITE){
        m_kingWhitePos = coordinates;
    }
    else m_kingBlackPos = coordinates;
}

CCoordinates CBoard::getKingPos(EColor color) const {
    if(color == BLACK)
        return m_kingBlackPos;
    else return m_kingWhitePos;
}

void CBoard::promotion(const SPieceMove &move) {
    EColor color = m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->getColor();
    m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()].reset();
    if(move.m_piece == QUEEN){
        m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()] = std::make_shared<CQueen>(CQueen(color));
    }
    else if(move.m_piece == BISHOP){
        m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()] = std::make_shared<CBishop>(CBishop(color));
    }
    else if(move.m_piece == KNIGHT){
        m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()] = std::make_shared<CKnight>(CKnight(color));
    }
    else if(move.m_piece == ROOK){
        m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()] = std::make_shared<CRook>(CRook(color));
    }
    m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()].reset();
}

void CBoard::moveRookDuringCastling(const SPieceMove &move) {
    if(move.m_to.operator==({move.m_to.getRow(), 2})){
        movePiece({move.m_to.getRow(), 0}, {move.m_to.getRow(), 3});
    }
    else{
        movePiece({move.m_to.getRow(), 7}, {move.m_to.getRow(), 5});
    }
}

const ChessBoard &CBoard::getBoard() const {
    return m_board.tiles;
}

const CChessBoard &CBoard::getChessBoard() const {
    return m_board;
}

ECGameState CBoard::getGameState(EColor colorOfPlayer, bool playerOnRow) const {
    std::vector<SPieceMove> checkPieces = isCheck(getKingPos(colorOfPlayer), true);
    if(!checkPieces.empty()){
        if(playerOnRow){
            if(checkPieces.size() > 1 || !checkForKiller(colorOfPlayer, *(checkPieces.begin()))){
                if(!checkForScapegoat(colorOfPlayer)){
                    return CHECKMATE;
                }
            }
        }
        else {
            if (checkCheckAroundKing(getKingPos(colorOfPlayer))) {
                if (checkPieces.size() > 1 || !checkForKiller(colorOfPlayer, *(checkPieces.begin()))) {
                    if (!checkForScapegoat(colorOfPlayer)) {
                        return CHECKMATE;
                    }
                }
            }
        }
    }
    else return NO_STATE;
    return CHECK;
}

bool CBoard::checkForScapegoat(EColor colorOfPlayer) const {
    bool in = false;
    for(const auto & piece : getChessBoard().getPlayersPieces(colorOfPlayer)){
        if(!(piece.second == getKingPos(colorOfPlayer))){
            for(const auto & pos : piece.first->getMoves(piece.second, getChessBoard(), m_lastMove)){
                in = true;
                CBoard tmpBoard(*this);
                tmpBoard.makeMove(pos, false);
                if(tmpBoard.isCheck(tmpBoard.getKingPos(colorOfPlayer), false).empty()){
                    return true;
                }
            }
        }
    }
    if (!in) return false;
    return false;
}

bool CBoard::checkForKiller(EColor colorOfPlayer, const SPieceMove &checkPiece) const {
    auto tmp = getChessBoard().getPlayersPieces(colorOfPlayer);
    for(const auto & piece : tmp){
        CBoard tmpBoard(*this);
        for(const auto & moveOfPiece : piece.first->getMoves(piece.second, getChessBoard(), m_lastMove)){
            if(checkPiece.m_from == moveOfPiece.m_to){
                tmpBoard.makeMove(moveOfPiece, false);
                if(tmpBoard.isCheck(tmpBoard.getKingPos(colorOfPlayer), false).empty()){
                    return true;
                }
                if(moveOfPiece.m_move == CASTLING || moveOfPiece.m_move == ENPASSANT){
                    tmpBoard = *this;
                }
                else tmpBoard.updateTo(*this, moveOfPiece);
            }
        }
    }
    return false;
}

bool CBoard::checkCheckAroundKing(const CCoordinates &coordinates) const {
    CBoard tmpBoard(*this);
    for(const auto & potentialPositionOfKing :
            m_board.getBoard()[coordinates.getRow()][coordinates.getColumn()]->getMoves(coordinates, getChessBoard(), m_lastMove)){
        tmpBoard.makeMove(SPieceMove(potentialPositionOfKing.m_from, potentialPositionOfKing.m_to,
                                     tmpBoard.getBoard()[potentialPositionOfKing.m_from.getRow()][potentialPositionOfKing.m_from.getColumn()]->getValue()),
                          false);
        if(tmpBoard.isCheck(potentialPositionOfKing.m_to, false).empty()) return false;
        if(potentialPositionOfKing.m_move == CASTLING || potentialPositionOfKing.m_move == ENPASSANT){
            tmpBoard = *this;
        }
        else tmpBoard.updateTo(*this, potentialPositionOfKing);
    }
    return true;
}

bool CBoard::isThreat(const CCoordinates &coordinatesOfKing, const CCoordinates &threatPiece) const {
    if(m_board.tiles[threatPiece.getRow()][threatPiece.getColumn()]){
        for(const auto & pos : m_board.tiles[threatPiece.getRow()][threatPiece.getColumn()]->getMoves(threatPiece, m_board, m_lastMove)){
            if(coordinatesOfKing == pos.m_to){
                return true;
            }
        }
    }
    return false;
}

std::vector<SPieceMove> CBoard::isCheck(const CCoordinates &coordinatesOfKing, bool saveMove) const {
    std::vector<SPieceMove> checkPieces;
    auto positions = m_board.tiles[coordinatesOfKing.getRow()][coordinatesOfKing.getColumn()]->generateMoves(coordinatesOfKing, m_board.tiles, true);
    for(const auto & possiblePositionOfOpponentsPiece : positions){
        if(isThreat(coordinatesOfKing, possiblePositionOfOpponentsPiece.m_to)){
            checkPieces.emplace_back(possiblePositionOfOpponentsPiece.m_to, coordinatesOfKing);
            if(saveMove){}
            else {
                return checkPieces;
            }
        }
    }
    checkKnights(coordinatesOfKing, checkPieces, saveMove);
    return checkPieces;
}

bool CBoard::makeMoveToEmptyTile(const SPieceMove &move) {
    if(m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()] && m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->isKing()){
        updateKingPos(m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->getColor(), move.m_to);
    }
    if(move.m_move != NO_MOVE) {
        if (move.m_move == ENPASSANT) {
            m_board.tiles[move.m_from.getRow()][move.m_to.getColumn()].reset();
            movePiece(move.m_from, move.m_to);
            return true;
        } else if (move.m_move == PROMOTION) {
            promotion(move);
            return false;
        } else if (move.m_move == CASTLING) {
            moveRookDuringCastling(move);
            updateKingPos(m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->getColor(), move.m_to);
        }
    }
    m_lastMove.m_points = 0;
    movePiece(move.m_from, move.m_to);
    return false;
}

EColor CBoard::getOtherColor(EColor color) {
    if (color == WHITE){
        return BLACK;
    }
    else return WHITE;
}

CBoard &CBoard::operator=(const CBoard &rhs) {
    if(&rhs == this){
        return *this;
    }
    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COL; ++j){
            if(rhs.m_board.tiles[i][j]){
                m_board.tiles[i][j] = rhs.m_board.tiles[i][j]->cloneShared();
            }
            else m_board.tiles[i][j].reset();
        }
    }
    m_board = rhs.m_board;
    m_lastMove = rhs.m_lastMove;
    m_kingBlackPos = rhs.m_kingBlackPos;
    m_kingWhitePos = rhs.m_kingWhitePos;
    return *this;
}

bool CBoard::checkKing(const SPieceMove &move) const {
    if(move.m_to == getKingPos(WHITE) || move.m_to == getKingPos(BLACK)){
        return false;
    }
    return true;
}

void CBoard::updateRealMoves() {
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < ROWS; j++){
            if(m_board.tiles[i][j]){
                m_board.tiles[i][j]->updateMoved();
            }
        }
    }
}

void CBoard::checkKnights(const CCoordinates &coordinatesOfKing, std::vector<SPieceMove> &checkPieces, bool saveMove) const {
    std::vector<CCoordinates> movesOfKnight = {{-2,1}, {-2,-1},{2,-1}, {2,1},
                                           {-1,2}, {-1,-2},{1,-2}, {1,2}};
    CCoordinates tmpPos = coordinatesOfKing;
    for(const auto & move : movesOfKnight){
        tmpPos+=move;
        if(tmpPos.getRow() >= 0 && tmpPos.getRow() < ROWS && tmpPos.getColumn() >= 0 && tmpPos.getColumn() < COL) {
            if(isThreat(coordinatesOfKing, tmpPos)){
                checkPieces.emplace_back(tmpPos, coordinatesOfKing);
                if(saveMove){}
                else {
                    return;
                }
            }
        }
        tmpPos = coordinatesOfKing;
    }
}

void CBoard::updateTo(const CBoard &boardOriginal, const SPieceMove &move) {
    //najdu piece, ktery se pohnul naposled a vratim jej
    for(auto & a : m_board.getPlayersPieces(boardOriginal.m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->getColor())){
        if(a.second == move.m_to){
            a.second = move.m_from;
            break;
        }
    }
    //pokud byla na to souradnici figurka, tak ji vratim zpet
    if(boardOriginal.m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]){
        for(auto & a : boardOriginal.m_board.getPlayersPieces(boardOriginal.m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]->getColor())){
            if(a.second == move.m_to){
                m_board.getPlayersPieces(boardOriginal.m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]->getColor()).emplace_back(a.first, a.second);
                break;
            }
        }
    }
    //resetuju policka a dam na ne spravne figurky
    m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()].reset();
    m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()] = boardOriginal.m_board.tiles[move.m_from.getRow()][move.m_from.getColumn()]->cloneShared();
    if(boardOriginal.m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]){
        m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()] = boardOriginal.m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()]->cloneShared();
    }
    else m_board.tiles[move.m_to.getRow()][move.m_to.getColumn()].reset();
    m_lastMove = boardOriginal.m_lastMove;
    m_kingBlackPos = boardOriginal.m_kingBlackPos;
    m_kingWhitePos = boardOriginal.m_kingWhitePos;
}

void CBoard::resetBoard() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COL; c++) {
            m_board.tiles[r][c].reset();
        }
    }
    setBoard(BLACK, 0, 1);
    setBoard(WHITE, 7, -1);
    for (int r = 2; r < ROWS - 2; r++) {
        for (int c = 0; c < COL; c++) {
            m_board.tiles[r][c] = nullptr;
        }
    }
    m_board.piecesWhite.clear();
    m_board.piecesBlack.clear();
    copyPiecesOnBoard({0, 0}, {1, 7}, m_board.piecesBlack);
    copyPiecesOnBoard({6, 0}, {7, 7}, m_board.piecesWhite);
}

void CBoard::makeCopyTo(CBoard &boardForSave) {
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COL; j++){
            if(m_board.tiles[i][j]){
                boardForSave.m_board.tiles[i][j] = m_board.tiles[i][j]->cloneShared();
            }
            else boardForSave.m_board.tiles[i][j].reset();
        }
    }
    boardForSave.m_board = m_board;
    boardForSave.m_lastMove = m_lastMove;
    boardForSave.m_kingBlackPos = m_kingBlackPos;
    boardForSave.m_kingWhitePos = m_kingWhitePos;
}







