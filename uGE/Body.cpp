#include "Body.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"


namespace uGE {

	Body::Body( GameObject * parent )
	:	_parent( parent ), _mesh( 0 ), _texture( 0 )
	{
//		parent->set( this );
	}

	Body::~Body()
	{
		//dtor
	}

	void Body::render( Shader * shader, glm::mat4 & transform )
	{
		if ( shader && _mesh ) {
			shader->setUniform( shader->model, transform );
			shader->setTexture( shader->colorMap, _texture );
			shader->setAttrib( _mesh->getIndexBuffer() );
			shader->setAttrib( shader->vertex, 3, _mesh->getVertexBuffer() );
			shader->setAttrib( shader->normal, 3, _mesh->getNormalBuffer() );
			shader->setAttrib( shader->uv, 		 2, _mesh->getUvBuffer() );
			shader->render( _mesh->size() );
		}
	}

	void Body::setMesh( Mesh * mesh )
	{
		_mesh = mesh;
	}
	void Body::setTexture( Texture * texture )
	{
		_texture = texture;
	}
}
