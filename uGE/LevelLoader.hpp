#ifndef LEVELLOADER_H
#define LEVELLOADER_H

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

    };
}

#endif // LEVELLOADER_H
