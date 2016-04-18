//
// by David Lam
// 4.17.16
// 'Food.cpp'
//

#include <iomanip>
#include <sstream>

#include "Agent.h"
#include "Food.h"
#include "Game.h"
#include "Piece.h"
#include "Resource.h"

using namespace std;

namespace Gaming
{

    const char Food::FOOD_ID = 'F';
    // Letter F is FOOD

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) { __capacity = capacity;}

    // dtr
    Food::~Food()
    {
    
    }

    void Food::print(ostream &os) const 
    {
        os << FOOD_ID << left << __id;
    }
}
