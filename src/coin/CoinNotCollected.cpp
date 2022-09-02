#include "coin/CoinNotCollected.h"

#include <Area2D.hpp>

void alai::CoinNotCollected::_register_methods()
{
    godot::register_method("_state_enter", &CoinNotCollected::_state_enter);
    godot::register_method("_state_exit", &CoinNotCollected::_state_exit);
    godot::register_method("_on_body_entered", &CoinNotCollected::_on_body_entered);
}

alai::CoinNotCollected::CoinNotCollected()
{
}

alai::CoinNotCollected::~CoinNotCollected()
{
}

void alai::CoinNotCollected::_init()
{
}

void alai::CoinNotCollected::_state_enter()
{
    animated_sprite = get_parent()->get_node<godot::AnimatedSprite>("AnimatedSprite");
    animated_sprite->set_animation("spin");
    animated_sprite->play();
}

void alai::CoinNotCollected::_state_exit()
{
}

void alai::CoinNotCollected::_on_body_entered(Node *node)
{
    auto parent_node = get_parent();

    if (parent_node != nullptr)
    {
        auto coin = Object::cast_to<godot::Area2D>(parent_node);
        coin->set_collision_mask_bit(0, false);
    }
    
    get_state_machine()->change("CoinCollected");
}
