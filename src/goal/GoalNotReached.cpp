#include "goal/GoalNotReached.h"
#include <Area2D.hpp>

using namespace godot;


void GoalNotReached::_register_methods()
{
    register_method("_state_enter", &GoalNotReached::_state_enter);
    register_method("_state_exit", &GoalNotReached::_state_exit);
    register_method("_on_Goal_body_entered", &GoalNotReached::_on_Goal_body_entered);
}

GoalNotReached::GoalNotReached()
{
}

GoalNotReached::~GoalNotReached()
{
}

void GoalNotReached::_init()
{

}

void GoalNotReached::_state_enter()
{
    animated_sprite = get_parent()->get_node<AnimatedSprite>("AnimatedSprite");
    animated_sprite->set_animation("flagmove");
    animated_sprite->play();
}

void GoalNotReached::_state_exit()
{
    
}

void GoalNotReached::_on_Goal_body_entered(Node *node)
{
    auto parent_node = get_parent();

    if (parent_node != nullptr)
    {
        auto goal = Object::cast_to<Area2D>(parent_node);
        goal->set_collision_mask_bit(0, false);
    }
    
    get_state_machine()->change("GoalReached");
    
    
}



