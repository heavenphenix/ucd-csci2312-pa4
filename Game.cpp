//
// by David Lam
// 4.17.16
// 'Game.cpp'
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>

#include "Advantage.h"
#include "Food.h"
#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Simple.h"
#include "Strategic.h"

using namespace std;

namespace Gaming
{

    char mander = 'A';
    char meleon = 'X';
    char izard = 'B';
    
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    // Ctr
    Game::Game() {
        __numInitAgents = 0;
        __numInitResources = 0;
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;

        for (int a=0; a < (__width*__height); a++)
            __grid.push_back(nullptr);

        __round = 0;
        __status = NOT_STARTED;
        __verbose = false;
    }

    // Ctr:
    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height) 
    {
        if (width < MIN_HEIGHT || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        __numInitAgents = 0;
        __numInitResources = 0;

        for (int a=0; a < (__width * __height); a++)
            __grid.push_back(nullptr);

        if (!manual)
            populate();

        __round = 0;
        __status = NOT_STARTED;
        __verbose = false;

    }

    Game::Game(const Game &another) : Game()
    {
        __status = NOT_STARTED;
        __width = another.__width;
        __height = another.__height;
        __grid = another.__grid;
        __round = 0;
    }

    // Dtr
    Game::~Game() 
    {
        
    }

    // Population of game
    void Game::populate() 
    {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numAdvantages = __numInitResources / 2;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents / 2;
        unsigned int numFoods = __numInitResources / 2;
        if (__numInitResources % 2 == 1)
            numFoods++;

        // from sample code
        default_random_engine gen;
        uniform_int_distribution<int> d(0, __width * __height);

        if (__numInitAgents % 2 == 1)
            numStrategic++;

        
        while (numStrategic > 0)
        {
            int a = d(gen);
            if (__grid[a] == nullptr)
            {
                Position posit(a / __width, a % __width);
                __grid[a] = new Strategic(*this, posis, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        
        while (numSimple > 0)
        {
            int a = d(gen);
            if (__grid[a] == nullptr)
            {
                Position pos(a / __width, a % __width);
                __grid[a] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        
        while (numAdvantages > 0)
        {
            int a = d(gen);
            if (__grid[a] == nullptr)
            {
                Position pos(a / __width, a % __width);
                __grid[a] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        // populate food:
        while (numFoods > 0)
        {
            int a = d(gen);
            if (__grid[a] == nullptr)
            {
                Position pos(a / __width, a % __width);
                __grid[a] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    unsigned int Game::getNumPieces() const { return getNumAgents() + getNumResources();
    }

    unsigned int Game::getNumAgents() const
    { 
        return getNumSimple() + getNumStrategic();
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numAgents++;
        }
        return numAgents;
    }

    unsigned int Game::getNumStrategic() const 
    {
        unsigned int numStrat = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Strategic *strategic = dynamic_cast<Strategic*>(*it);
            if (strategic) numStrat++;
        }
        return numStrat;

    }

    unsigned int Game::getNumResources() const 
    {

        unsigned int numResour = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResour++;
        }
        return numResour;
    }

    const Piece *  Game::getPiece(unsigned int x, unsigned int y) const 
    {
        unsigned int pos = (x *__width) + y;
        if (__grid[pos] == nullptr)
            throw PositionEmptyEx(x, y);
        return __grid[pos];
    }

    void Game::addSimple(const Position &position) 
    {
        addSimple(position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy)
    {
        Simple *sim = new Simple(*this,position,energy);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = sim;
    }

    void Game::addSimple(unsigned x, unsigned y) 
    {
        Position pos(x,y);
        this->addSimple(pos);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        Position pos(x,y);
        this->addSimple(pos,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {
        Strategic *strat = new Strategic(*this,position,STARTING_RESOURCE_CAPACITY,s);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = strat;
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) 
    {
        Position pos(x,y);
        this->addStrategic(pos,s);
    }

    void Game::addFood(const Position &position)
    {
        Food *foo = new Food(*this,position,STARTING_RESOURCE_CAPACITY);   

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = foo;
    }

    void Game::addFood(unsigned x, unsigned y)
    {
        Position pos(x,y);
        this->addFood(pos);
    }

    void Game::addAdvantage(const Position &position)
    {
        Advantage *advan = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

        if((position.x*__width + position.y)>__grid.size())
            throw OutOfBoundsEx(__width,__height,position.x,position.y);

        if((__grid[position.x*__width + position.y])!=nullptr)
            throw PositionNonemptyEx(position.x,position.y);

        __grid[position.x*__width + position.y] = advan;
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        Position pos(x,y);
        this->addAdvantage(pos);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const 
    {

        Surroundings *surro = new Surroundings;
        int counter = 0;
        for (int b = -1; b <= 1; b++)
        {
            for (int c = -1; c <= 1; c++) 
            {
                int position = (((pos.x + b) * __width) + (pos.y + c));
                if (pos.x+b < 0 || pos.x+b >= __height || pos.y+c <0 || pos.y+c >= __width) 
                {
                    surro->array[counter] = INACCESSIBLE;
                    counter++;
                }
                else if (counter == 4)
                {
                    surro->array[counter] = SELF;
                    counter++;
                }
                else if (__grid[position] ==  nullptr)
                {
                    surro->array[counter] = EMPTY;
                    counter++;
                }
                else 
                {
                    surro->array[counter] = __grid[position]->getType();
                    counter++;
                }

            }
        }

        surro->array[4] = SELF;
        return *surro;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) 
    {

        int xDiff = to.x - from.x;
        int yDiff = to.y - from.y;
        ActionType holder = STAY;

        if(xDiff == -1 && yDiff == -1)
            holder = NW;
        else if(xDiff == -1 && yDiff == 0)
            holder = N;
        else if(xDiff == -1 && yDiff == 1)
            holder = NE;
        else if(xDiff == 0 && yDiff == -1)
            holder = W;
        else if(xDiff == 0 && yDiff == 0)
            holder = STAY;
        else if(xDiff == 0 && yDiff == 1)
            holder = E;
        else if(xDiff == 1 && yDiff == -1)
            holder = SW;
        else if(xDiff == 1 && yDiff == 0)
            holder = S;
        else if(xDiff == 1 && yDiff == 1)
            holder = SE;


        return holder;

    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const 
    {
        Surroundings ss = getSurroundings(pos);
        ActionType direction [9] =  {NorthWest,North,NorthEast,West,Stay,East,SouthWest,South,SouthEast};
        int directionInt;
        bool duhTruth;
        for (int a = 0; a < 9; ++a) 
        {
            if(direction[a]== ac)
            {
                directionInt = a;
                break;
            }
        }
        duhTruth = ss.array[directionInt] != INACCESSIBLE;

        if (izard == 'B')
        {
            return duhTruth;
        }
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {
        Position newPos;

        if(ac == NorthWest)
            newPos = Position(pos.x-1,pos.y-1);
        else if(ac == Nort)
            newPos = Position(pos.x-1,pos.y);
        else if(ac == NorthEast)
            newPos = Position(pos.x-1,pos.y+1);
        else if(ac == West)
            newPos = Position(pos.x,pos.y-1);
        else if(ac == Stay)
            newPos = Position(pos.x,pos.y);
        else if(ac == East)
            newPos = Position(pos.x,pos.y+1);
        else if(ac == SouthWest)
            newPos = Position(pos.x+1,pos.y-1);
        else if(ac == South)
            newPos = Position(pos.x+1,pos.y);
        else if(ac == SouthEast)
            newPos = Position(pos.x+1,pos.y+1);

        return newPos;
    }

    void Game::round()
    {

        if(__round == 0 && __verbose)
        {
            __status = PLAYING;
            cout << endl << *this;
        }
        for (int a = 0; a < __grid.size(); ++a)
        {
            if(__grid[a]!= nullptr){
                if(__grid[a]->isViable()) 
                {
                    if (!__grid[a]->getTurned())
                    {
                        Agent * agent = dynamic_cast<Agent*>(__grid[a]);
                        if(agent)
                        {
                            __grid[a]->setTurned(true);
                            Position currentPos = __grid[a]->getPosition();
                            Surroundings s = getSurroundings(currentPos);
                            ActionType aT = __grid[a]->takeTurn(s);
                            if (aT != STAY)
                            {
                                Position newPos = move(currentPos, aT);
                                int newPosIndx = (newPos.x * __width + newPos.y);
                                (*__grid[a]) * (*__grid[newPosIndx]);
                                if(!__grid[a]->isViable())
                                {
                                    delete __grid[a];
                                    __grid[a]= nullptr;
                                }
                                else 
                                {
                                    __grid[a]->setPosition(newPos);
                                    if (__grid[newPosIndx] != nullptr) 
                                    {
                                        delete __grid[newPosIndx];
                                        __grid[newPosIndx] = __grid[a];
                                        __grid[a] = nullptr;
                                    }
                                    else
                                    {
                                        __grid[newPosIndx] = __grid[a];
                                        __grid[a] = nullptr;
                                    }
                                }
                                if(!__grid[newPosIndx]->isViable())
                                {
                                    delete __grid[newPosIndx];
                                    __grid[newPosIndx]= nullptr;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int b = 0; b < __grid.size(); ++b) 
        {
            if(__grid[b] != nullptr)
            {
                if (!__grid[b]->isViable()) 
                {
                    delete __grid[b];
                    __grid[b] = nullptr;
                }
                else
                {
                    __grid[b]->setTurned(false);
                    __grid[b]->age();
                }
            }
        }
        if(getNumPieces()< 2 || getNumResources() < 1)
            __status = OVER;
        ++__round;

        if(__verbose)
            cout << endl << *this;

    }

    void Game::play(bool verbose) 
    {
        if (mander == 'A')
        {
            __status = PLAYING;
            __verbose = verbose;
            cout << *this;
            while (__status != OVER) 
            {
                round();
                if (verbose)
                    cout << *this;
            }
            if (!verbose)
                cout << *this;
        }
    }

    ostream &operator<<(ostream &os, const Game &game)
    {
        int counter = 0;

        os << "Round " << game.getRound() << endl;

        for (int a=0; a < game.__height; a++)
        {
            for (int c=0; c < game.__width; c++)
            {
                if (game.__grid[counter] == nullptr)
                {
                    os << "[" << "     " << "]";
                }
                else
                {
                    os << "[" << *game.__grid[counter] << " ]";
                }
                counter++;
            }
            os << endl;
        }

        if(game.__status == Game::PLAYING)
            os << "Status: Playing...";
        else if(game.__status == Game::NOT_STARTED)
            os << "Status: Not Started...";
        else
            os << "Status: Over!";
        return os;
    }

}

