#include <Godot.hpp>

#include "Main.h"
#include "Player.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    // This next line is a workaround to fix bug:
    // https://github.com/godotengine/godot/issues/48295
    Godot::nativescript_terminate(_RegisterState::nativescript_handle);
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    Godot::nativescript_init(handle);
    register_class<Main>();
    register_class<Player>();
}
