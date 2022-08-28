#include "Event.h"

void alai::Event::_register_methods()
{
    godot::register_signal<Event>("object_created", "name", GODOT_VARIANT_TYPE_STRING, "state", GODOT_VARIANT_TYPE_STRING, "position", GODOT_VARIANT_TYPE_VECTOR2, "velocity", GODOT_VARIANT_TYPE_VECTOR2);
    godot::register_signal<Event>("object_updated", "name", GODOT_VARIANT_TYPE_STRING, "state", GODOT_VARIANT_TYPE_STRING, "position", GODOT_VARIANT_TYPE_VECTOR2, "velocity", GODOT_VARIANT_TYPE_VECTOR2);
    godot::register_signal<Event>("object_removed", "name", GODOT_VARIANT_TYPE_STRING);
    godot::register_signal<Event>("coin_collected", "amount", GODOT_VARIANT_TYPE_INT);
    godot::register_signal<Event>("player_died");

}

alai::Event::Event()
{
}

alai::Event::~Event()
{
}

void alai::Event::_init()
{
}
