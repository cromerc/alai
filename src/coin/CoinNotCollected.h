#ifndef ALAI_COIN_NOT_COLLECTED
#define ALAI_COIN_NOT_COLLECTED

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Node.hpp>
#include <AnimatedSprite.hpp>

namespace godot
{
        /**
         * @brief This class controls what happens when the Coin is in the not collected state.
         * 
         */
        class CoinNotCollected : public State
        {
            GODOT_CLASS(CoinNotCollected, State)

            private:
                /**
                 * @brief The animated sprite of the Coin.
                 * 
                 */
                AnimatedSprite *animated_sprite;

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
    
}

#endif
