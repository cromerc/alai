#include "coin/CoinCollected.h"
#include <AnimationPlayer.hpp>
#include "Event.h"

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
    auto event = get_node<alai::Event>("/root/Event");
    event->emit_signal("coin_collected", 1);
    this->get_parent()->queue_free();


   // get_state_machine()->change("CoinCounter");

}


