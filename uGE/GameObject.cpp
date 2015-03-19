#include "GameObject.hpp"

#include "Animation.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Controller.hpp"
#include "Material.hpp"
#include "Renderer.hpp"


namespace uGE {

	GameObject::GameObject( std::string name )
	: transform( _transform ), _name( name ), _colliders( 0 ), _body( 0 ), _controller( 0 )
	{
	    //_direction = glm::vec3(1f, 0f, 0f);
	    _transform = glm::mat4( 1 );
	}

	GameObject::~GameObject()
	{
		delete _body;
		delete _controller;

		for(unsigned int i = 0; i < _colliders.size() ; i++ ){
            delete _colliders[i];
        }
	}

	void GameObject::addChild( GameObject * child ) //Use this to build your scattered pieces into your GameObject (eyes, feet, etc.)
	{
		children.push_back( child );
	}

	GameObject * GameObject::getChildWithName(std::string childName)
	{
	    for( GameObject* child : children ) {
            if( child->getName() == childName ) {
                return child;
            }
	    }
	    return NULL;
	}

	std::string GameObject::getName()
	{
		return _name;
	}


	void GameObject::render( Shader * shader, glm::mat4 & parentTransform )
	{
		glm::mat4 transform = parentTransform * _transform;
		//if ( _body ) _body->render( shader, transform );

		if( _body ) {
            if( _body->getMaterial()->getBlendMode() == Material::BlendMode::NORMAL ) {
                Renderer::firstPassRender[ _body ] = transform * _animTransform;
            } else {
                Renderer::secondPassRender[ _body ] = transform * _animTransform;
            }
		}

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->render( shader, transform );
		}
	}
	void GameObject::setBody( Body * body )
	{
		_body = body;
	}
    Body* GameObject::getBody()
	{
		return _body;
	}

	Material * GameObject::getMaterial()
	{
	    if( !_body ) { return NULL; }
	    return _body->getMaterial();
	}

	void GameObject::setCollider( Collider * collider )
	{
		_colliders.push_back( collider );
	}

	std::vector<Collider *> GameObject::getColliders()
	{
        return _colliders;
	}

	void GameObject::setController( Controller * controller )
	{
		_controller = controller;
	}

	Controller* GameObject::getController()
	{
	    return _controller;
	}

	void GameObject::setAnimTransform( glm::mat4 & animTransform )
	{
	    _animTransform = animTransform;
	}
    void GameObject::setRotation( glm::vec3 aRotation )
    {
        glm::vec3 xAxis = glm::cross( glm::vec3( 0.f, 1.f, 0.f ), aRotation );
        transform[2] = glm::vec4( aRotation, 0.f );
        transform[0] = glm::vec4( glm::normalize( xAxis ), 0.f );
    }
	void GameObject::setPosition( glm::vec3 position )
	{
		_transform[3] = glm::vec4( position, 1.0f );
	}

    void GameObject::setDirection( glm::vec3 direction )
	{
		_direction = direction;
	}
    glm::vec3 GameObject::getDirection()
	{
		return _direction;
	}

	void GameObject::update()
	{
		if ( _controller ) _controller->update();

		if ( this->getName() == "Player" )
        {
            if ( this->getBody()->getAnimation() )
            {
                this->getBody()->getAnimation()->update();
            }
        }

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->update();
		}
	}

	glm::vec3 GameObject::getPosition()
	{
        glm::vec4 position = glm::vec4( _transform[3] );
        return glm::vec3( position );
	}

}
