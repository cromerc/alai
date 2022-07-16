#ifndef ALAI_COIN_COUNTER
#define ALAI_COIN_COUNTER


#include <Godot.hpp>
#include <Node.hpp>
#include <Label.hpp>

namespace godot
{
        /**
         * @brief This class controls what happens when the Coin is in the collected .
         * 
         */
        class CoinCounter : public Label
        {
            GODOT_CLASS(CoinCounter, Label)

            private:
                int coins = 0;


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
                 * @brief Called when the collected  of the coin is entered.
                 * 
                 */

                void _on_CoinHUD_ready();
                void _on_coin_collected(int amount);
                void _ready();
                
        };
    
}

#endif
