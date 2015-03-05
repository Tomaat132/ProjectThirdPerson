#include "Animation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Utils/glm.hpp"


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
            std::cout << "Done loading " << filename << "." << std::endl;
            return animation;
        } else {
			std::cout << "Error => Could not load " << filename << "." << std::endl;
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
	    //this->setIsPlaying("true");/*
	    //std::cout << _parent->getName() << std::endl;
	    //std::cout << "FPS = " << playFPS << "." << std::endl;
	    //std::cout << _animTrans.size() << ", " << _animRot.size() << std::endl;
	    //int i = 0;
	    //signed int j = _animTrans.size();
	    //std::cout << "j = " << j << "." << std::endl;
        //for(i = 0; i < j; ++i)
        //{
            //_parent->transform = glm::rotate(_parent->transform, _animRot[i][0], glm::vec3(_parent->transform[0]));
            //_parent->transform = glm::rotate(_parent->transform, _animRot[i][1], glm::vec3(_parent->transform[1]));
            //_parent->transform = glm::rotate(_parent->transform, _animRot[i][2], glm::vec3(_parent->transform[2]));
            //_parent->transform = glm::translate(_parent->transform, _animTrans[i]);
            //std::cout << "Loop Process: " << i << "." << std::endl;
            //if(_repeat && i >= j)
            //{
                //i = 0;
            //}
        //}
        //std::cout << "bool repeat = " << repeat << "." << std::endl;
        //std::cout << "int i afterwards: " << i << "." << std::endl;
        //std::cout << "int j afterwards: " << j << "." << std::endl;*/
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

	void Animation::update() //Update function
	{
        std::cout << "_repeat: " << _repeat << "." << std::endl;
        std::cout << "_isPlaying: " << _isPlaying << "." << std::endl;
        _animTransform = glm::mat4( 1.0 );
        unsigned int i = _animTrans.size();
        if(!_isPlaying)
        {
            /* <- A try to set transformation to default again...
            //Assigning rotations x,y,z from that specific frame to rotation part of animTransform matrix
            _animTransform = glm::rotate( _animTransform, _animRot[frame][0], glm::vec3( _animTransform[0] ) ); //_animRot.x assigned to _animTransform.x
            _animTransform = glm::rotate( _animTransform, _animRot[frame][1], glm::vec3( _animTransform[1] ) ); //_animRot.y assigned to _animTransform.y
            _animTransform = glm::rotate( _animTransform, _animRot[frame][2], glm::vec3( _animTransform[2] ) ); //_animRot.z assigned to _animTransform.z
            //Assigning translations to animTransform matrix
            _animTransform = glm::translate( _animTransform, _animTrans[frame] );
            _parent->setAnimTransform( _animTransform );*/
            return;
        } else {
            //Assigning rotations x,y,z from that specific frame to rotation part of animTransform matrix
            _animTransform = glm::rotate( _animTransform, _animRot[frame][0], glm::vec3( _animTransform[0] ) ); //_animRot.x assigned to _animTransform.x
            _animTransform = glm::rotate( _animTransform, _animRot[frame][1], glm::vec3( _animTransform[1] ) ); //_animRot.y assigned to _animTransform.y
            _animTransform = glm::rotate( _animTransform, _animRot[frame][2], glm::vec3( _animTransform[2] ) ); //_animRot.z assigned to _animTransform.z
            //Assigning translations to animTransform matrix
            _animTransform = glm::translate( _animTransform, _animTrans[frame] );
            _parent->setAnimTransform( _animTransform ); // Setting animTransform onto GameObject.transform
            frame++;
        }
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
