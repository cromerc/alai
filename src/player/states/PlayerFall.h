#ifndef JUEGO_PLAYER_FALL_H
#define JUEGO_PLAYER_FALL_H

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>

namespace godot
{
    namespace player
    {
        class PlayerFall : public State
        {
            GODOT_CLASS(PlayerFall, State)

            private:
                Input *_input;
                AnimatedSprite *animated_sprite;

            public:
                static void _register_methods();

                PlayerFall();

                ~PlayerFall();

                /**
                 * @brief Initialize the class from Godot.
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                void _state_enter();

                void _state_exit();

                void _physics_process(float delta);
        };
    }
}

#endif
