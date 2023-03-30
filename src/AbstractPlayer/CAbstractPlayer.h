#ifndef PETRIPAT_CABSTRACTPLAYER_H
#define PETRIPAT_CABSTRACTPLAYER_H
#include "../AI/CAI.h"
#include <sstream>

/**
 * @brief Parent class to CComputer player nad CPlayer playerPieces.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CAbstractPlayer {
    /*
     * Method that checks draw after 25 moves without captured pieces in game.
     * @param move - last move chosen
     * @return true - is draw
     *         false - no draw
    bool checkDraw(const SPieceMove &move, bool forcedCheck);
      */
     /** Method that checks draw after 50 moves without captured pieces in game.
     * @param move - last move chosen
     * @return true - is draw
     *         false - no draw
     */
     bool nonCompleteDraw(int points);
   /* @param forcedCheck - true, draw will not be skipped
     * @param points - points of the last move made
     * @return true - draw can be skipped
    bool canSkipDraw(bool forcedCheck, int points);
     */
    /**
     * Method that makes sure that player is not trying to move during a game.
     * @param file - file for communication
     * @return move that is not trying to move during game
     */
    SPieceMove moveDuringCheck(CVisualization &file);

    /**
     * Method that checks check - king cannot move anywhere without pieces capturing him
     * @return true - is check
     *         false - no check
     */
    bool isStaleMate() const;
    static ECGameState m_lastMoveGameState; /** players state of game after last move */
    ECGameState m_lastMoveGameStateForSave; /** players state of game after last move */
    static unsigned int m_counter; /** m_counter of moves made in game without piece getting thrown out */
    unsigned int m_counterForSave; /** m_counter of moves made in game without piece getting thrown out */
    CBoard m_boardForSave;
    /**
     * Method that writes out given move.
     * @param move - move to write out
     * @param file - file to write it out to
     */
    void writeMove(const SPieceMove &move, CVisualization &file, std::vector<std::string> &moves) const;
protected:
    static CBoard m_board; /** Static m_board on which are all playerPieces playing at */
    const EColor piecesColor; /** m_colorOfPieces of pieces playerPieces is playing with */
    int capturedPieces; /** m_counter of captured opponent's pieces */
    CAbstractPlayer(const CAbstractPlayer & rhs) :  piecesColor(rhs.piecesColor),
                                                    capturedPieces(rhs.capturedPieces) {
        m_lastMoveGameStateForSave = rhs.m_lastMoveGameStateForSave;
        m_boardForSave = rhs.m_boardForSave;
        m_counterForSave = rhs.m_counterForSave;
    }
public:
    /**
     * Constructor that sets up m_colorOfPieces and initialises m_counter of destroyed pieces
     * @param Color - m_colorOfPieces of players pieces - enum ECColor from ECColor.h
     */
    explicit CAbstractPlayer(EColor Color);
    /**
     * Vitual default destructor.
     */
    virtual ~CAbstractPlayer() = default;
    /**
     * Play of playerPieces - chooses move, makes it and return state of game.
     * @param file - CVisualization class for communication
     * @return enum ECGameState from ECGameState.h for state of game
     */
    ECGameState play(CVisualization &file, std::vector<std::string> &moves);
    /**
     * Virtual function for choosing next move called from play.
     * @param file - CVisualization class for communication
     * @return chosen move represented by struct SPieceMove from SPieceMove.h
     */
    virtual SPieceMove chooseMove(CVisualization &file) const = 0;
    /**
     * @return m_board represented by array with pieces on which are players playing at
     */
    const ChessBoard& getBoard() const;
    /**
     * @return m_colorOfPieces of players pieces - enum ECColor from ECColor.h
     */
    EColor getColorOfPieces() const;
    /**
     * Possible to use in combination with CBoard method getOtherColor();
     * @param color - enum value from EColor
     * @return Color given in string.
     */
    std::string getColorInString(EColor color) const;
    /**
     * @return count of captured pieces
     */
    int getCapturedCount() const;
    /**
     * Creates unique pointer to instance of CComputer.
     */
    virtual std::unique_ptr<CAbstractPlayer> cloneUnique() const = 0;
    /**
     * Method that saves game.
     */
    void saveGame();
    /**
     * Method that updates saved game for play.
     */
    void updateGame();
    /**
     * Saves move to string for printing.
     * @param move - move to save
     * @param moves - vector of all moves during game
     * @return created move string
     */
    std::string saveMoveString(const SPieceMove &move, std::vector<std::string> &moves) const;
    /**
     * Catches up game after loading from file.
     * @param file - CVisualization game for communication
     * @param moves - vector of moves
     * @return
     */
    bool catchUpGame(CVisualization &file, std::vector<std::string> &moves, std::string &line, bool lastMove = false, const std::string & move2 = " ");
    void resetBoard(){
        m_board.resetBoard();
    }
