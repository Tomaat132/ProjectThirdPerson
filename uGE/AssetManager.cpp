#include "AssetManager.hpp"

#include "Mesh.hpp"
#include "Texture.hpp"

namespace uGE {

	std::map< std::string, Mesh * > AssetManager::meshes;
//	std::map< std::string, Sound * > AssetManager::sounds; // needs fmod included
	std::map< std::string, Texture * > AssetManager::textures;

	AssetManager::AssetManager()
	{
		//ctor
	}

	AssetManager::~AssetManager()
	{
		//dtor
	}

	Mesh * AssetManager::loadMesh( std::string filename ) {
		auto found = meshes.find( filename );
		if ( found != meshes.end() ) {
            if(filename == "Assets/Models/Undertaker_walk/U_W_Idle.obj")std::cout<< filename << " = " <<found->second << std::endl;
			return found->second;
		} else {
			Mesh * mesh = Mesh::load( filename );
			meshes[ filename ] = mesh;
			return mesh;
		}
	}
/*
	Sound * AssetManager::loadSound( std::string filename ) {
		auto found = sounds.find( filename );
		if ( found != sounds.end() ) {
			return found->second;
		} else {
			Sound * sound = Sound::load( filename );
			sounds[ filename ] = sound;
			return sound;
		}
	}
*/
	Texture * AssetManager::loadTexture( std::string filename ) {
		auto found = textures.find( filename );
		if ( found != textures.end() ) {
			return found->second;
		} else {
			Texture * texture = Texture::load( filename );
			if( texture == NULL && filename != "Assets/Textures/bricks.jpg" ) {
                texture = loadTexture( "Assets/Textures/bricks.jpg" );
			}
			textures[ filename ] = texture;
			return texture;
		}
	}

}
