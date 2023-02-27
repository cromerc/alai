#include "CameraLimit.h"
#include "Event.h"
#include "Main.h"
#include "coin/CoinCollected.h"
#include "coin/CoinCounter.h"
#include "coin/CoinNotCollected.h"
#include "goal/GoalNotReached.h"
#include "goal/GoalReached.h"
#include "gui/game_over/GameOverScreen.h"
#include "gui/game_won/GameWonScreen.h"
#include "player/AI.h"
#include "player/Player.h"
#include "player/states/PlayerFall.h"
#include "player/states/PlayerIdle.h"
#include "player/states/PlayerJump.h"
#include "player/states/PlayerMove.h"
#include "state_machine/State.h"
#include "state_machine/StateMachine.h"

#include <Godot.hpp>

/**
 * @brief This function connects the gdnative init function.
 *
 */
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    godot::Godot::gdnative_init(o);
}

/**
 * @brief This function connects the gdnative terminate function.
 *
 */
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    // This next line is a workaround to fix bug:
    // https://github.com/godotengine/godot/issues/48295
    godot::Godot::nativescript_terminate(godot::_RegisterState::nativescript_handle);
    godot::Godot::gdnative_terminate(o);
}

/**
 * @brief This function connects the init methods in the classes to godot's gdnative.
 *
 */
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    godot::Godot::nativescript_init(handle);

    godot::register_class<alai::Event>();
    godot::register_class<alai::StateMachine>();
    godot::register_class<alai::State>();
    godot::register_class<alai::Main>();
    godot::register_class<alai::CameraLimit>();
    godot::register_class<alai::player::Player>();
    godot::register_class<alai::player::AI>();
    godot::register_class<alai::player::PlayerIdle>();
    godot::register_class<alai::player::PlayerMove>();
    godot::register_class<alai::player::PlayerJump>();
    godot::register_class<alai::player::PlayerFall>();
    godot::register_class<alai::CoinNotCollected>();
    godot::register_class<alai::CoinCollected>();
    godot::register_class<alai::CoinCounter>();
    godot::register_class<alai::GoalReached>();
    godot::register_class<alai::GoalNotReached>();
    godot::register_class<alai::GameOverScreen>();
    godot::register_class<alai::GameWonScreen>();
}
