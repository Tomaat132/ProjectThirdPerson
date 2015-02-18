#ifndef LEVELLOADER_H
#define LEVELLOADER_H

class LevelLoader
{
    public:
        LevelLoader();
        virtual ~LevelLoader();
        //add stuff here

        void getObjectsPosition();


    protected:
    private:

        void loadXML(const char * iFilename);
        void parseXML(const char * iFilename);

};

#endif // LEVELLOADER_H
