#ifndef JUEGO_PLAYER_JUMP_H
#define JUEGO_PLAYER_JUMP_H

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>

namespace godot
{
    namespace player
    {
        /**
         * @brief This class control what happens when the player is in the jump state.
         * 
         */
        class PlayerJump : public State
        {
            GODOT_CLASS(PlayerJump, State)

            private:
                /**
                 * @brief Input singleton.
                 * 
                 */
                Input *_input;
                /**
                 * @brief The animated sprite connected to the player.
                 * 
                 */
                AnimatedSprite *animated_sprite;
                /**
                 * @brief If the player has already performed a double jump or not.
                 * 
                 */
                bool double_jumped;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * 
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new Player Jump object.
                 * 
                 */
                PlayerJump();

                /**
                 * @brief Destroy the Player Jump object.
                 * 
                 */
                ~PlayerJump();

                /**
                 * @brief Initialize the class from Godot.
                 * 
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                /**
                 * @brief Called when the player enters the jump state.
                 * 
                 * @details If the previous state was the jump state, a double jump was performed.
                 * 
                 * @param[in] state The previous state before this one was entered.
                 */
                void _state_enter(const String state);

                /**
                 * @brief Called when the player exits the jump state.
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
    }
}

#endif
