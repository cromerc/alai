#ifndef ALAI_GAME_OVER_GAME_OVER_SCREEN_H
#define ALAI_GAME_OVER_GAME_OVER_SCREEN_H

#include <CanvasLayer.hpp>
#include <Godot.hpp>
#include <ResourceLoader.hpp>

namespace alai
{
    /**
     * @brief This class controls what happens when the Coin is in the collected .
     * 
     */
    class GameOverScreen : public godot::CanvasLayer
    {
        GODOT_CLASS(GameOverScreen, godot::CanvasLayer)

        private:
            godot::ResourceLoader *_resource_loader;

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new GameOverScreen object.
             * 
             */
            GameOverScreen();

            /**
             * @brief Destroy the GameOverScreen object.
             * 
             */
            ~GameOverScreen();

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
            void _ready();
            void _on_player_died();
            void _on_restart_button_pressed();
            void restart_game();
            void connect_signal();
    };
}

#endif
