#ifndef ALAI_GAME_WON_GAME_WON_SCREEN_H
#define ALAI_GAME_WON_GAME_WON_SCREEN_H

#include <CanvasLayer.hpp>
#include <Godot.hpp>

namespace alai
{
    /**
     * @brief This class controls what happens when the game is won.
     * 
     */
    class GameWonScreen : public godot::CanvasLayer
    {
        GODOT_CLASS(GameWonScreen, godot::CanvasLayer)

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new GameWonScreen object.
             * 
             */
            GameWonScreen();

            /**
             * @brief Destroy the GameWonScreen object.
             * 
             */
            ~GameWonScreen();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            void _ready();
            void _on_player_won();
            void _on_quit_button_pressed();
            void connect_signal();
    };
}

#endif
