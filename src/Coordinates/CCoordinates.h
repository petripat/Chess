#ifndef PETRIPAT_CCOORDINATES_H
#define PETRIPAT_CCOORDINATES_H

#include <string>
#include <vector>

/**
 * @brief Class CCoordinates represents coordinates on m_board .
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

class CCoordinates {
    int row; /** number of row on m_board*/
    int column; /** number of column on m_board*/
public:
    /**
     * Constuctor that sets up coordinates.
     * @param rowY = row on m_board
     * @param columnX = column on m_board
     */
    CCoordinates(int rowY = 0, int columnX = 0);
    /**
     * Copy constructor
     * @param cor - coordinates to be copied
     */
    CCoordinates(const CCoordinates & cor);
    /**
     * Method that saves position from string
     * @param position - string with position
     * @return true - position in string is ok
     *          false - wrong format of position in string
     */
    bool savePosition(std::string &position);
    /**
     * Getter for column
     * @return  column
     */
    int getColumn() const;
    /**
     * Getter for row
     * @return row
     */
    int getRow() const;
    /**
     * Operator for +=
     * @param rhs - coordinates to add to current ones
     * @return this instance
     */
    CCoordinates& operator+=(const CCoordinates & rhs);
    /**
     * Operator for +
     * @param rhs - coordinates to add with current ones
     * @return return added this and rhs coordinates
     */
    CCoordinates operator+(const CCoordinates & rhs) const ;
    /**
     * Opeator == to compare equality
     * @param rhs - coordinates to compare with
     * @return - true - coordinates are equal
     *          false - coordinates are different
     */
    bool operator==(const CCoordinates & rhs) const;
    /**
     * Copy operator
     * @param rhs - coordinates to copy
     * @return this instance with copied coordinates
     */
    CCoordinates & operator=(const CCoordinates & rhs);
    /**
     * Compares if this coordinates are less than rhs coordinates
     * @param rhs - coordinates to compare with
     * @return true - yes, these are less
     *          false - coordinates are more or equal
     */
    bool operator<(const CCoordinates & rhs) const;

};

#endif //PETRIPAT_CCOORDINATES_H

