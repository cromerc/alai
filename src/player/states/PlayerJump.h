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
        class PlayerJump : public State
        {
            GODOT_CLASS(PlayerJump, State)

            private:
                Input *_input;
                AnimatedSprite *animated_sprite;
                bool double_jumped;

            public:
                static void _register_methods();

                PlayerJump();

                ~PlayerJump();

                /**
                 * @brief Initialize the class from Godot.
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                void _state_enter(const String state);

                void _state_exit();

                void _physics_process(float delta);
        };
    }
}

#endif
