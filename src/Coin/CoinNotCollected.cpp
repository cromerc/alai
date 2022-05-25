#include "player/states/CoinNotCollected.h"

using namespace godot;

void CoinNotCollected::_register_methods()
{
    register_method("_state_enter", &CoinNotCollected::_state_enter);
    register_method("_state_exit", &CoinNotCollected::_state_exit);
    register_method("_physics_process", &CoinNotCollected::_physics_process);
}

CoinNotCollected::CoinNotCollected()
{
}

CoinNotCollected::~CoinNotCollected()
{
}

void CoinNotCollected::_init()
{

}

void CoinNotCollected::_state_enter()
{
    animated_sprite = get_parent()->get_node<AnimatedSprite>("AnimatedSprite");
    animated_sprite->stop();
    animated_sprite->set_animation("idle");
}

void CoinNotCollected::_state_exit()
{
}

void CoinNotCollected::_physics_process(float delta)
{
   
}
