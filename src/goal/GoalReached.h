#ifndef ALAI_GOAL_GOAL_REACHED_H
#define ALAI_GOAL_GOAL_REACHED_H

#include "state_machine/State.h"

#include <AnimatedSprite.hpp>
#include <Godot.hpp>

namespace alai
{
    /**
     * @brief This class controls what happens when the goal flag is in the reached state.
     * 
     */
    class GoalReached : public alai::State
    {
            GODOT_CLASS(GoalReached, alai::State)

        private:
            /**
             * @brief The animated sprite of the Coin.
             * 
             */
            godot::AnimatedSprite *animated_sprite;

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new GoalReached object.
             * 
             */
            GoalReached();

            /**
             * @brief Destroy the GoalReached object.
             * 
             */
            ~GoalReached();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            /**
             * @brief Called when the collected state of the coin is entered.
             * 
             */
            void _state_enter();

            /**
             * @brief Called when the collected state of the coin is exited.
             * 
             */
            void _state_exit();

            /**
             * @brief Called when the animation of the collected coin has finished.
             * 
             */
    };
} // namespace alai

#endif
