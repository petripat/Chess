#ifndef PETRIPAT_CAI_H
#define PETRIPAT_CAI_H
#include "../Board/CBoard.h"
#include <climits>

/**
 * @brief Parent class to AI levels - CMedium, CHard, CEasy with method to check draw.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CAI {

private:
    /**
     * Evaluates state of board and returns points based on pieces left on.
     * @param board - board to be evaluated
     * @param color - color of player on row
     * @param points - points given during minimax
     * @return overall state - points
     */
    long long int evaluateBoard(const CBoard &board, EColor color, long long int points) const;
    /**
     * Generates all moves that can be made on board sorted by points of move.
     * @param board - board where pieces are
     * @param color - color of pieces to generate moves for
     * @return sorted vector of SPieceMove representing move
     */
    std::vector<SPieceMove> generateMoves(const CBoard &board, EColor color) const;
/**
 * Function that decides if value is new max and updates current best move - for maximizing.
 * @param currentMax - current value of best move
 * @param newMax - possibly new value of best move
 * @param currentMaxMove - current best move
 * @param newMaxMove - possibly better move
 * @return true - value was updated
 *         false - value remains unchanged
 */
    bool isMax(long long int &currentMax, long long int &newMax, SPieceMove & currentMaxMove, SPieceMove & newMaxMove) const;
     /**
      * Recursion which makes move of opponentPieces and chooses move for computer which get most points it gets from upcoming moves based on first move
      * @param depth - desired depth of recursion
      * @param alpha - minimal value of points - if point get below this value, recursion stops
      * @param beta - maximal value of points - if point get above this value, recursion stops (CHECKMATE, king capture)
      * @param board - m_board at which are players playing at
      * @param portion  - value move will be multiplied - get's lower every round
      * @param color  - color of players pieces to check move of
      * @param perfTest - for perf testing purposes
      * @param points - points given for taking piece
      * @return value of all moves done
      */
     long long int
     minimaxMaximizing(int depth, long long int alpha, long long int beta, const CBoard &board, EColor color,
                       long long int &perfTest, long long int points) const;
     /**
     * Recursion which makes move of opponentPieces and chooses move for computer which get most points it gets from upcoming moves based on first move
     * @param depth - desired depth of recursion
     * @param alpha - minimal value of points - if point get below this value, recursion stops
     * @param beta - maximal value of points - if point get above this value, recursion stops (CHECKMATE, king capture)
     * @param board - m_board at which are players playing at
     * @param color - color of players pieces to check move of
     * @param perfTest - for perf testing purposes
     * @param points - points given for taking piece
     * @return value of all moves done
      */
     long long int
    minimaxMinimazing(int depth, long long int alpha, long long int beta, const CBoard &board, EColor color,
                      long long int &perfTest, long long int points) const;
protected:
    EColor m_colorOfPieces; /** color of player's pieces*/
    /**
     * * Method that starts recursion with minimaxMinimazing and remembers starting moves.
     * @param board - m_board on which game is at represented by array with pointer on pieces
     * @param depth - desired depth of recursion
     * @param color -- color of players pieces to check move of - default color of AI's pieces
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    SPieceMove chooseMove(const CBoard &board, int depth, EColor color) const;
public:
    /**
     * Constructor that sets up m_colorOfPieces of AI and vector pieces and opponentPieces pieces.
     * @param color - m_colorOfPieces of AI
     */
    CAI(EColor color);
    /**
     * Virtual method that gets move based on difficulty of AI.
     * Default is return movefrom 0,0 to 0,0
     * @param board - m_board on which game is at represented by array with pointer on pieces
     * @return chosen move of AI's difficulty represented by struct SPieceMove from SPieceMove.h
     */
    virtual SPieceMove getMovementFromAI(const CBoard &board) const;
    /**
     * virtual default destructor for CAI.
     */
    virtual ~CAI() = default;
    /**
     * CCreates unique pointer to instance of CAI.
     */
    virtual std::unique_ptr<CAI> cloneUnique() const;
};

#endif //PETRIPAT_CAI_H




