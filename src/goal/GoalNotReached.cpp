#include "goal/GoalNotReached.h"

#include <Area2D.hpp>

void alai::GoalNotReached::_register_methods()
{
    godot::register_method("_state_enter", &GoalNotReached::_state_enter);
    godot::register_method("_state_exit", &GoalNotReached::_state_exit);
    godot::register_method("_on_Goal_body_entered", &GoalNotReached::_on_Goal_body_entered);
}

alai::GoalNotReached::GoalNotReached()
{
}

alai::GoalNotReached::~GoalNotReached()
{
}

void alai::GoalNotReached::_init()
{
}

void alai::GoalNotReached::_state_enter()
{
    animated_sprite = get_parent()->get_node<godot::AnimatedSprite>("AnimatedSprite");
    animated_sprite->set_animation("flagmove");
    animated_sprite->play();
}

void alai::GoalNotReached::_state_exit()
{
}

void alai::GoalNotReached::_on_Goal_body_entered(Node *node)
{
    auto parent_node = get_parent();

    if (parent_node != nullptr)
    {
        auto goal = Object::cast_to<godot::Area2D>(parent_node);
        goal->set_collision_mask_bit(0, false);
    }

    get_state_machine()->change("GoalReached");
}
