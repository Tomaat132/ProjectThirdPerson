#include <iostream>
#include <string>
#include <vector>

#include "utils/glm.hpp"
#include "utils/tinyxml2.h"

#include "LevelLoader.hpp"

using namespace tinyxml2;
using namespace std;


    LevelLoader::LevelLoader() {
    }
    LevelLoader::~LevelLoader() {
    }

    void LevelLoader::loadXML(const char* iFilename ){

        XMLDocument doc;
        //doc.LoadFile( iFilename );
        bool loadOK = doc.LoadFile(iFilename);

        if(!loadOK){ //!loadOK because doc is seen as NULL which will TRIGGER the ELSE at any rate. (*this wile it actually LOADS*)

            printf(iFilename);

        }
        else{

             printf("Failure to load \"%s\"\n", iFilename);

        }

    }

    void LevelLoader::parseXML(const char* iFilename){

        //store the flaots in an std::<vector>
        //before storing it into the vector seperate the values within the string
        //use a for loop to go through all data
        XMLDocument doc;
        //doc.LoadFile(iFilename);
        std::cout << "Load: " << doc.LoadFile(iFilename) << std::endl; // "Zero" means no error
        //std::cout << doc.RootElement()->FirstChildElement("library_visual_scenes")->FirstChildElement()->FirstChildElement("node")->Attribute("name")<< std::endl;
        //std::cout << doc.RootElement()->FirstChildElement("library_visual_scenes")->FirstChildElement()->FirstChildElement()->FirstChildElement("matrix")->GetText()<< std::endl;

        XMLElement * object = doc.RootElement()->FirstChildElement("library_visual_scenes")->FirstChildElement()->FirstChildElement("node");
        XMLElement * objMatrix; //= doc.RootElement()->FirstChildElement("library_visual_scenes")->FirstChildElement()->FirstChildElement()->FirstChildElement("matrix");

        while( object ) {
            std::cout<<object->Attribute("name")<<std::endl;
            objMatrix = object->FirstChildElement("matrix");
            std::cout<<objMatrix->GetText()<<std::endl;//get matrix RIGHT after the 1st OBJECT
            //split stuff and store it here
            //working area
            std::string  word;
            std::vector< std::string > words;
            const char * matrixString = objMatrix->GetText();//this gets the actual float data
            for (unsigned int i = 0; i < std::strlen(matrixString) ; i++){ //a for loop to go through the matricString (all the float numbers as chars in the XML)
                if(matrixString[i] == ' '){ //seperate words with SPACE
                 words.push_back(word);//push the WORD into the WORDS array every time we encounter SPACE so we get a total complete single float
                 word.clear();//clear the WORD after we inserted it, otherwise it gets cluttered... AND TURNS INTO ASCII !
                }
                else {
                     word += matrixString[i];// it builds up the WORD character by character.
                }
            }
            words.push_back(word);//the last word needs to be pushed into words, otherwise we only have 3 things instead of 4
            //else {char *matrixString += matrixString[i];}
            //end of working area
            glm::mat4 matrix; //a matrix to store the floats in
            for (unsigned int i = 0; i < words.size(); i++){ //loop through all the collected words separated with space
                //convert stuff from words into matrix
                float convert = std::atof(words[i].c_str());//turn the words into actual floats
                matrix[i%4][i/4] = convert;//insert the float per location into the matrix
                //std::cout << convert << std::endl;
                //insert into matrix

            }
            std::cout<<matrix[3][2]<<std::endl;
            std::cout<<matrix<<std::endl;
            //then go to next object!
            object = object->NextSiblingElement("node");

            /*
            std::cout<< objMatrix->Value()<<std::endl;
            objMatrix = objMatrix->;
            std::cout<< objMatrix->Value()<<std::endl;
            */
        }
        //std::cout << doc.RootElement()->GetText() << std::endl;
        /*
        //std::cout << "Parse: " << doc.Parse("empty.xml") << std::endl;
        //std::cout << doc.Value() << std::endl;
        //XMLNode* titleElement = doc.NextSibling();
        //std::cout << "Test: " << titleElement->GetText() << std::endl;
        //const char* title = titleElement->Value();
        //XMLText * text = titleElement->ToText();
        //std::cout << text->Value() << std::endl;
        //XMLText* textNode = titleElement->FirstChild()->ToText();
        //const char* title = doc.FirstChildElement( "Hello" )->GetText();
        //XMLText* textNode = doc.FirstChildElement( "Hello" )->ToText();
        */
    }

    /*
    void dump_data(const char* pFilename)
    {
        XMLDocument doc(pFilename);
        bool loadOkay = doc.LoadFile(pFilename);
        doc.Parse();
        if (loadOkay)
        {
            printf(pFilename);
            // broken shit //dump_data( &doc ); // defined later in the tutorial
            //std::string s(120, pFilename); // s now has "A"
            //std::cout<< s << std::endl;
        }
        else
        {
            printf("Failed to load file \"%s\"\n", pFilename);
        }
    }
    */

    void LevelLoader::getObjectsPosition()
{

    //loadXML("empty.xml");
    parseXML("Assets/Level/test_export.dae");
    //dump_data("empty.xml");

}
