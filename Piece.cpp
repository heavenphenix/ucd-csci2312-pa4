//
// by David Lam
// 4.17.16
// 'Piece.cpp'

#include <iostream>

#include "Game.h"
#include "Piece.h"


namespace Gaming 
{

    unsigned int Piece::__idGen = 1000;
    Piece::Piece(const Game &g, const Position &p): __game(g) 
    {
        __position = p;
        __finished = false;
        __turned = false;
        __id = ++__idGen;
    }

    Piece::~Piece()
    {
        
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) 
    {
        piece.print(os);
        return os;
    }

}
