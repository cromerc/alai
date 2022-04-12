#ifndef JUEGO_STATE_H
#define JUEGO_STATE_H

#include "StateMachine.h"

#include <Godot.hpp>
#include <Node.hpp>

namespace godot
{
    class State : public StateMachine
    {
        GODOT_CLASS(State, Node)

        private:
            StateMachine *state_machine;

        public:
            Node *parent;
            static void _register_methods();

            State();

            ~State();

            /**
             * @brief Initialize the class from Godot.
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            virtual void _init();

            virtual void _state_enter(const String state, const Array args = Array());

            virtual void _state_exit(const String state, const Array args = Array());

            virtual void set_parent(Node *parent) final;

            virtual Node *get_parent() final;

            virtual void set_state_machine(StateMachine *state_machine) final;

            virtual StateMachine *get_state_machine() final;
    };
}

#endif
