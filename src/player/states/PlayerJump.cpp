#include "player/states/PlayerJump.h"
#include "player/Player.h"

#include <AudioStreamPlayer.hpp>

using namespace godot;
using namespace player;

void PlayerJump::_register_methods()
{
    register_method("_state_enter", &PlayerJump::_state_enter);
    register_method("_state_exit", &PlayerJump::_state_exit);
    register_method("_physics_process", &PlayerJump::_physics_process);
}

PlayerJump::PlayerJump()
{
}

PlayerJump::~PlayerJump()
{
}

void PlayerJump::_init()
{
    _input = Input::get_singleton();
}

void PlayerJump::_state_enter(const String state)
{
    auto jump_sound = get_parent()->get_node<AudioStreamPlayer>("Sounds/Jump");
    jump_sound->play();

    animated_sprite = get_parent()->get_node<AnimatedSprite>("AnimatedSprite");
    animated_sprite->stop();
    animated_sprite->set_animation("air");

    if (state == "Jump")
    {
        double_jumped = true;
    }
    else
    {
        double_jumped = false;
    }

    auto parent = Object::cast_to<player::Player>(get_parent());
    auto velocity = parent->get_velocity();
    velocity.y = -parent->get_jump_force();
    parent->set_velocity(velocity);
}

void PlayerJump::_state_exit()
{
        animated_sprite->set_animation("move");
        animated_sprite->set_frame(1);
}

void PlayerJump::_physics_process(float delta)
{
    auto parent = Object::cast_to<player::Player>(get_parent());
    if (parent->is_on_floor())
    {
        get_state_machine()->change("Move");
        return;
    }

    auto current_speed = parent->get_speed();
    auto velocity = parent->get_velocity();
    velocity.x = 0;
    if (_input->is_action_pressed("run"))
    {
        current_speed *= parent->get_run_speed();
    }

    if (_input->is_action_pressed("right"))
    {
        velocity.x += current_speed;
    }

    if (_input->is_action_pressed("left"))
    {
        velocity.x += -current_speed;
    }

    if (_input->is_action_just_released("jump"))
    {
        if (velocity.y < -100)
        {
            velocity.y = -100;
        }
    }

    if (parent->get_double_jump() && !double_jumped && _input->is_action_just_pressed("jump"))
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

    parent->set_velocity(velocity);
}
