#include "goal/GoalReached.h"

using namespace godot;

void GoalReached::_register_methods()
{
    register_method("_state_enter", &GoalReached::_state_enter);
    register_method("_state_exit", &GoalReached::_state_exit);
    //register_signal<GoalReached>("coin_collected", "amount", GODOT_VARIANT_TYPE_INT);
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

    
}

void GoalReached::_state_exit()
{
    
}

