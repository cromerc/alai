#ifndef JUEGO_STATE_MACHINE_H
#define JUEGO_STATE_MACHINE_H

#include <Godot.hpp>
#include <Node.hpp>

namespace godot
{
    class StateMachine : public Node
    {
        GODOT_CLASS(StateMachine, Node)

        private:
            Node *parent;
            String default_state;
            bool debug;
            String current_state;
            Dictionary states;

            void add_state(const String state, Node *child);

        public:
            static void _register_methods();

            StateMachine();

            ~StateMachine();

            /**
             * @brief Initialize the class from Godot.
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            /**
             * @brief Code to be run when ready.
             * @details This method is run when all the children of this node are ready.
             */
            void _ready();

            void setup();

            bool is_current();

            bool is_current(const String state);

            bool has(const String state);

            void restart(const String state, const Array& args = Array());

            void change(const String state, const Array &args = Array());

            Variant call(const String method, const Array &args = Array());

            Variant _call(const String method, const Array &args = Array());

            template <class ...Args> Variant restart(Args ...args)
            {
                return restart(Array::make(args...));
            }

            template <class ...Args> Variant change(const String state, Args ...args)
            {
                return change(state, Array::make(args...));
            }

            template <class ...Args> Variant call(const String method, Args ...args)
            {
                return call(method, Array::make(args...));
            }

            template <class ...Args> Variant _call(const String method, Args ...args)
            {
                return _call(method, Array::make(args...));
            }

            void set_default_state(const String new_default_state);

            String get_default_state();

            void set_debug(bool debug);

            bool get_debug();

            void set_current_state(const String new_current_state);

            String get_current_state();

            void _on_StateMachine_tree_entered();

            void _on_StateMachine_tree_exiting();
    };
}

#endif
