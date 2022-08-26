#ifndef ALAI_GAME_OVER_SCREEN
#define ALAI_GAME_OVER_SCREEN


#include <Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>

namespace godot
{
	/**
	 * @brief This class controls what happens when the Coin is in the collected .
	 * 
	 */
	class GameOverScreen : public Control
	{
		GODOT_CLASS(GameOverScreen, Control)

		private:

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
		void _on_restart_button_pressed();
	};
}

#endif
