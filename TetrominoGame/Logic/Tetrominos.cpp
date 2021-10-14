//
//  Tetrominos.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "Tetrominos.hpp"

namespace Tetrominos
{
    // Tetrominos definition
    // 7 different types, 4 rotations for each, and 5x5 grid to store everything
    const TetrominosMatrix mTetrominos =
    {
    // Square
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, -1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, -1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, -1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, -1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    }
    },

    // I
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 2, -1, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 2, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 2, -1, 2, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 2, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0}
    }
    }
    ,
    // L
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 3, -1, 3, 0},
    {0, 3, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 3, 3, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 3, 0},
    {0, 3, -1, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
    },
    // L mirrored
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 4, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 4, 4, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 4, 0, 0, 0},
    {0, 4, -1, 4, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 4, 4, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 4, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 4, -1, 4, 0},
    {0, 0, 0, 4, 0},
    {0, 0, 0, 0, 0}
    }
    },
    // N
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 5, 0},
    {0, 0, -1, 5, 0},
    {0, 0, 5, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 5, -1, 0, 0},
    {0, 0, 5, 5, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 5, 0, 0},
    {0, 5, -1, 0, 0},
    {0, 5, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },

    {
    {0, 0, 0, 0, 0},
    {0, 5, 5, 0, 0},
    {0, 0, -1, 5, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
    },
    // N mirrored
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 7, 0, 0},
    {0, 0, -1, 7, 0},
    {0, 0, 0, 7, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, -1, 7, 0},
    {0, 7, 7, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 7, 0, 0, 0},
    {0, 7, -1, 0, 0},
    {0, 0, 7, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 7, 7, 0},
    {0, 7, -1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
    },
    // T
    {
    {
    {0, 0, 0, 0, 0},
    {0, 0, 6, 0, 0},
    {0, 0, -1, 6, 0},
    {0, 0, 6, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 6, -1, 6, 0},
    {0, 0, 6, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 6, 0, 0},
    {0, 6, -1, 0, 0},
    {0, 0, 6, 0, 0},
    {0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0},
    {0, 0, 6, 0, 0},
    {0, 6, -1, 6, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
    }
    };

    // Colors for tetrominos, accessed by the numbers in each pieces matrix
const std::vector<SDL_Color> tetrominoColors =
    {
        { 0x00, 0x00, 0x00, 0x00 }, // Transparent
        { 0xFF, 0x00, 0x00, 0xFF }, // Red
        { 0x00, 0xFF, 0x00, 0xFF }, // Green
        { 0x00, 0x00, 0xFF, 0xFF }, // Blue
        { 0xFF, 0xFF, 0x00, 0xFF }, // Orangey
        { 0x00, 0xFF, 0xFF, 0xFF }, // Purply
        { 0xFF, 0x00, 0xFF, 0xFF },
        { 0xFF, 0xAA, 0xFF, 0xFF }
    };

    // Pieces need to start in a reasonable position with regards to top of board
    // 7 types, 4 rotations, and 2 to store the starting position for each rotation
    const InitialPositionsMatrix mTetrominosInitialPosition =
    {
    /* Square */
    {
    {-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -3}
    },
    /* I */
    {
    {-2, -2},
    {-2, -3},
    {-2, -2},
    {-2, -3}
    },
    /* L */
    {
    {-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
    },
    /* L mirrored */
    {
    {-2, -3},
    {-2, -2},
    {-2, -3},
    {-2, -3}
    },
    /* N */
    {
    {-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
    },
    /* N mirrored */
    {
    {-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
    },
    /* T */
    {
    {-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
    },
    };

    const int GetBlockType(Tetromino tetromino, Rotation rotation, int x, int y)
    {
        return mTetrominos[tetromino][rotation][x][y];
    }

    const SDL_Color GetTetrominoColor(Tetromino tetromino)
    {
        return tetrominoColors[tetromino + 1];
    }

    const int GetInitialPositionX(Tetromino tetromino, Rotation rotation)
    {
        return mTetrominosInitialPosition[tetromino][rotation][0];
    }

    const int GetInitialPositionY(Tetromino tetromino, Rotation rotation)
    {
        return mTetrominosInitialPosition[tetromino][rotation][1];
    }
};
