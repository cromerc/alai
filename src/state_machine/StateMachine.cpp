#include "state_machine/StateMachine.h"
#include "state_machine/State.h"

void alai::StateMachine::_register_methods()
{
    godot::register_method("_ready", &StateMachine::_ready);
    godot::register_method("_on_StateMachine_tree_entered", &StateMachine::_on_StateMachine_tree_entered);
    godot::register_method("_on_StateMachine_tree_exiting", &StateMachine::_on_StateMachine_tree_exiting);
    godot::register_property<StateMachine, godot::String>("default_state", &StateMachine::set_default_state, &StateMachine::get_default_state, godot::String());
    godot::register_property<StateMachine, bool>("debug", &StateMachine::set_debug, &StateMachine::get_debug, false);
    godot::register_signal<StateMachine>("state_entered", "state", GODOT_VARIANT_TYPE_STRING);
    godot::register_signal<StateMachine>("state_exited", "state", GODOT_VARIANT_TYPE_STRING);
    godot::register_signal<StateMachine>("state_restarted", "state", GODOT_VARIANT_TYPE_STRING);
}

alai::StateMachine::StateMachine()
{
}

alai::StateMachine::~StateMachine()
{
}

void alai::StateMachine::_init()
{
    set_default_state(godot::String());
    set_debug(false);
}

void alai::StateMachine::_ready()
{
    connect("tree_entered", this, "_on_StateMachine_tree_entered");
    connect("tree_exiting", this, "_on_StateMachine_tree_exiting");
    parent = get_parent();
    add_states();
    if (has(get_default_state()))
    {
        set_current_state(get_default_state());
    }
    else
    {
        WARN_PRINT("The selected default state " + get_default_state() + " doesn't exist!");
    }
    setup();
}

void alai::StateMachine::setup()
{
    auto children = get_children();

    if (get_current_state() == "")
    {
        if (children.size() > 0)
        {
            WARN_PRINT("The state machine doesn't have a default state set, using first child!");
            auto child = Object::cast_to<Node>(children[0].operator Object*());
            set_current_state(child->get_name());
        }
        else
        {
            ERR_PRINT("The state machine doesn't have a default state set and has no child states!");
            return;
        }
    }

    for (uint8_t i = 0; i < children.size(); i++)
    {
        auto child = Object::cast_to<Node>(children[i].operator Object*());

        child->call("set_state_machine", this);

        child->call("set_parent", parent);

        if (child->get_name() != get_current_state())
        {
            this->remove_child(child);
        }
    }

    Node *state_node = Object::cast_to<Node>(this->states[get_current_state()]);
    if (state_node->has_method("_state_enter"))
    {
        this->call("_state_enter", get_current_state());
    }
    else {
        WARN_PRINT("The state " + get_current_state() + " doesn't have a _state_enter method!");
    }
}

void alai::StateMachine::add_states()
{
    auto children = get_children();
    for (uint8_t i = 0; i < children.size(); i++)
    {
        auto child = Object::cast_to<Node>(children[i].operator Object*());
        add_state(child->get_name(), child);
    }
}

void alai::StateMachine::add_state(const godot::String state, Node *child)
{
    states[state] = child;
}

bool alai::StateMachine::is_current(const godot::String state)
{
    if (get_current_state() == "")
    {
        return false;
    }
    else
    {
        return get_current_state() == state;
    }
}

bool alai::StateMachine::has(const godot::String state)
{
    return states.has(state);
}

void alai::StateMachine::restart(const godot::String state, const godot::Array& args)
{
    this->call("_state_exit", state, args);
    this->call("_state_enter", state, args);
    this->emit_signal("state_restarted", get_current_state());
}

void alai::StateMachine::change(const godot::String state, const godot::Array &args)
{
    if (is_current(state))
    {
        return this->restart(state, args);
    }

    if (!has(state))
    {
        WARN_PRINT("The state " + state + " does not exist, called from state " + get_current_state() + "!");
        return;
    }

    auto previous_state = get_current_state();

    godot::Variant exiting;
    Node *state_node = Object::cast_to<Node>(this->states[previous_state]);
    if (state_node)
    {
        if (state_node->has_method("_state_exit"))
        {
            exiting = this->call("_state_exit", state, args);
        }
        else
        {
            WARN_PRINT("The state " + get_current_state() + " doesn't have a _state_exit method!");
        }
    }
    else
    {
        ERR_PRINT("Could not get current state node for " + get_current_state() + "!");
    }

    if (get_current_state() != "")
    {
        auto child = Object::cast_to<Node>(states[get_current_state()].operator Object*());
        if (child != nullptr)
        {
            this->remove_child(child);
        }
        this->emit_signal("state_exited", get_current_state());
        if (debug)
        {
            godot::Godot::print(get_current_state() + " exited!");
        }
    }

    set_current_state(state);
    auto child = Object::cast_to<Node>(states[get_current_state()].operator Object*());
    this->add_child(child);

    state_node = Object::cast_to<Node>(this->states[get_current_state()]);
    if (state_node)
    {
        if (state_node->has_method("_state_enter"))
        {
            this->call("_state_enter", previous_state, args);
        }
        else
        {
            WARN_PRINT("The state " + get_current_state() + " doesn't have a _state_enter method!");
        }
    }
    else
    {
        ERR_PRINT("Could not get current state node for " + get_current_state() + "!");
    }

    this->emit_signal("state_entered", get_current_state());
    if (debug)
    {
        godot::Godot::print(get_current_state() + " entered!");
    }
}

godot::Variant alai::StateMachine::call(const godot::String method, const godot::Array &args)
{
    auto node = Object::cast_to<Node>(states[get_current_state()].operator Object*());
    if (node)
    {
        if (node->has_method(method))
        {
            return node->call(method, args);
        }
        else
        {
            WARN_PRINT("The state " + get_current_state() + " doesn't contain the method " + method + "!");
            return godot::Variant();
        }
    }
    else
    {
        ERR_PRINT("Could not get current state node for " + get_current_state() + "!");
        return godot::Variant();
    }
}

godot::Variant alai::StateMachine::_call(const godot::String method, const godot::Array &args)
{
    return this->call(method, args);
}

void alai::StateMachine::set_default_state(const godot::String default_state)
{
    this->default_state = default_state;
}

godot::String alai::StateMachine::get_default_state()
{
    return this->default_state;
}

void alai::StateMachine::set_current_state(const godot::String current_sate)
{
    this->current_state = current_sate;
}

godot::String alai::StateMachine::get_current_state()
{
    return this->current_state;
}

void alai::StateMachine::set_debug(bool debug)
{
    this->debug = debug;
}

bool alai::StateMachine::get_debug()
{
    return this->debug;
}

void alai::StateMachine::_on_StateMachine_tree_entered()
{
    setup();
}

void alai::StateMachine::_on_StateMachine_tree_exiting()
{
    auto keys = states.keys();
    for (uint8_t i = 0; i < keys.size(); i++)
    {
        auto child = Object::cast_to<Node>(states[keys[i]].operator Object*());
        if (child)
        {
            auto children = get_children();
            if (!children.has(child))
            {
                this->add_child(child);
            }
        }
        else
        {
            ERR_PRINT("Could not get child node!");
            return;
        }
    }
}
