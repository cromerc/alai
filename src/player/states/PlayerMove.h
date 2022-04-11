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
        class PlayerMove : public State
        {
            GODOT_CLASS(PlayerMove, State)

            private:
                Input *_input;
                AnimatedSprite *animated_sprite;

            public:
                static void _register_methods();

                PlayerMove();

                ~PlayerMove();

                /**
                 * @brief Initialize the class from Godot.
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                void _state_enter(String state, Array args);

                void _state_exit();

                void _physics_process(float delta);

                Vector2 move_player(Vector2 velocity);
        };
    }
}

#endif
