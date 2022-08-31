#include "goal/GoalReached.h"

#include "Event.h"

#include <Area2D.hpp>

void alai::GoalReached::_register_methods()
{
    godot::register_method("_state_enter", &GoalReached::_state_enter);
    godot::register_method("_state_exit", &GoalReached::_state_exit);
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
    auto event = get_node<alai::Event>("/root/Event");
    event->emit_signal("player_won");
}

void alai::GoalReached::_state_exit()
{
}
