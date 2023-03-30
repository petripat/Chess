#include <iostream>
#include "CCoordinates.h"


bool CCoordinates::savePosition(std::string & position){
    if(position.length() != 2){
        return false;
    }
    char colChar = toupper(position[0]);
    char rowChar = toupper(position[1]);
    column = colChar - 65;
    row = rowChar - 49;
    if(column < 0 || column > 7 || row < 0 || row > 7){
        return false;
    }
    else return true;
    std::cout << "position on m_board" << position << "   " << column << row << std::endl;
}

int CCoordinates::getRow() const {
    return row;
}

int CCoordinates::getColumn() const {
    return column;
}

CCoordinates::CCoordinates(int rowY, int columnX) : row(rowY), column(columnX) {}

CCoordinates &CCoordinates::operator+=(const CCoordinates &rhs) {
    column+=rhs.column;
    row+=rhs.row;
    return *this;
}

bool CCoordinates::operator==(const CCoordinates &rhs) const {
    return column == rhs.column && row == rhs.row;
}

CCoordinates CCoordinates::operator+(const CCoordinates &rhs) const {
    return {row+rhs.row, column+rhs.column};
}

CCoordinates &CCoordinates::operator=(const CCoordinates &rhs) {
    row = rhs.row;
    column = rhs.column;
    return *this;
}

CCoordinates::CCoordinates(const CCoordinates &cor) {
    row = cor.row;
    column = cor.column;
}

bool CCoordinates::operator<(const CCoordinates &rhs)  const {
    return row < rhs.row || (row == rhs.row && column < rhs.column);
}

