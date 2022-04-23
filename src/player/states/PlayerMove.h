#ifndef JUEGO_PLAYER_MOVE_H
#define JUEGO_PLAYER_MOVE_H

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>

namespace godot
{
    namespace player
    {
        /**
         * @brief This class controls what happens when the Player is in the move state.
         * 
         */
        class PlayerMove : public State
        {
            GODOT_CLASS(PlayerMove, State)

            private:
                /**
                 * @brief Input singleton.
                 * 
                 */
                Input *_input;
                /**
                 * @brief The animated sprite of the Player.
                 * 
                 */
                AnimatedSprite *animated_sprite;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * 
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new PlayerMove object.
                 * 
                 */
                PlayerMove();

                /**
                 * @brief Destroy the PlayerMove object.
                 * 
                 */
                ~PlayerMove();

                /**
                 * @brief Initialize the class from Godot.
                 * 
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                /**
                 * @brief Called when the player enters the move state.
                 * 
                 */
                void _state_enter();

                /**
                 * @brief Called when the player exists the move state.
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
