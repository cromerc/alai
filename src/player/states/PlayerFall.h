#ifndef JUEGO_PLAYER_FALL_H
#define JUEGO_PLAYER_FALL_H

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>

/**
 * @brief This is the godot namespace for all the code included in the library.
 * 
 * @details This namespace is used a prefix when the Godot engine looks for classes, methods, and properties.
 */
namespace godot
{
    namespace player
    {
        /**
         * @brief This class controls what happens when the player is in a falling state.
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
                Input *_input;

                /**
                 * @brief The animated sprite connected to the player.
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
                 * @brief Construct a new Player Fall object.
                 * 
                 */
                PlayerFall();

                /**
                 * @brief Destroy the Player Fall object.
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
    }
}

#endif
