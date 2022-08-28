#include "goal/GoalReached.h"

#include <Area2D.hpp>

void alai::GoalReached::_register_methods()
{
    register_method("_state_enter", &GoalReached::_state_enter);
    register_method("_state_exit", &GoalReached::_state_exit);
}

alai::GoalReached::GoalReached()
{
}

alai::GoalReached::~GoalReached()
{
}

void alai::GoalReached::_init()
{
}

void alai::GoalReached::_state_enter()
{
    godot::Godot::print("Flag touched");
}

void alai::GoalReached::_state_exit()
{
}
