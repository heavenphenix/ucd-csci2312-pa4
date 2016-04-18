//
// by David Lam
// 4.17.16
// 'advantage.cpp'
//

#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Agent.h"
#include "Advantage.h"
#include <iomanip>

using namespace std;

namespace Gaming {
   
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char  Advantage::ADVANTAGE_ID = 'D';
   
    // Constructor
    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource (g, p, capacity * ADVANTAGE_MULT_FACTOR) 
    { 
        
    }
    
    // Destructor
    Advantage::~Advantage() 
    {
    
    }
    
    // Print
    void Advantage::print(ostream &os) const 
    {
        os << ADVANTAGE_ID;
    }

    double Advantage::getCapacity() const { return __capacity; 
        
    }

    double Advantage::consume() 
    {
        __capacity = -1;
        finish();
        return __capacity;

    }
}
