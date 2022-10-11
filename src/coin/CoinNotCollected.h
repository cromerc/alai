#ifndef ALAI_COIN_COIN_NOT_COLLECTED_H
#define ALAI_COIN_COIN_NOT_COLLECTED_H

#include "state_machine/State.h"

#include <AnimatedSprite.hpp>
#include <Godot.hpp>

namespace alai
{
    /**
     * @brief This class controls what happens when the Coin is in the not collected state.
     * 
     */
    class CoinNotCollected : public alai::State
    {
            GODOT_CLASS(CoinNotCollected, alai::State)

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
             * @brief Construct a new CoinNotCollected object.
             * 
             */
            CoinNotCollected();

            /**
             * @brief Destroy the CoinNotCollected object.
             * 
             */
            ~CoinNotCollected();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            /**
             * @brief Called when the not collected state of the coin is entered.
             * 
             */
            void _state_enter();

            /**
             * @brief Called when the not collected state of the coin is exited.
             * 
             */
            void _state_exit();

            /**
             * @brief Method called on body entered.
             * 
             * @param[in] node Node interacting with whoever 
             */
            void _on_body_entered(Node *node);
    };
} // namespace alai

#endif
