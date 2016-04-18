//
// by David Lam
// 4.17.16
// 'AggressiveAgentStrategy.cpp'
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"
#include <random>

using namespace std;

namespace Gaming 
{

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) { __agentEnergy = agentEnergy;}

    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {
    
    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const 
    {
        vector<int> positions;
        default_random_engine gen;

        if (__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD) 
        {
            for (int a = 0; a < 9; ++a) 
            {
                if (s.array[a] == PieceType::SIMPLE || s.array[a] == PieceType::STRATEGIC)
                {
                    positions.push_back(a);
                }
            }
        }

        if (positions.size() == 0) 
        {
            for (int a = 0; a < 9; ++a)
            {
                if (s.array[a] == PieceType::ADVANTAGE)
                {
                    positions.push_back(a);
                }
            }
        }

        if (positions.size() == 0) 
        {
            for (int a = 0; a < 9; ++a) 
            {
                if (s.array[a] == PieceType::EMPTY)
                {
                    positions.push_back(a);
                }
            }
        }

        if (positions.size() == 0) 
        {
            for (int a = 0; a < 9; ++a)
            {
                if (s.array[a] == PieceType::FOOD)
                {
                    positions.push_back(a);
                }
            }
        }

        if (positions.size() > 0) 
        {

            int index = positions[gen() % positions.size()];
            if (positions.size() == 1) index = positions[0];
            ActionType action;
            switch (index) 
            {
                case 0: 
                    action = NorthWest; 
                    break;
                case 1: 
                    action = North; 
                    break;
                case 2: 
                    action = NorthEast; 
                    break;
                case 3: 
                    action = West; 
                    break;
                case 4: 
                    action = Stay; 
                    break;
                case 5: 
                    action = East; 
                    break;
                case 6: 
                    action = SouthWest; 
                    break;
                case 7: 
                    action = South; 
                    break;
                case 8: 
                    action = SouthEast; 
                    break;
                default: 
                    action = Stay;
            }
            return (action);
        }

        return ActionType::Stay;
    }

}
