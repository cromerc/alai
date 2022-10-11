#ifndef ALAI_STATE_MACHINE_STATE_MACHINE_H
#define ALAI_STATE_MACHINE_STATE_MACHINE_H

#include <Godot.hpp>
#include <Node.hpp>

namespace alai
{
    /**
     * @brief This class provides a finite state machine that can be used with any scene and node.
     * 
     */
    class StateMachine : public godot::Node
    {
            GODOT_CLASS(StateMachine, godot::Node)

        private:
            /**
             * @brief The parent node which is one level above the state machine.
             * 
             */
            godot::Node *parent;
            /**
             * @brief The default state for the state machine to run.
             * 
             * @details If this is not set, the state machine will try to run the first state node.
             * If no state nodes are present, an error will be printed and the state machine will not work.
             */
            godot::String default_state;
            /**
             * @brief If set to true the state machine will print a message showing when it enters or exits a state.
             * 
             */
            bool debug;
            /**
             * @brief The current state the machine is in.
             * 
             */
            godot::String current_state;
            /**
             * @brief A list of the states in the state machine.
             * 
             */
            godot::Dictionary states;

            /**
             * @brief This adds all nodes of the states machine as states in the machine.
             * 
             */
            void add_states();

            /**
             * @brief This adds a state to the list of states in the state machine.
             * 
             * @param[in] state The new state.
             * @param[in] child The godot node which represents the state.
             */
            void add_state(const godot::String state, godot::Node *child);

            /**
             * @brief Set the current state object.
             * 
             * @param[in] current_state The current state that is running.
             */
            void set_current_state(const godot::String current_state);

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new StateMachine object.
             */
            StateMachine();

            /**
             * @brief Destroy the StateMachine object.
             */
            ~StateMachine();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            /**
             * @brief Code to be run when ready.
             * 
             * @details This method is run when all the children of this node are ready.
             */
            void _ready();

            /**
             * @brief This method will remove all no default states from the scene tree and start the default state.
             * 
             */
            void setup();

            /**
             * @brief Check if the given state is the current running state.
             * 
             * @param[in] state The state to compare with the running state.
             * @return true If the running state and given state are the same.
             * @return false If the running state and given state are not the same.
             */
            bool is_current(const godot::String state);

            /**
             * @brief Check if the state machine has a given state.
             * 
             * @param[in] state The state to check for.
             * @return true If the state exists.
             * @return false If the state doesn't exist.
             */
            bool has(const godot::String state);

            /**
             * @brief Restar the running state by calling its enter and exit methods.
             * 
             * @param[in] state The state that is being restarted.
             * @param[in] args The arguments to pass to the state on exit and enter.
             */
            void restart(const godot::String state, const godot::Array &args = godot::Array());

            /**
             * @brief Change to a different state.
             * 
             * @details If the running state is the same as the state it will restart it.
             * 
             * @param[in] state The state to change to.
             * @param[in] args The arguments to pass to the exiting state and the entering state.
             */
            void change(const godot::String state, const godot::Array &args = godot::Array());

            /**
             * @brief Call a registered godot method in the class.
             * 
             * @param[in] method The method name to call.
             * @param[in] args The arguments to pass to the method.
             * @return Variant Returns a Variant based off what the method returns.
             */
            godot::Variant call(const godot::String method, const godot::Array &args = godot::Array());

            /**
             * @brief This method is to link up a signal call back.
             * 
             * @param[in] method The method to call for the signal.
             * @param[in] args The arguments to pass to the method.
             * @return Variant Returns a Variant based off what the method returns.
             */
            godot::Variant _call(const godot::String method, const godot::Array &args = godot::Array());

            /**
             * @brief Set the default state object.
             * 
             * @param[in] default_state The new default state.
             */
            void set_default_state(const godot::String default_state);

            /**
             * @brief Get the default state object.
             * 
             * @return String The default state.
             */
            godot::String get_default_state();

            /**
             * @brief Get the current state object.
             * 
             * @return String The current running state.
             */
            godot::String get_current_state();

            /**
             * @brief Set the debug object.
             * 
             * @param[in] debug Whether or not to debug.
             */
            void set_debug(bool debug);

            /**
             * @brief Get the debug object.
             * 
             * @return true If debugging is enabled.
             * @return false If debugging is disabled.
             */
            bool get_debug();

            /**
             * @brief This method is called when the signal tree_entered is emitted.
             * 
             * @details This will run the setup method to prepare the state machine for use.
             */
            void _on_StateMachine_tree_entered();

            /**
             * @brief This method is called when the signal tree_exiting is emitted.
             * 
             * @details If the tree is in the exiting state readd all the removed state nodes to the scene tree.
             * This is important because the memory won't be freed if they are no longer in the scene tree.
             */
            void _on_StateMachine_tree_exiting();

            /**
             * @brief Restarts the running state.
             * 
             * @param Args Variable number of arguments to pass to restart.
             * @param[in] state The state being restarted.
             * @param[in] args The arguments to pass when restarting.
             */
            template<class... Args> void restart(const godot::String state, Args... args)
            {
                return restart(state, godot::Array::make(args...));
            }

            /**
             * @brief Changes to a new state.
             * 
             * @param Args Variable number of arguments to pass when changing states.
             * @param[in] state The state to change to.
             * @param[in] args The arguments to pass to the new state.
             */
            template<class... Args> void change(const godot::String state, Args... args)
            {
                return change(state, godot::Array::make(args...));
            }

            /**
             * @brief Call a registered godot method in the class.
             * 
             * @param Args The variable arguments to pass to the method.
             * @param[in] method The method to call.
             * @param[in] args The arguments to pass to it.
             * @return Variant The Variant object returned by the method called.
             */
            template<class... Args> godot::Variant call(const godot::String method, Args... args)
            {
                return call(method, godot::Array::make(args...));
            }

            /**
             * @brief This is used to connect a callback from a signal.
             * 
             * @param Args The arguments to pass to the callback method.
             * @param[in] method The method to call.
             * @param[in] args The arguments to pass.
             * @return Variant The Variant object returned by the method called.
             */
            template<class... Args> godot::Variant _call(const godot::String method, Args... args)
            {
                return _call(method, godot::Array::make(args...));
            }
    };
} // namespace alai

#endif
