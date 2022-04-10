#include <Godot.hpp>

#include "StateMachine.h"
#include "State.h"
#include "Walk.h"
#include "Run.h"
#include "Main.h"
#include "Player.h"
#include "PlayerIdle.h"

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
    register_class<StateMachine>();
    register_class<State>();
    register_class<Walk>();
    register_class<Run>();
    register_class<Main>();
    register_class<Player>();
    register_class<PlayerIdle>();
}
