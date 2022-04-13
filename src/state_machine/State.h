#ifndef JUEGO_STATE_H
#define JUEGO_STATE_H

#include "StateMachine.h"

#include <Godot.hpp>
#include <Node.hpp>

namespace godot
{
    /**
     * @brief This class provides a virtual template state that real states should extend from and override.
     * 
     */
    class State : public StateMachine
    {
        GODOT_CLASS(State, Node)

        private:
            /**
             * @brief The state's parent, this is the node 1 level above the state machine.
             * 
             */
            Node *parent;
            /**
             * @brief The state machine itself, used to handle all state related work.
             * 
             */
            StateMachine *state_machine;

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new State object.
             * 
             */
            State();

            /**
             * @brief Destroy the State object.
             * 
             */
            ~State();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            virtual void _init();

            /**
             * @brief This is called when a state is entered.
             * 
             * @param[in] state This will contain the previous state.
             * @param[in] args The arguments passed to the state.
             */
            virtual void _state_enter(const String state, const Array args = Array());

            /**
             * @brief This is called when a state is exited.
             * 
             * @param[in] state The state we are going to.
             * @param[in] args The arguments passed to the state.
             */
            virtual void _state_exit(const String state, const Array args = Array());

            /**
             * @brief Set the parent object.
             * 
             * @param[in] parent The parent of the state.
             */
            virtual void set_parent(Node *parent) final;

            /**
             * @brief Get the parent object.
             * 
             * @return Node* The parent of the state.
             */
            virtual Node *get_parent() final;

            /**
             * @brief Set the state machine object.
             * 
             * @param[in] state_machine The state machine.
             */
            virtual void set_state_machine(StateMachine *state_machine) final;

            /**
             * @brief Get the state machine object.
             * 
             * @return StateMachine* The state machine.
             */
            virtual StateMachine *get_state_machine() final;
    };
}

#endif
