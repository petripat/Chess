#include "CAI.h"
#include <cstddef>
#include <iostream>
#include <climits>
#define WHITE_SQUARE ' '
#define BLACK_SQUARE '#'
#define CHECKMATE_VAL 100000
#define CHECK_VAL 100
#define COEFFICIENT 11
//EColor CAI::m_colorOfPieces;

CAI::CAI(EColor color) {
    m_colorOfPieces = color;
}

long long int CAI::evaluateBoard(const CBoard &board, EColor color, long long int points) const {
    long long int score = points;
    for (const auto & piece : board.getChessBoard().getPlayersPieces(color)){
        score += piece.first->getValue();
    }
    for (const auto & pieceOpponent : board.getChessBoard().getOpponentsPieces(color)){
        score -= pieceOpponent.first->getValue();
    }
    return score;
}

std::vector<SPieceMove> CAI::generateMoves(const CBoard &board, EColor color) const {
    std::vector<SPieceMove> moves;
    for (const auto &piece: board.getChessBoard().getPlayersPieces(color)) {
        for (auto &move: piece.first->getMoves(piece.second, board.getChessBoard(), board.getLastMoveMade())) {
            moves.emplace_back(move);
        }
    }
    std::sort(moves.begin(), moves.end());
    std::reverse(moves.begin(), moves.end());
    return moves;
}

SPieceMove CAI::chooseMove(const CBoard &board, int depth, EColor color) const {
    std::vector<SPieceMove> allBestMoves;
    SPieceMove bestMove;
    CBoard boardTmp(board);
    long long int perfTest = 0;
    long long int eval;
    long long int points;
    long long int overallMaximum = LLONG_MIN;
    long long int alpha = LLONG_MIN, beta = LLONG_MAX;
    for(const auto & piece : board.getChessBoard().getPlayersPieces(color)) {
//        if (depth > 1)
//            std::cout << " " << piece.first->pieceChar() << std::endl;
        for (auto &move : piece.first->getMoves(piece.second, board.getChessBoard(), board.getLastMoveMade())){
            points = 0;
//            if (depth > 1) {
//                std::cout << " Move from: " << piece.second.getRow() + 1 << " "
//                          << (char ) (piece.second.getColumn() + 'A')
//                          << " Move to: " << move.m_to.getRow() + 1 << " " << (char) (move.m_to.getColumn() + 'A')
//                          << " Move points: " << move.m_points
//                          << " Points: " << std::endl;
//            }
            boardTmp.makeMove(move, false);
            ECGameState state = boardTmp.getGameState(piece.first->getColor(), true);
            if(state == CHECK || state == CHECKMATE){
                if(move.m_move == CASTLING || move.m_move == ENPASSANT){
                    boardTmp = board;
                }
                else boardTmp.updateTo(board, move);
                boardTmp.updateRealMoves();
                continue;
            }
            else {
                state = boardTmp.getGameState(CBoard::getOtherColor(piece.first->getColor()), false);
                if(state == CHECKMATE) {
                    points = CHECKMATE_VAL;
                }
                else if(state == CHECK){
                    points = CHECK_VAL;
                }
                points += move.m_points;
                if(depth - 1 != 0)
                    eval = minimaxMinimazing(depth - 1, alpha, beta, boardTmp, color, perfTest, points);
            }
            if(isMax(overallMaximum, eval, bestMove, move)) {
                allBestMoves.clear();
                allBestMoves.emplace_back(move);
            }
            else if(eval == overallMaximum){
                allBestMoves.emplace_back(move);
            }
            if (depth > 1) {
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
//                std::cout << "Best move" << std::endl;
                    return bestMove;
                }
            }
            if(move.m_move == CASTLING || move.m_move == ENPASSANT){
                boardTmp = board;
            }
            else boardTmp.updateTo(board, move);
//            if(depth > 1)
//                std::cout << " " << eval << " " << std::endl;
            boardTmp.updateRealMoves();
        }
    }
    if(allBestMoves.size() > 1){
        unsigned int random = rand() % allBestMoves.size();
        bestMove = allBestMoves[random];
    }
    return bestMove;
}


