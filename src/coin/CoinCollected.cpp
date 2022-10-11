#include "Event.h"
#include "coin/CoinCollected.h"

#include <AnimationPlayer.hpp>
#include <AudioStreamPlayer.hpp>

void alai::CoinCollected::_register_methods()
{
    godot::register_method("_state_enter", &CoinCollected::_state_enter);
    godot::register_method("_state_exit", &CoinCollected::_state_exit);
    godot::register_method("_on_animation_finished", &CoinCollected::_on_animation_finished);
}

alai::CoinCollected::CoinCollected()
{
}

alai::CoinCollected::~CoinCollected()
{
}

void alai::CoinCollected::_init()
{
}

void alai::CoinCollected::_state_enter()
{
    auto node = get_parent()->find_node("AnimationPlayer");

    if (node != nullptr)
    {
        auto animation_player = Object::cast_to<godot::AnimationPlayer>(node);
        animation_player->play("jump");
    }
    auto coin_collected_sound = get_parent()->get_node<godot::AudioStreamPlayer>("CoinCollectedSound");
    coin_collected_sound->play();
}

void alai::CoinCollected::_state_exit()
{
}

void alai::CoinCollected::_on_animation_finished(godot::String anim_name)
{
    auto event = get_node<alai::Event>("/root/Event");
    event->emit_signal("coin_collected", 1);
    this->get_parent()->queue_free();
}
