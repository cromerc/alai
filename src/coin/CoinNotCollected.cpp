#include "coin/CoinNotCollected.h"
#include <Area2D.hpp>

using namespace godot;

void CoinNotCollected::_register_methods()
{
    register_method("_state_enter", &CoinNotCollected::_state_enter);
    register_method("_state_exit", &CoinNotCollected::_state_exit);
    register_method("_on_body_entered", &CoinNotCollected::_on_body_entered);
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
    animated_sprite->set_animation("spin");
    animated_sprite->play();
}

void CoinNotCollected::_state_exit()
{
    
}

void CoinNotCollected::_on_body_entered(Node *node)
{
    Godot::print("Coin touched");
    auto parent_node = get_parent();

    if (parent_node != nullptr)
    {
        auto coin = Object::cast_to<Area2D>(parent_node);
        coin->set_collision_mask_bit(0, false);
    }
    get_state_machine()->change("CoinCollected");
    
    
}



