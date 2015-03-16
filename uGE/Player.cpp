#include "Player.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "Colliders/BoxCollider.hpp"
#include "Utils/glm.hpp"
#include "Time.hpp"

#include <iostream>
#include <map>

namespace uGE
{

    Player::Player()
    :GameObject( "Player" ), _score( 0 ), _shootable( 5 )
    {
        idle.push_back( AssetManager::loadMesh( "Assets/Models/suzanna.obj" ) );
        //walk.push_back( AssetManager::loadMesh( "Assets/Models/teapot.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/Character_animation.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/fthyhhf.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/hero_anim.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Animations/player.obj" ) );
        activeAction = "IDLE";
        currentAnim = idle;
    }

    Player::~Player()
    {
        //dtor
    }

    void Player::addScore( int value){
        _score += value;
    }
    int Player::getScore(){
        return _score;
    }
    int Player::getHealth(){
        return health;
    }
    int Player::getShootable(){
        return _shootable;
    }
    void Player::changeShootable(int value){
        _shootable += value;
    }
    void Player::changeHealth(int _health){
        health += _health;
        if( health > maxHealth ) {
            health = maxHealth;
        }
    }

    void Player::update(){
        GameObject::update();
        if (health <= 0){ std::cout<<"HOLY SHIT IT'S 0"<<std::endl; }
		addCrumbs();

        time += Time::step();
		while( time > .1f ) {
            time -= .1f;
            updateFrame();
        }
    }

    void Player::addCrumbs(){
		_timeCrumb +=Time::step();
        if(_timeCrumb > 1){//time to update the dropping of crumbs for zombie to follow
        dropCrumbs();//actual dropping of the crumbs
        _timeCrumb = 0;//reset, duh
        }
    }

    void Player::dropCrumbs(){//makes player drop a trail
		glm::vec3 crumb;
		crumb = getPosition();
		crumbs.push_back(crumb);
			for(unsigned int i = 0; i < crumbs.size(); i++){
				if(crumbs.size() > 4){
				crumbs.erase(crumbs.begin());
				}
			}
		}

	std::vector<glm::vec3> Player::getCrumbs()
	{
		return crumbs;
	}

    std::vector<glm::vec3> Player::getCrumbs()
	{
        return crumbs;
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
