//
// by David Lam
// 4.17.16
// 'DefaultAgentStrategy.cpp'
//

#include <random>

#include "DefaultAgentStrategy.h"
#include "Game.h"

using namespace std;

namespace Gaming 
{

    DefaultAgentStrategy::DefaultAgentStrategy() 
    { 
        
    }

    DefaultAgentStrategy::~DefaultAgentStrategy() 
    {
        
    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const 
    {
        ActionType action;
        vector<int> posit;
        default_random_engine gen;

        for (int a = 0; a < s.array.size(); a++)
        {
            if (s.array[a] == ADVANTAGE)
            {
                pos.push_back(a);
            }
        }

        if (pos.size() == 0) 
        {
            for (int a = 0; a < s.array.size(); a++)
            {
                if (s.array[a] == FOOD)
                {
                    pos.push_back(a);
                }
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

        if (pos.size() == 0) 
        {
            for (int a = 0; a < s.array.size(); a++)
            {
                if (s.array[a] == SIMPLE) 
                {
                    pos.push_back(a);
                }
            }
        }

        if (pos.size() > 0) 
        {
            uniform_int_distribution<> dis(0, (int) (pos.size()-1));
            int index = dis(gen);


            if (pos.size() == 1) 
            {
                index = pos[0];
            }

            switch (index) 
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
