#ifndef ALAI_COIN_COIN_COLLECTED_H
#define ALAI_COIN_COIN_COLLECTED_H

#include "state_machine/State.h"

#include <AnimatedSprite.hpp>
#include <Godot.hpp>

namespace alai
{
    /**
     * @brief This class controls what happens when the Coin is in the collected state.
     * 
     */
    class CoinCollected : public alai::State
    {
        GODOT_CLASS(CoinCollected, alai::State)

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
             * @brief Construct a new CoinCollected object.
             * 
             */
            CoinCollected();

            /**
             * @brief Destroy the CoinCollected object.
             * 
             */
            ~CoinCollected();

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
            void _on_animation_finished(godot::String anim_name);
    };
}

#endif
