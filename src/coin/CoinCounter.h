#ifndef ALAI_COIN_COUNTER
#define ALAI_COIN_COUNTER

#include "state_machine/State.h"

#include <Godot.hpp>
#include <Node.hpp>
#include <AnimatedSprite.hpp>

namespace godot
{
        /**
         * @brief This class controls what happens when the Coin is in the collected state.
         * 
         */
        class CoinCounter : public State
        {
            GODOT_CLASS(CoinCounter, State)

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
                 * @brief Construct a new CoinCounter object.
                 * 
                 */
                CoinCounter();

                /**
                 * @brief Destroy the CoinCounter object.
                 * 
                 */
                ~CoinCounter();

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

                void _on_CoinHUD_ready();
                
        };
    
}

#endif
