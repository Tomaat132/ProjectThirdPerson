#include <iostream>
#include <string>
#include <vector>

#include "utils/glm.hpp"
#include "utils/tinyxml2.h"
#include "AssetManager.hpp"
#include "Body.hpp"
#include "GameObject.hpp"
#include "LevelLoader.hpp"
#include "SceneManager.hpp"

using namespace tinyxml2;

namespace uGE
{
    LevelLoader::LevelLoader() {
    }

    LevelLoader::~LevelLoader() {
    }

    void LevelLoader::parseXML(const char* iFilename)
    {
        XMLDocument doc;
        std::cout << "Loading level " << iFilename << ", result: " << doc.LoadFile(iFilename) << std::endl;

        XMLElement * object = doc.RootElement()->FirstChildElement( "library_visual_scenes" )->FirstChildElement()->FirstChildElement( "node" );
        XMLElement * objMatrix;

        while( object ) {
            objMatrix = object->FirstChildElement( "matrix" );
            const char * matrixString = objMatrix->GetText();

            //Decompose the matrix into the 16 separate values
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

            //Set and format the object name
            std::string objName = std::string( object->Attribute( "name" ) );
            while( isdigit( objName.at( objName.size() - 1 ) ) ) {
                objName.pop_back();
            }

            //Compose the GameObject
            if( objName.compare( "group" ) != 0 ) {
                GameObject * obj = new GameObject( objName );
                obj->transform = matrix;

                Body * body = new Body( obj );
                body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
                obj->setBody( body );

                uGE::SceneManager::add( obj );
            }

            //Next object
            object = object->NextSiblingElement( "node" );
        }
    }

    void LevelLoader::loadLevel(std::string iFilename)
    {
        parseXML( ( "Assets/Level/" + iFilename + ".dae" ).c_str() );
    }
}
