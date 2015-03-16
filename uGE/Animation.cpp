#include "Animation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Utils/glm.hpp"
#include "Time.hpp"
#include "Logger.h"

namespace uGE {

	Animation::Animation() //constructor
	:_mesh(0)
	{
		//cotr
	}

	Animation::~Animation() //destructor
	{
		glDeleteBuffers( 2, _buffTotal );
	}

	GLuint Animation::getTransBuffer() //To get acces to buffer
	{
	    return _buffTotal[0];
	}

	GLuint Animation::getRotBuffer() //To get access to buffer
	{
	    return _buffTotal[1];
	}

	void Animation::setMesh( Mesh * mesh ) //Sets the mesh again, especially for Animation class
	{
	    _mesh = mesh;
	}

	Animation * Animation::LoadAnimation(std::string filename) //Loads the animation based on name
	{
	    Animation * animation = new Animation(); //Create new instance of animation

        std::ifstream animFile; //Variable for this scope
        animFile.open(filename.c_str(), std::ios::in); //Open file

        if(animFile.is_open()) //Read file if it's open
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
                animation->_animTrans.push_back(transl);
                animation->_animRot.push_back(rotat);
            }
            animFile.close();
            animation->createBuffers();
            Logger::print( Logger::INFO, "Done loading " + filename + "." );
            return animation;
        } else {
            Logger::print( Logger::ERROR, "Could not load " + filename + "!" );
			delete animation;
        }
        return 0;
	}

	void Animation::PlayAnimation(GameObject * parent, std::string repeat) //Plays the animation on custom designated fps with repeat option
	{
	    //Variables: speed of playing, loopable, activation
	    _parent = parent;
	    if(repeat == "false")
        {
            _repeat = false;
            _isPlaying = true;
        }
	    else if(repeat == "true")
        {
            _repeat = true;
            _isPlaying = true;
        }

	    if(frame >= _animTrans.size()) frame = 0;
	}

	void Animation::StopAnimation() //Stops animation and resets frame to 0;
	{
	    //_isPlaying = false;
	    frame = 0;
	}

	void Animation::setIsPlaying(std::string isPlaying)
	{
        if(isPlaying == "false") _isPlaying = false;
        else if(isPlaying == "true") _isPlaying = true;
	}

    void Animation::update()
    {
        time += Time::step();
        while( time > .05f ) {
            time -= .05f;
            updateFrame();
        }
    }

	void Animation::updateFrame() //Update function
	{
	    if( !_parent || !_isPlaying ) {
            return;
	    }

        _animTransform = glm::mat4( 1.0 );
        unsigned int i = _animTrans.size();

        //Assigning rotations x,y,z from that specific frame to rotation part of animTransform matrix
        _animTransform = glm::rotate( _animTransform, _animRot[frame][0], glm::vec3( _animTransform[0] ) ); //_animRot.x assigned to _animTransform.x
        _animTransform = glm::rotate( _animTransform, _animRot[frame][1], glm::vec3( _animTransform[1] ) ); //_animRot.y assigned to _animTransform.y
        _animTransform = glm::rotate( _animTransform, _animRot[frame][2], glm::vec3( _animTransform[2] ) ); //_animRot.z assigned to _animTransform.z
        //Assigning translations to animTransform matrix
        _animTransform = glm::translate( _animTransform, _animTrans[frame] );
        _parent->setAnimTransform( _animTransform ); // Setting animTransform onto GameObject.transform
        frame++;

        if(frame >= i && _repeat != false)
        {
            frame = 0;
        }
        else if(_repeat != true)
        {
            _isPlaying = false;
        }
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
