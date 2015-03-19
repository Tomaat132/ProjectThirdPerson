#include "Player.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "Colliders/BoxCollider.hpp"
#include "Utils/glm.hpp"
#include "Time.hpp"
#include "Logger.h"
#include "SceneManager.hpp"
#include "Hud.hpp"

#include <iostream>

namespace uGE
{
    Player::Player()
    :GameObject( "Player" ), _shootable( 5 ), _score( 0 ), _timeLeft( 300.f ), time( 0.f )
    {
        idle.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_Idle.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_1.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_2.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_3.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_4.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_5.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_6.obj" ) );
        walk.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_7.obj" ) );
        melee.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_melee/U_A_1.obj" ) );
        melee.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_melee/U_A_2.obj" ) );
        melee.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_melee/U_A_3.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_1.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_2.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_3.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_4.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_5.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_6.obj" ) );
        shoot.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_shoot/U_shoot_7.obj" ) );
        suck.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_suck/U_Suck_1.obj" ) );
        suck.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_suck/U_Suck_2.obj" ) );
        suck.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_suck/U_Suck_3.obj" ) );
        death.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_death/U_D_1.obj" ) );
        death.push_back( AssetManager::loadMesh( "Assets/Models/Undertaker_death/U_D_2.obj" ) );
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
    void Player::setHealth(int newHealth){
        health = newHealth;
    }
    void Player::resetTime(){
        _timeLeft = 300.f;
    }
    int Player::getTimeLeft(){
        int timeLeft = (int) _timeLeft;
        if( timeLeft < 0 ) {
            timeLeft = 0;
        }
        return timeLeft;
    }
    int Player::getShootable(){
        return _shootable;
    }
    void Player::changeShootable(int value){
        _shootable += value;
        if( _shootable > 9 ) {
            _shootable = 9;
        }
    }
    void Player::changeHealth(int _health){
        health += _health;
        if( health > maxHealth ) {
            health = maxHealth;
        }
    }
    bool reset = true;
    //PlayerController* Player::getPlayerController()
    //{
    //    return _controller;
   // }
    void Player::update()
	{
        GameObject::update();

		_timeLeft -= Time::step();
		if( reset ) {
			resetTime();
			reset = false;
		}
		if( _timeLeft <= 0.f ) {
            SceneManager::_hud->setEndGame( "Time's Up" );
        }

        if (health <= 0){
            //Make sure that PlayerController's keyboard controls get disabled!!!
            playNow("DEATH");
            SceneManager::_hud->setEndGame( "Game Over" );
        }
		//addCrumbs();

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

    void Player::updateFrame()
    {
        ++frame;
        //Logger::print( Logger::INFO, "Anim: " + activeAction + ", Frame: " + to_s(frame) );
        if(frame >= currentAnim.size()) frame = 0;
        this->getBody()->setMesh(currentAnim[frame]);
    }

    //Player::playNow for switching between animations
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
        else if( action == "MELEE" && action != activeAction )
        {
            activeAction = "MELEE";
            currentAnim = melee;
        }
        else if( action == "SHOOT" && action != activeAction )
        {
            activeAction = "SHOOT";
            currentAnim = shoot;
        }
        else if( action == "SUCK" && action != activeAction )
        {
            activeAction = "SUCK";
            currentAnim = suck;
        }
        else if( action == "DEATH" && action != activeAction )
        {
            activeAction = "DEATH";
            currentAnim = death;
        }
    }


    //add stuff below
}
