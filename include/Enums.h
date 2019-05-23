#ifndef CHESS_ENUMS_H
#define CHESS_ENUMS_H

enum Piece_type {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    ANY
};

enum game_state {
    NORMAL,
    WHITE_IN_CHECK,
    BLACK_IN_CHECK,
    WHITE_IN_STALEMATE,
    BLACK_IN_STALEMATE,
    WHITE_IN_CHECK_MATE,
    BLACK_IN_CHECK_MATE
};

enum color {
    BLACK,
    WHITE
};

enum special_args {
    NONE,
    PROM_N,
    PROM_B,
    PROM_R,
    PROM_Q,
    SHORT_CASTLE,
    LONG_CASTLE,
    STARTING_POINT_KNOWN    //for conflict situations
};

#endif //CHESS_ENUMS_H
