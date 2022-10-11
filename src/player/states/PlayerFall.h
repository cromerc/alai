#ifndef ALAI_PLAYER_STATES_PLAYER_FALL_H
#define ALAI_PLAYER_STATES_PLAYER_FALL_H

#include "state_machine/State.h"

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <Input.hpp>

namespace alai
{
    namespace player
    {
        /**
         * @brief This class controls what happens when the Player is in a falling state.
         * 
         */
        class PlayerFall : public State
        {
                GODOT_CLASS(PlayerFall, State)

            private:
                /**
                 * @brief Input singleton.
                 * 
                 */
                godot::Input *_input;

                /**
                 * @brief The animated sprite connected to the Player.
                 * 
                 */
                godot::AnimatedSprite *animated_sprite;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * 
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new PlayerFall object.
                 * 
                 */
                PlayerFall();

                /**
                 * @brief Destroy the PlayerFall object.
                 * 
                 */
                ~PlayerFall();

                /**
                 * @brief Initialize the class from Godot.
                 * 
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                /**
                 * @brief Called when the fall state is entered.
                 * 
                 */
                void _state_enter();

                /**
                 * @brief Called when the fall state is exited.
                 * 
                 */
                void _state_exit();

                /**
                 * @brief The physics processed every delta time.
                 * 
                 * @param[in] delta The time since the method was last run.
                 */
                void _physics_process(float delta);
        };
    } // namespace player
} // namespace alai

#endif
