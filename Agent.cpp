//
// by David Lam
// 4.17.16
// 'agent.cpp'
//

#include "Advantage.h"
#include "Agent.h"

namespace Gaming 
{

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    // ctr
    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy)
    {
        
    }

    // dtr
    Agent::~Agent() 
    {
       
    }

    void Agent::age() 
    {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other)
    {
        Piece *p = &other;
        Resource *cost = dynamic_cast<Resource*>(p);
        if (cost) 
        {
            interact(cost);
        }
        Agent *agent = dynamic_cast<Agent*>(p);
        if (agent) {
            interact(agent);
        }
        if (!isFinished()) 
        {

            Position NewPosit;
            NewPosit = other.getPosition();
            Position OldPosit;
            OldPosit = getPosition();
            setPosition(NewPosit);
            other.setPosition(OldPosit);
        }
        return *this;
    }

    Piece &Agent::interact(Agent *other) 
    {
        if (__energy == other->__energy)
        {
            finish();
            other->finish();
        }
        else {
            if (__energy > other->__energy) 
            {
                __energy -= other->__energy;
                other->finish();
            }
            else {
                other->__energy -= __energy;
                finish();
            }
        }
        return *this;
    }

    Piece &Agent::interact(Resource *other)
    {
        __energy += other->consume();
        return *this;
    }

}

