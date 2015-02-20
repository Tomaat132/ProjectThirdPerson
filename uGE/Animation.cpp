#include "Animation.hpp"
#include "Mesh.hpp"

namespace uGE {

	Animation::Animation()
	{
		//ctor
	}

	Animation::~Animation()
	{
		glDeleteBuffers( 2, _buffTotal );
	}

	GLuint Animation::getTransBuffer()
	{
	    return _buffTotal[0];
	}

	GLuint Animation::getRotBuffer()
	{
	    return _buffTotal[1];
	}

	//Loads the animation based on name
	Animation * Animation::LoadAnimation(std::string filename)
	{
	    //Create new instance of animation
	    Animation * animation = new Animation();
        //Open file
        std::ifstream animFile;
        animFile.open(filename.c_str(), std::ios::in);
        //Read file if it's open
        if(animFile.is_open())
        {
			std::vector<glm::vec3> translation;
			std::vector<glm::vec3> rotation;

			std::string line;
			//As long as program did not reach end of file, read line, store values (1, 2, 3) as translation, (4, 5, 6) as rotation.
			while( getline(animFile, line) )
            {
                glm::vec3 transl;
                glm::vec3 rotat;
                sscanf(line.c_str(), "%f %f %f %f %f %f", &transl.x, &transl.y, &transl.z, &rotat.x, &rotat.y, &rotat.z);
                translation.push_back(transl);
                rotation.push_back(rotat);
                //std::cout << "rotationArray: " << line << std::endl;
                animation->_animTrans.push_back(transl);
                animation->_animRot.push_back(rotat);
            }
            animFile.close();
            animation->createBuffers();
            std::cout << "Done loading " << filename << "." << std::endl;
            return animation;
        } else {
			std::cout << "Error => Could not load " << filename << "." << std::endl;
			delete animation;
        }
        //Function done
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

	GLuint Animation::createBuffers()
	{
	    glGenBuffers( 2, _buffTotal ); //generate 2 buffers, one for translation, one for rotation.

            glBindBuffer( GL_ARRAY_BUFFER, _buffTotal[0] ); //working on translation buffer
                glBufferData( GL_ARRAY_BUFFER, _animTrans.size() * 3 * sizeof( float ), _animTrans.data(), GL_STATIC_DRAW ); //data being drawn into memory

            glBindBuffer( GL_ARRAY_BUFFER, _buffTotal[1] ); //working on rotation buffer
                glBufferData( GL_ARRAY_BUFFER, _animRot.size() * 3 * sizeof( float ), _animRot.data(), GL_STATIC_DRAW ); //data being drawn into memory

        return _name; //return buffername
	}
}