protected:
    std::vector<char> pieces = {'K', 'Q', 'R', 'N', 'B', 'P'}; /** vector of possible format of pieces */
    /**
     * Method that gets valid movements of chosen piece and checks if playerPieces choose correct move.
     * @param move - possible next move of playerPieces
     * @param file - CVisualization class for communication
     * @return true - move is correct
     *         false - move is wrong
     */
    bool isCorrectMove(SPieceMove &move, CVisualization &file, bool noMessage = false) const;
    /**
     * Method that reads piece and checks if it is existing piece.
     * @param file - CVisualization class for communication
     * @param movePiece - enum representing piece
     * @param str - stream from which is piece read
     * @return true - piece is correctly written
     *          false - piece is written incorectly
     */
    bool readPiece(CVisualization &file, const CCoordinates &from, std::string &piece, bool noMessage = false) const;
    /**
     * Method for reading and checking correctness of position.
     * @param file file - CVisualization class for communication
     * @param move - possible position
     * @param str - stream from which read possible position
     * @return true - piece position is correctly written
     *          false - piece position is wrong
     */
    bool readPos(CVisualization &file, CCoordinates &move, std::stringstream &str, bool noMessage = false) const;
    /**
     * Method that transform piece string to enum represantation of piece.
     * @param piece - - string with piece written in one letter
     * @return enum EPiece representing piece from ECPiece.h
     */
    EPiece getPieceEnum(const std::string &piece) const;
    /**
     * If playerPieces choose promotion of pawn this method is called and asks which pieces does opponentPieces want promote piece to.
     * @param move - promotion move of pawn to choose desired piece for
     * @param file - - CVisualization class for communication
     */
    void promotionOfPawn(SPieceMove &move, CVisualization &file, const std::string & piecePromotion = " ") const;
    /**
     * Method to check if move made results in check while in check
     * @param move - move to be made
     * @return - yes, move will result in check
     */
    bool isMoveInCheck(SPieceMove &move);
    /**
     * Splits string move to current move
     * @param line - string with written move
     * @param currentMove - move to be created
     * @param file - CVisualization file for communication
     * @param noMessage - instead of communication with player, sends exception
     * @return
     */
    bool splitMove(std::string & line, SPieceMove & currentMove, CVisualization & file, bool noMessage = false) const;
    /**
     * Prints out error output.
     * @param noMessage - if true, no output is printed out but exception is send
     * @param errorLine - line to print
     * @param file - file for printing line to
     */
    void errorOutput(bool noMessage, const std::string &errorLine, CVisualization & file) const;
    /**
     * Checks check.
     * @param file - CVisualization file for communication.
     */
    inline void checkStaleMate(CVisualization &file) const;
    /**
     * Gets move from player.
     * @param file - CVisualization file for communication
     * @return created piece
     */
    SPieceMove getMove(CVisualization &file);
    /**
     * Takes care of communication with player about promotion of pawn.
     * @param file  - file for communication
     * @return piece to promote pawn to
     */
    EPiece playerPromotion(CVisualization &file) const;

};

#endif //PETRIPAT_CABSTRACTPLAYER_H