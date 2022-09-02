#include "player/states/PlayerIdle.h"

#include "player/Player.h"

void alai::player::PlayerIdle::_register_methods()
{
    godot::register_method("_state_enter", &PlayerIdle::_state_enter);
    godot::register_method("_state_exit", &PlayerIdle::_state_exit);
    godot::register_method("_physics_process", &PlayerIdle::_physics_process);
}

alai::player::PlayerIdle::PlayerIdle()
{
}

alai::player::PlayerIdle::~PlayerIdle()
{
}

void alai::player::PlayerIdle::_init()
{
    _input = godot::Input::get_singleton();
}

void alai::player::PlayerIdle::_state_enter()
{
    animated_sprite = get_parent()->get_node<godot::AnimatedSprite>("AnimatedSprite");
    animated_sprite->stop();
    animated_sprite->set_animation("idle");
}

void alai::player::PlayerIdle::_state_exit()
{
}

void alai::player::PlayerIdle::_physics_process(float delta)
{
    auto parent = Object::cast_to<Player>(get_parent());

    if (_input->is_action_pressed("right"))
    {
        get_state_machine()->change("Move");
        return;
    }

    if (_input->is_action_pressed("left"))
    {
        get_state_machine()->change("Move");
        return;
    }

    if (_input->is_action_just_pressed("jump"))
    {
        get_state_machine()->change("Jump");
        return;
    }

    if (!parent->is_on_floor())
    {
        get_state_machine()->change("Fall");
        return;
    }
}
