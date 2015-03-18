#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Animation.hpp"
#include "AssetManager.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Controller.hpp"
#include "ZombieController.hpp"
#include "Material.hpp"
#include "Renderer.hpp"
#include "Time.hpp"
#include "Utils/glm.hpp"
#include "Logger.h"


namespace uGE {

	Zombie::Zombie( std::string name )
	: GameObject( name )
	{
	    idle.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Zombie_idle.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_1.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_2.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_3.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_4.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_5.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_6.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_7.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_8.obj" ) );
	    walk.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_9.obj" ) );
	    attack.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_attack/Z_A_1.obj" ) );
	    attack.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_attack/Z_A_2.obj" ) );
        death.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_death/Z_D_1.obj" ) );
        death.push_back( AssetManager::loadMesh( "Assets/Models/Zombie_death/Z_D_2.obj" ) );
        activeAction = "IDLE";
        currentAnim = idle;
        _viking = false;
	    //_direction = glm::vec3(1f, 0f, 0f);
	}

	Zombie::~Zombie()
	{
		//GameObject::~GameObject();
	}

	void Zombie::update()
	{
		GameObject::update();

		time += Time::step();
		while( time > .1f )
        {
            time -= .1f;
            updateFrame();
        }
	}

	void Zombie::updateFrame()
	{
	    ++frame;
        //Logger::print( Logger::INFO, "Anim: " + activeAction + ", Frame: " + to_s(frame) );
	    if(frame >= currentAnim.size()) frame = 0;
	    this->getBody()->setMesh(currentAnim[frame]);
	}

	//Zombie::playNow for switching between animations
	void Zombie::playNow( std::string action )
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
        else if( action == "ATTACK" && action != activeAction )
        {
            activeAction = "ATTACK";
            currentAnim = attack;
        }
        else if( action == "DEATH" && action != activeAction )
        {
            activeAction = "DEATH";
            currentAnim = death;
        }
	}

	void Zombie::setViking(bool value)
	{
	    _viking = value;
	}
	bool Zombie::getViking()
	{
	    return _viking;
	}
}