long long int
CAI::minimaxMaximizing(int depth, long long int alpha, long long int beta, const CBoard &board, EColor color,
                       long long int &perfTest, long long int points) const {
    CBoard boardTmp(board);
    long long int maximum = LLONG_MIN;
    long long int eval;
    long long int add;
    //get all possible my moves
    auto moves = generateMoves(board, color);
    for (auto & currentMove : moves) {
        add = currentMove.m_points;
        boardTmp.makeMove(currentMove, false);
//        std::cout << "               Move from: " << currentMove.m_from.getRow() + 1 << " "
//                  << (char ) (currentMove.m_from.getColumn() + 'A')
//                  << " Move to: " << currentMove.m_to.getRow() + 1 << " " << (char) (currentMove.m_to.getColumn() + 'A') << " ";
        ECGameState state = boardTmp.getGameState(boardTmp.getChessBoard().getBoard()[currentMove.m_to.getRow()][currentMove.m_to.getColumn()]->getColor(), true);
        if (state == CHECKMATE) {
            add -= CHECKMATE_VAL;
        }
        else if (state == CHECK) add -= CHECK_VAL;
        if(depth - 1 != 0) {
            eval = minimaxMinimazing(depth - 1, alpha, beta, boardTmp, color, perfTest, points + add);
        }
        else eval = evaluateBoard(boardTmp, color, points);
//        std::cout << eval << std::endl;
        if(currentMove.m_move == CASTLING || currentMove.m_move == ENPASSANT){
            boardTmp = board;
        }
        else boardTmp.updateTo(board, currentMove);
        maximum = std::max(maximum, eval);
        alpha = std::max(alpha, maximum);
        if(beta <= alpha) {
            return alpha;
        }
    }
//    std::cout << "    Max: " << maximum << std::endl;
    return maximum;
}

long long int
CAI::minimaxMinimazing(int depth, long long int alpha, long long int beta, const CBoard &board, EColor color,
                       long long int &perfTest, long long int points) const {
    CBoard boardTmp(board);
    long long int minimum = LLONG_MAX;
    long long int eval;
    long long int add;
    auto moves = generateMoves(board, board.getOtherColor(color));
    for (auto & currentMove : moves) {
        boardTmp.makeMove(currentMove, false);
        if (currentMove.m_points > 0) add = 0 - 1 - currentMove.m_points;
        else add = 0;
//        std::cout << "      Move from: " << currentMove.m_from.getRow() + 1 << " "
//                  << (char) (currentMove.m_from.getColumn() + 'A')
//                  << " Move to: " << currentMove.m_to.getRow() + 1 << " " << (char) (currentMove.m_to.getColumn() + 'A') << " ";
        ECGameState state = boardTmp.getGameState(board.getOtherColor(color), true); //ja jsem v check"
        if (state == CHECKMATE) add += CHECKMATE_VAL;
        else if (state == CHECK) add += CHECK_VAL;
        state = boardTmp.getGameState(boardTmp.getChessBoard().getBoard()[currentMove.m_to.getRow()][currentMove.m_to.getColumn()]->getColor(), true); //ja jsem v check
        if (state == CHECKMATE) add -= CHECKMATE_VAL;
        else if (state == CHECK) add -= CHECK_VAL;
        if(depth - 1 != 0)
            eval = minimaxMaximizing(depth - 1, alpha, beta, boardTmp, color, perfTest, points + add);
        else eval = evaluateBoard(boardTmp, color, points + add);
//        std::cout << eval << std::endl;
        if(currentMove.m_move == CASTLING || currentMove.m_move == ENPASSANT){
            boardTmp = board;
        }
        else boardTmp.updateTo(board, currentMove);
        minimum = std::min(minimum, eval);
        beta = std::min(beta, minimum);
        if(beta <= alpha) {
            return beta;
        }
    }
//    std::cout << "      Minimum: " << minimum << std::endl;
    return minimum;
}

std::unique_ptr<CAI> CAI::cloneUnique() const {
    return std::make_unique<CAI>(*this);
}

SPieceMove CAI::getMovementFromAI(const CBoard &board) const {
    return chooseMove(board, 1, m_colorOfPieces);
}


bool CAI::isMax(long long int &currentMax, long long int &newMax, SPieceMove &currentMaxMove, SPieceMove &newMaxMove) const {
    if(currentMax < newMax){
        currentMax = newMax;
        currentMaxMove = newMaxMove;
        return true;
    }
    return false;
}




