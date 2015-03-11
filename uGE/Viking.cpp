#include "Viking.hpp"
#include "Game.hpp"
#include "WinSequence.hpp"
#include <iostream>

namespace uGE {

    int Viking::zombieCount = 20;

    Viking::Viking()
    {

    }

    Viking::~Viking()
    {
        //dtor
    }

    void Viking::startWinSeq()
    {
        std::cout << "You beat the game!" << std::endl;
        WinSequence * winSeq = new WinSequence();
    }

}
