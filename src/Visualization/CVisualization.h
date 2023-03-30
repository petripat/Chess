#ifndef PETRIPAT_CVISUALIZATION_H
#define PETRIPAT_CVISUALIZATION_H

#include <iostream>
#include "../CChessBoard/CChessBoard.h"
#include "../AbstractPiece/CAbstractPiece.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#define WHITE_SQUARE ' '
#define BLACK_SQUARE '#'

/*
 * @brief CVisualization class communicates with player. Draws m_board and has function to read or print.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CVisualization {
    std::istream & m_in; /** stream for input*/
    std::ostream & m_out; /** stream for output*/
public:
    /**
     * @param in - sets up m_in asi std::cin unless different istream is provided
     * @param out - sets up m_out as std::cout unless different ostream is provided
     */
    CVisualization(std::istream & in = std::cin, std::ostream & out = std::cout);
    /**
     * Reads input from playerPieces.
     * @return string written by playerPieces
     */
    bool read(std::string &read);
    /**
     * Prints string for playerPieces to read.
     * @param str - string containing message for playerPieces
     */
    void paste(const std::string str);
    /**
     * Prints char in red for playerPieces to read.
     * @param str - char to print out
     */
    void pasteColoredMagenta(const char str);
    /**
     * Print string with std::endl
     * @param str - string to print out
     */
    void pasteEndOfLine(const std::string str);
    /**
     * Prints character
     * @param character
     */
    void paste(char character);
    /**
     * Print string
     * @param str - string to print out
     */
    void paste(std::string & str);
    /**
     * Print number
     * @param n - number to print
     */
    void pasteNumber(int n);
    /**
     * Prints m_board
     * @param board - m_board to print out
     * @param ColorOfPlayerOnRow  - color of currently playing playerPieces
     */
    void printBoard(const ChessBoard &board);
    /**
     * Method that prints piece
     * @param piece - pointer to piece to print out
     * @param color - color of piece
     */
    void printPiece(const std::shared_ptr<CAbstractPiece> &piece);
    /**
     * Read line in m_in and saves it std::string line in lower cases.
     * @param line  - string to save line in
     * @return true - string read ok
     *          false - EOF
     */
    bool getLineInLower(std::string &line);
    /**
     * Read line in m_in and saves it std::string line in lower cases.
     * @param line  - string to save line in
     * @return true - string read ok
     *          false - EOF
     */
    bool getLineRegular(std::string &line);
    /**
     * Prints char in blue for playerPieces to read.
     * @param str - char to print out
     */
    void pasteColoredBlue(const char str);
    /**
     * Reads name of game to save game under.
     * @return name of game
     */
    std::string getNameOfGame();
    /**
     * @param line - string to save line in
     * @return true - reading succesfull
      */
    bool readLine(std::string &line);
    /*&*
     * Method for removing whitespaces at the end of string.
     */
    static void removeWhiteSpace(std::string &line);
    /**
     * Reads string from ifstream inFile
     * @param inFile
     * @param line - read string
     * @param counter - DrawCounter of lines read
     */
    static void getLineForString(std::ifstream &inFile, std::string &line, int &counter);
};


#endif //PETRIPAT_CVISUALIZATION_H