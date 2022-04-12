#include "State.h"

using namespace godot;

void State::_register_methods()
{
    register_method("set_parent", &State::set_parent);
    register_method("get_parent", &State::get_parent);
    register_method("set_state_machine", &State::set_state_machine);
    register_method("_state_enter", &State::_state_enter);
    register_method("_state_exit", &State::_state_exit);
}

State::State()
{
}

State::~State()
{
}

void State::_init()
{
}

void State::_state_enter(const String state, const Array args)
{
    WARN_PRINT("State " + state + " is missing its _state_enter method!");
}

void State::_state_exit(const String state, const Array args)
{
    WARN_PRINT("State " + state + " is missing its _state_exit method!");
}

void State::set_parent(Node *parent)
{
    this->parent = parent;
}

Node *State::get_parent()
{
    return parent;
}

void State::set_state_machine(StateMachine *state_machine)
{
    this->state_machine = state_machine;
}

StateMachine *State::get_state_machine()
{
    return this->state_machine;
}
