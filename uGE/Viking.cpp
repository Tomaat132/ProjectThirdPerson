#include "Viking.hpp"

namespace uGE {

    Viking::Viking()
    : alive(20)
    {
        //ctor
    }

    Viking::~Viking()
    {
        //dtor
    }

    void vikingBuried()
    {
        alive--;
    }
}
