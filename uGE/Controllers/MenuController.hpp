#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "Viking.hpp"

namespace uGE {

    class MenuController : public Controller
    {
        public:
            MenuController( uGE::GameObject * parent );
            virtual ~MenuController();

            void update();
        private:
    };
}

#endif // MENUCONTROLLER_H
