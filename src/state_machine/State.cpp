#include "state_machine/State.h"

void alai::State::_register_methods()
{
    register_method("set_parent", &State::set_parent);
    register_method("get_parent", &State::get_parent);
    register_method("set_state_machine", &State::set_state_machine);
    register_method("_state_enter", &State::_state_enter);
    register_method("_state_exit", &State::_state_exit);
}

alai::State::State()
{
}

alai::State::~State()
{
}

void alai::State::_init()
{
}

void alai::State::_state_enter(const godot::String state, const godot::Array args)
{
    WARN_PRINT("State " + get_state_machine()->get_current_state() + " is missing its _state_enter method!");
}

void alai::State::_state_exit(const godot::String state, const godot::Array args)
{
    WARN_PRINT("State " + get_state_machine()->get_current_state() + " is missing its _state_exit method!");
}

void alai::State::set_parent(Node *parent)
{
    this->parent = parent;
}

godot::Node *alai::State::get_parent()
{
    return parent;
}

void alai::State::set_state_machine(alai::StateMachine *state_machine)
{
    this->state_machine = state_machine;
}

alai::StateMachine *alai::State::get_state_machine()
{
    return this->state_machine;
}
