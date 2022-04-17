#ifndef ALAI_MAIN_H
#define ALAI_MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <OS.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <Ref.hpp>

/**
 * @brief This is the godot namespace for all the code included in the library.
 * 
 * @details This namespace is used a prefix when the Godot engine looks for classes, methods, and properties.
 */
namespace godot
{
    /**
     * @brief This namespace houses some global variables and the main class.
     * 
     */
    namespace main
    {
        /**
         * @brief The default value for if the game should start in full screen.
         * 
         */
        const bool full_screen = false;
        /**
         * @brief The default resolution for the game window.
         * 
         */
        const Vector2 window_size = Vector2(1280, 720);
        /**
         * @brief The default screen the the game should open on.
         * 
         * @details -1 opens it on the currently active screen. And 0 and above are the screens to use.
         */
        const int8_t launch_screen = -1;

        /**
         * @brief This class controls the Main node.
         * 
         * @details The main node is responsible for controling the window and the game iteself is a child of it.
         */
        class Main : public Node
        {
            GODOT_CLASS(Main, Node)

            private:
                /**
                 * @brief OS singleton.
                 * 
                 */
                OS *_os;
                /**
                 * @brief Input singleton.
                 * 
                 */
                Input *_input;

                /**
                 * @brief The first level to load
                 * 
                 */
                Ref<PackedScene> level;
                /**
                 * @brief If the window is full screen or not.
                 * 
                 */
                bool full_screen;
                /**
                 * @brief The size of the window.
                 * 
                 */
                Vector2 window_size;
                /**
                 * @brief The screen to launch the game on.
                 * 
                 */
                int8_t launch_screen;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * 
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new Main object.
                 * 
                 */
                Main();

                /**
                 * @brief Destroy the Main object.
                 * 
                 */
                ~Main();

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
                 * @brief This class handles the physics processing.
                 * 
                 * @details Every delta time, this function is called to check for input and update positioning.
                 * 
                 * @param[in] delta The difference in time that passed since the last call to this method.
                 */
                void _physics_process(float delta);

                /**
                 * @brief Set the level object.
                 * 
                 * @param[in] level The new level to load when starting.
                 */
                void set_level(Ref<PackedScene> level);

                /**
                 * @brief Get the level object.
                 * 
                 * @return Ref<PackedScene> The level scene to load.
                 */
                Ref<PackedScene> get_level();

                /**
                 * @brief Set the full screen object.
                 * 
                 * @param[in] full_screen The new full screen state.
                 */
                void set_full_screen(bool full_screen);

                /**
                 * @brief Get the full screen object.
                 * 
                 * @return true If full screen.
                 * @return false If not full screen.
                 */
                bool get_full_screen();

                /**
                 * @brief Set the window size object.
                 * 
                 * @param[in] window_size The new window size.
                 */
                void set_window_size(Vector2 window_size);

                /**
                 * @brief Get the window size object.
                 * 
                 * @return Vector2 The window size.
                 */
                Vector2 get_window_size();

                /**
                 * @brief Set the launch screen object.
                 * 
                 * @param[in] launch_screen The launch screen to use.
                 */
                void set_launch_screen(int8_t launch_screen);

                /**
                 * @brief Get the launch screen object.
                 * 
                 * @return int8_t The launch screen.
                 */
                int8_t get_launch_screen();
        };
    }
}

#endif
