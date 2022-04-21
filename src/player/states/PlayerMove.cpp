#include "player/states/PlayerMove.h"
#include "player/Player.h"

using namespace godot;
using namespace player;

void PlayerMove::_register_methods()
{
    register_method("_state_enter", &PlayerMove::_state_enter);
    register_method("_state_exit", &PlayerMove::_state_exit);
    register_method("_physics_process", &PlayerMove::_physics_process);
}

PlayerMove::PlayerMove()
{
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::_init()
{
    _input = Input::get_singleton();
}

void PlayerMove::_state_enter()
{
    animated_sprite = get_parent()->get_node<AnimatedSprite>("AnimatedSprite");
    animated_sprite->set_animation("move");
    animated_sprite->play();
}

void PlayerMove::_state_exit()
{
}

void PlayerMove::_physics_process(float delta)
{
    auto parent = Object::cast_to<player::Player>(get_parent());

    auto direction_pressed = false;

    auto current_speed = parent->get_speed();
    auto velocity = parent->get_velocity();
    velocity.x = 0;
    if (_input->is_action_pressed("run"))
    {
        current_speed *= parent->get_run_speed();
    }

    if (_input->is_action_pressed("right"))
    {
        direction_pressed = true;
        velocity.x += current_speed;
    }

    if (_input->is_action_pressed("left"))
    {
        direction_pressed = true;
        velocity.x += -current_speed;
    }

    if (_input->is_action_just_pressed("jump"))
    {
        get_state_machine()->change("Jump");
        return;
    }

    if (velocity.x > 0)
    {
        animated_sprite->set_flip_h(true);
    }
    else if (velocity.x < 0)
    {
        animated_sprite->set_flip_h(false);
    }
    else
    {
        if (!direction_pressed)
        {
            get_state_machine()->change("Idle");
        }
        return;
    }

    parent->set_velocity(velocity);

    if (!parent->is_on_floor())
    {
        get_state_machine()->change("Fall");
        return;
    }
}
