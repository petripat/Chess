#ifndef PETRIPAT_ESPECIALMOVE_H
#define PETRIPAT_ESPECIALMOVE_H

#include "../AbstractPiece/ECPiece.h"


/**
 * Enum of special moves possible for pawn and king
 */
enum ESpecialMove {
    ENPASSANT,
    PROMOTION,
    CASTLING,
    NO_MOVE,
};
/**
 * @brief Struct SPieceMove represents move.
 *          Detailed description follows here.
            @author P. Petriľáková
            @date May 2021
 */

struct SPieceMove {
    EPiece m_piece; /** Variable used only when move is promotion or en passant, during promotion stores which
     * piece should pawn transform to*/
    CCoordinates m_from;
    CCoordinates m_to;
    int m_points; /** Points of move - if > 0 -> piece is being taken during move */
    ESpecialMove m_move; /** NO_MOVE unless move is special move */
    /**
     * Default constructor.
     */
    SPieceMove() : m_piece(NO_PIECE), m_from({0, 0}), m_to({0, 0}), m_points (0), m_move(NO_MOVE) {}
    /**
     * constructor
     * @param from
     * @param to
     * @param points - Points of move - if > 0 -> piece is being taken during move default 0
     * @param piece - Variable used only when move is promotion or en passant, during promotion stores which
     * piece should pawn transform to default NO_PIECE
     * @param move1 - NO_MOVE unless move is special move default NO_MOVE
     */
    SPieceMove( const CCoordinates & from, const CCoordinates & to,  int points = 0, EPiece piece = NO_PIECE, ESpecialMove move = NO_MOVE)
            : m_piece(piece), m_from(from), m_to(to), m_points(points), m_move(move) {}
    /**
     * Copy constructor
     * @param rhs - move to be copied from
     */
    SPieceMove(const SPieceMove & rhs) : m_piece(rhs.m_piece), m_from(rhs.m_from), m_to(rhs.m_to), m_points(rhs.m_points), m_move(rhs.m_move) {}
    /**
        * Compares two moves based on points
        * @param rhs - right hand side for comparing
        * @return true - *this has lower value based on points
        *         false - rhs has lower value based on points
         */
    bool operator<(const SPieceMove & rhs) const{
        return m_points < rhs.m_points;
    }
    SPieceMove& operator=(const SPieceMove & rhs) = default;
};

#endif //PETRIPAT_ESPECIALMOVE_H