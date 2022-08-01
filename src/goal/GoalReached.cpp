#include "goal/GoalReached.h"
#include <Area2D.hpp>

using namespace godot;

void GoalReached::_register_methods()
{
    register_method("_state_enter", &GoalReached::_state_enter);
    register_method("_state_exit", &GoalReached::_state_exit);
}

GoalReached::GoalReached()
{
}

GoalReached::~GoalReached()
{
}

void GoalReached::_init()
{

}

void GoalReached::_state_enter()
{
    Godot::print("Flag touched");

    
}

void GoalReached::_state_exit()
{
    
}

