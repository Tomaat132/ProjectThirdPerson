#include <iostream>
#include <string>
#include <vector>

#include "Colliders/SphereCollider.hpp"
#include "Colliders/AABBcollision.hpp"
#include "Colliders/BoxCollider.hpp"

#include "utils/glm.hpp"
#include "utils/tinyxml2.h"
#include "AssetManager.hpp"
#include "Body.hpp"
#include "GameObject.hpp"
#include "LevelLoader.hpp"
#include "Material.hpp"
#include "SceneManager.hpp"
#include "Shader.hpp"
#include "Player.hpp"
#include "Logger.h"

using namespace tinyxml2;

namespace uGE
{
    LevelLoader::LevelLoader() {
    }

    LevelLoader::~LevelLoader() {
    }

    void LevelLoader::parseGroup( XMLElement * group )
    {
        XMLElement * object = group->FirstChildElement( "node" );

        while( object ) {
            //Set and format the object name
            std::string objName = std::string( object->Attribute( "name" ) );
            while( isdigit( objName.at( objName.size() - 1 ) ) ) {
                objName.pop_back();
            }


            if( objName == "group" ) {
                parseGroup( object );
                object = object->NextSiblingElement( "node" );
                continue;
            }

            //Decompose the matrix into the 16 separate values
            XMLElement * objMatrix = object->FirstChildElement( "matrix" );
            const char * matrixString = objMatrix->GetText();

            std::string  word;
            std::vector< std::string > words;
            for ( unsigned int i = 0; i < std::strlen(matrixString); ++i ) {
                if(matrixString[i] == ' ') {
                    words.push_back(word);
                    word.clear();
                }
                else {
                     word += matrixString[i];
                }
            }
            words.push_back(word);

            //Push the values in an empty matrix to add to the object later
            glm::mat4 matrix;
            for (unsigned int i = 0; i < words.size(); i++) {
                float value = std::atof( words[i].c_str() );
                matrix[i%4][i/4] = value;
            }

            //Compose the GameObject
            if( objName == "watervv" || objName == "pasted__group" ) {
                /*GameObject * obj = new GameObject( objName );
                obj->transform = matrix;

                Body * body = new Body( obj );
                body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
                body->setShader( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/water.fs" ) );
                body->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );
                body->getMaterial()->setAlpha( 1.75f );
                obj->setBody( body );

				uGE::SceneManager::add( obj );*/
                object = object->NextSiblingElement( "node" );
                continue;
            }

            if( objName == "groundff" || objName == "bridge_msize" || objName == "bridge_vsize" || objName == "Skull_m" || objName == "grass") {
                //std::cout<< objName << std::endl;
                GameObject * obj = new GameObject( objName );
                obj->transform = matrix;

                Body * body = new Body( obj );
                body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
                if(objName == "grass") body->getMaterial()->setBlendMode( uGE::Material::BlendMode::ALPHA );

                obj->setBody( body );

                uGE::SceneManager::add( obj );
                object = object->NextSiblingElement( "node" );
                continue;
            }

            if( objName == "position_of_wisp" ){
                GameObject* obj = new GameObject( "" );
                obj->transform = matrix;

                uGE::SceneManager::addSpawnLoc(obj->getPosition());
                delete obj;

                object = object->NextSiblingElement( "node" );
                continue;
            }

            if( objName == "position_of_player" ) {
                SceneManager::_player->setPosition( glm::vec3( matrix[3] ) );
                object = object->NextSiblingElement( "node" );
                continue;
            }

            if( objName == "pozition_of_zombie" )
            {
                GameObject* obj = new GameObject( "" );
                obj->transform = matrix;

                uGE::SceneManager::addZombieSpawnLoc(obj->getPosition());
                delete obj;

                object = object->NextSiblingElement( "node" );
                continue;
            }

            if( objName.compare( "group" ) != 0 ) {
                GameObject * obj = new GameObject( objName );
                obj->transform = matrix;
                Body * body = new Body( obj );

                if( objName != "position_of_wisp" && objName != "pozition_of_zombie" ){
                    if(objName != "Water_box"){
                        body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                        body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
                    }
                    obj->setBody( body );
                }
                if( body->getMesh() ) {
                    if( objName == "Cone_tree" ) {
                        obj->setCollider( new SphereCollider( obj, 2.5f ) );
                    }
                    else if( objName == "Tree_dead" ) {
                        obj->setCollider( new SphereCollider( obj, 1.75f ) );
                    }
                    else if( objName != "bridge_msize" || objName != "bridge_vsize" ) {
						obj->setCollider( new BoxCollider( obj ) );
					}
                }
                /*if( objName == "Cone_tree"){
                    body->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );
                    body->getMaterial()->setAlpha( 1.75f );
                }*/

                uGE::SceneManager::add( obj );
            }

            //Next object
            object = object->NextSiblingElement( "node" );
        }
    }

    void LevelLoader::parseXML(const char* iFilename)
    {
        XMLDocument doc;
        Logger::print( Logger::INFO, "Loading level " + to_s(iFilename) + ", result: " + to_s( doc.LoadFile(iFilename) ) );

        XMLElement * object = doc.RootElement()->FirstChildElement( "library_visual_scenes" )->FirstChildElement();
        parseGroup( object );
    }

    void LevelLoader::loadLevel(std::string iFilename)
    {
        parseXML( ( "Assets/Level/" + iFilename + ".dae" ).c_str() );
    }
}
