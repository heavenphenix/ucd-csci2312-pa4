//
// by David Lam
// 4.17.16
// 'Resource.cpp'
//

#include "Agent.h"
#include "Simple.h"
#include <iomanip>

using namespace std;

namespace Gaming 
{

    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) 
    { 
        
    }

    Simple::~Simple()
    {
        
    }

    void Simple::print(ostream &os) const 
    {
        os << SIMPLE_ID << left << __id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const 
    {

        ActionType action;
        vector<int> pos;

        random_device rd;
        mt19937 gen(rd());

        for (int a = 0; a < s.array.size(); a++) 
        {
            if (s.array[a] == ADVANTAGE || s.array[a] == FOOD)
            {
                pos.push_back(a);
            }
        }

        if (pos.size() == 0) 
        {
            for (int a = 0; a < s.array.size(); a++)
            {
                if (s.array[a] == EMPTY) 
                {
                    pos.push_back(a);
                }
            }
        }

        if (pos.size() > 0)
        {
            uniform_int_distribution<> distribution(0, (int) (pos.size() - 1));
            int a = distribution(gen);


            if (pos.size() == 1)
            {
                a = pos[0];
            }

            switch (a) 
            {
                case 1 :
                    action = North;
                    break;
                case 2 :
                    action = NorthEast;
                    break;
                case 5 :
                    action = East;
                    break;
                case 8 :
                    action = SouthEast;
                    break;
                case 7 :
                    action = South;
                    break;
                case 6 :
                    action = SouthWest;
                    break;
                case 3 :
                    action = West;
                    break;
                case 0 :
                    action = NorthWest;
                    break;
                case 4 :
                    action = Stay;
                    break;
                default :
                    action = Stay;
            }
            return action;

        }

        return Stay;
    }
}
