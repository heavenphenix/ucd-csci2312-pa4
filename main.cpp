//
// by David Lam
// 4.17.16
// 'main.cpp'
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ErrorContext.h"
#include "GamingTests.h"

using std::cout;
using std::endl;

using namespace Testing;

int main()
{

    const int NumIters = 3;

    cout << endl << "Testing PA5!!" << endl << endl;

    cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
    cout << "       Tests intentionally invoke destructors after they complete," << endl;
    cout << "       so if you see a seg-fault after a passed test, it is" << endl;
    cout << "       probably a bug in your destructor." << endl;

    cout << endl;

    ErrorContext ec(cout);

    // test piece
    test_piece_smoketest(ec);
    test_piece_print(ec, NumIters);
    test_piece_aging(ec, NumIters);
    test_piece_energy(ec, NumIters);
    test_piece_turntaking(ec, NumIters);
    test_piece_interaction(ec, NumIters);

   // test surrounding
    test_surroundings_smoketest(ec);

   // test action
    test_action_smoketest(ec);

  // test game
    test_game_smoketest(ec);
    test_game_populate(ec, NumIters);
    test_game_getpiece(ec, NumIters);
    test_game_print(ec, NumIters);
    test_game_randomization(ec, NumIters);
    test_game_play(ec, NumIters);

    return 0;
}
