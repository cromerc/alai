#include <Godot.hpp>

#include "Event.h"
#include "state_machine/StateMachine.h"
#include "state_machine/State.h"
#include "Main.h"
#include "CameraLimit.h"
#include "player/Player.h"
#include "player/states/PlayerIdle.h"
#include "player/states/PlayerMove.h"
#include "player/states/PlayerJump.h"
#include "player/states/PlayerFall.h"
#include "coin/CoinNotCollected.h"
#include "coin/CoinCollected.h"
#include "coin/CoinCounter.h"
#include "goal/GoalReached.h"
#include "goal/GoalNotReached.h"

using namespace godot;

/**
 * @brief This function connects the gdnative init function.
 * 
 */
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    Godot::gdnative_init(o);
}

/**
 * @brief This function connects the gdnative terminate function.
 * 
 */
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    // This next line is a workaround to fix bug:
    // https://github.com/godotengine/godot/issues/48295
    Godot::nativescript_terminate(_RegisterState::nativescript_handle);
    Godot::gdnative_terminate(o);
}

/**
 * @brief This function connects the init methods in the classes to godot's gdnative.
 * 
 */
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    Godot::nativescript_init(handle);
    register_class<alai::Event>();
    register_class<StateMachine>();
    register_class<State>();
    register_class<main::Main>();
    register_class<CameraLimit>();
    register_class<player::Player>();
    register_class<player::PlayerIdle>();
    register_class<player::PlayerMove>();
    register_class<player::PlayerJump>();
    register_class<player::PlayerFall>();
    register_class<CoinNotCollected>();
    register_class<CoinCollected>();
    register_class<CoinCounter>();
    register_class<GoalReached>();
    register_class<GoalNotReached>();
}
