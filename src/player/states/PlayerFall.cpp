#include "player/states/PlayerFall.h"
#include "player/Player.h"

void alai::player::PlayerFall::_register_methods()
{
    register_method("_state_enter", &PlayerFall::_state_enter);
    register_method("_state_exit", &PlayerFall::_state_exit);
    register_method("_physics_process", &PlayerFall::_physics_process);
}

alai::player::PlayerFall::PlayerFall()
{
}

alai::player::PlayerFall::~PlayerFall()
{
}

void alai::player::PlayerFall::_init()
{
    _input = godot::Input::get_singleton();
}

void alai::player::PlayerFall::_state_enter()
{
    animated_sprite = get_parent()->get_node<godot::AnimatedSprite>("AnimatedSprite");
    animated_sprite->stop();
    animated_sprite->set_animation("air");
}

void alai::player::PlayerFall::_state_exit()
{
    animated_sprite->set_animation("move");
    animated_sprite->set_frame(1);
}

void alai::player::PlayerFall::_physics_process(float delta)
{
    auto parent = Object::cast_to<Player>(get_parent());

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
