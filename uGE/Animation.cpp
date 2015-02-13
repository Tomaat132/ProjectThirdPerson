#include "Animation.hpp"

namespace uGE {

	Animation::Animation(GameObject * _parent)
	{
		//ctor
	}

	Animation::~Animation()
	{
		//dtor
	}

	//Loads the animation based on name
	Animation * Animation::LoadAnimation(std::string filename)
	{
        //should find name of ascii file (best if I can link the ascii to the mesh's name)
        //open file
        std::ifstream movFile;
        movFile.open(filename, std::ios::in);
        if(!movFile)
        {
            std::cerr << "READING FAILED!!!" << std::endl;
        } else {
        //read first three numbers as translation
            float tx, ty, tz, rx, ry, rz;
            movFile >> tx >> ty >> tz >> rx >> ry >> rz;
            std::cout << "translation: " << tx << ty << tz << std::endl;
            //read second three numbers as rotation
        }
        //arrays are ready now.
        return 0;
	}

	//Plays the animation based on name
	void Animation::PlayAnimation()
	{
        //get name (from loadAnimation)
        //get data (from loadAnimation variable data);
        //animation actually is an array of which the engine should scroll down to and apply the current numbers to designated mesh
        //Get mesh name, link mesh to animation
        //Apply data to Mesh
	}
}
