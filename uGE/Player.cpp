#include "Player.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "Colliders/BoxCollider.hpp"
#include <iostream>
#include <map>
#include "Time.hpp"

namespace uGE{

    int health = 100;
    int maxHealth = 150;

    Player::Player()
    :GameObject( "Player" )
    {//ctor
        idle.push_back( AssetManager::loadMesh( "Assets/Models/suzanna.obj" ) );
        //walk.push_back( AssetManager::loadMesh( "Assets/Models/teapot.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/Character_animation.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/fthyhhf.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/hero_anim.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/player.obj" ) );
        activeAction = "IDLE";
        currentAnim = idle;
        std::cout << "All Player Meshes loaded and stored. Player Constructor closed." << std::endl;
    }


    Player::~Player()
    {
        //dtor
    }
//var space

//end of var space


    int Player::getHealth(){
        return health;
    }

    void Player::changeHealth(int _health){
        health += _health;
        if( health > maxHealth ) {
            health = maxHealth;
        }
    }

    void Player::update(){
        GameObject::update();
        if (health <= 0){std::cout<<"HOLY SHIT IT'S 0"<<std::endl;}

        time += Time::step();
        while( time > .05f ) {
            time -= .05f;
            updateFrame();
        }
    }

    void Player::updateFrame()
    {
        ++frame;
        std::cout << "Frame: " << frame << std::endl;
        if(frame >= currentAnim.size()) frame = 0;
        std::cout << currentAnim[frame] << std::endl;
        this->getBody()->setMesh(currentAnim[frame]);
    }

    //Player::currentlyPlaying for switching between animations
    void Player::playNow( std::string action )
    {
        if( action == "IDLE" && action != activeAction )
        {
            activeAction = "IDLE";
            currentAnim = idle;
        }
        else if( action == "WALK" && action != activeAction )
        {
            activeAction = "WALK";
            currentAnim = walk;
        }
    }


    //add stuff below
}
