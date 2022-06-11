#include "coin/CoinCollected.h"
#include <AnimationPlayer.hpp>

using namespace godot;

void CoinCollected::_register_methods()
{
    register_method("_state_enter", &CoinCollected::_state_enter);
    register_method("_state_exit", &CoinCollected::_state_exit);
    register_method("_on_animation_finished", &CoinCollected::_on_animation_finished);
}

CoinCollected::CoinCollected()
{
}

CoinCollected::~CoinCollected()
{
}

void CoinCollected::_init()
{

}

void CoinCollected::_state_enter()
{

    auto node = get_parent()->find_node("AnimationPlayer");

    if (node != nullptr)
    {
        auto animation_player = Object::cast_to<AnimationPlayer>(node);
        animation_player->play("jump");
    }
}

void CoinCollected::_state_exit()
{
    
}

void CoinCollected::_on_animation_finished(String anim_name)
{
    this->get_parent()->queue_free();

}


