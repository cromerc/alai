#include "player/states/PlayerIdle.h"
#include "player/Player.h"

using namespace godot;
using namespace player;

void PlayerIdle::_register_methods()
{
    register_method("_state_enter", &PlayerIdle::_state_enter);
    register_method("_state_exit", &PlayerIdle::_state_exit);
    register_method("_physics_process", &PlayerIdle::_physics_process);
}

PlayerIdle::PlayerIdle()
{
}

PlayerIdle::~PlayerIdle()
{
}

void PlayerIdle::_init()
{
    _input = Input::get_singleton();
}

void PlayerIdle::_state_enter()
{
    animated_sprite = get_parent()->get_node<AnimatedSprite>("AnimatedSprite");
    animated_sprite->stop();
    animated_sprite->set_animation("idle");
}

void PlayerIdle::_state_exit()
{
}

void PlayerIdle::_physics_process(float delta)
{
    auto parent = Object::cast_to<player::Player>(get_parent());

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
