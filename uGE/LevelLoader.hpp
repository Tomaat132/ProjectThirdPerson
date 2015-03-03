#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "utils/tinyxml2.h"

namespace uGE {

    class LevelLoader
    {
        public:
            LevelLoader();
            virtual ~LevelLoader();
            //add stuff here

            void loadLevel(std::string iFilename);


        protected:
        private:

            void parseXML(const char * iFilename);
            void parseGroup( tinyxml2::XMLElement * group );

    };
}

#endif // LEVELLOADER_H
