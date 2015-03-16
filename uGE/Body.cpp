#include "Body.hpp"
#include "Mesh.hpp"
#include "Animation.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include "Material.hpp"
#include "SceneManager.hpp"


namespace uGE {

	Body::Body( GameObject * parent )
	:	_parent( parent ), _mesh( 0 ), _animation( 0 ), _texture( 0 ), _shader( 0 ), time( 0 )
	{
        _material = new Material();
	}

	Body::~Body()
	{
		//dtor
	}

	std::string Body::getParentName()
	{
	    return _parent->getName();
	}

	void Body::render( Shader * shader, glm::mat4 & transform )
	{
	    if( !SceneManager::paused ) {
            time += Time::step();
	    }
	    //if(!_shader) return;
		if ( shader && _mesh ) {
            _material->applyBlendMode();
            shader->setUniform( shader->time, time );
            shader->setUniform( shader->alpha, _material->getAlpha() );
            shader->setUniform( shader->outlineColor, _outlineColor );
			shader->setUniform( shader->model, transform );
			shader->setTexture( shader->colorMap, _texture );
			shader->setAttrib( _mesh->getIndexBuffer() );
			shader->setAttrib( shader->vertex, 3, _mesh->getVertexBuffer() );
			shader->setAttrib( shader->normal, 3, _mesh->getNormalBuffer() );
			shader->setAttrib( shader->uv, 	   2, _mesh->getUvBuffer() );
			shader->render( _mesh->size() );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glDisableVertexAttribArray( shader->vertex );
			glDisableVertexAttribArray( shader->normal );
			glDisableVertexAttribArray( shader->uv );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}
	}

	void Body::setMesh( Mesh * mesh )
	{
        _mesh = mesh;
	}

	Mesh * Body::getMesh(){

	return _mesh;
	}

	void Body::setOutlineColor( glm::vec4 color )
	{
		_outlineColor = color;
	}
	void Body::setAnimation( Animation * animation ) //Set Animation
	{
	    _animation = animation;
	    _animation->setMesh(_mesh);
	}
	Animation * Body::getAnimation() //Get Animation
	{
	    if(_animation == NULL)
        {
            return 0;
        } else {
            return _animation;
        }
	}
	void Body::setTexture( Texture * texture )
	{
		_texture = texture;
	}
	void Body::setShader( Shader * shader)
	{
		_shader = shader;
	}

	void Body::setMaterial( Material * material )
	{
	    _material = material;
	}

	Shader* Body::getShader()
	{
		return _shader;
	}

	Material * Body::getMaterial()
	{
	    return _material;
	}
}
