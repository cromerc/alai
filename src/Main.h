#ifndef ALAI_MAIN_H
#define ALAI_MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <OS.hpp>
#include <Input.hpp>

/**
 * @brief This is the godot namespace for all the code included in the library.
 * @details This namespace is used a prefix when the Godot engine looks for classes, methods, and properties.
 */
namespace godot
{
    namespace main
    {
        const bool full_screen = false;
        const Vector2 window_size = Vector2(1280, 720);
        const int8_t launch_screen = -1;

        /**
         * @brief This class controls the Main node.
         * @details The main node is responsible for controling the window and the game iteself is a child of it.
         */
        class Main : public Node
        {
            GODOT_CLASS(Main, Node)

            private:
                /**
                 * @brief OS singleton.
                 */
                OS *_os;
                /**
                 * @brief Input singleton.
                 */
                Input *_input;

                /**
                 * @brief If the window is full screen or not.
                 */
                bool full_screen;
                /**
                 * @brief The size of the window.
                 */
                Vector2 window_size;
                /**
                 * @brief The screen to launch the game on.
                 */
                int8_t launch_screen;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new Main object.
                 */
                Main();

                /**
                 * @brief Destroy the Main object.
                 */
                ~Main();

                /**
                 * @brief Initialize the class from Godot.
                 * @details This method is called just once when the Godot engine connects to the instance of the class.
                 */
                void _init();

                /**
                 * @brief Code to be run when ready.
                 * @details This method is run when all the children of this node are ready.
                 */
                void _ready();

                /**
                 * @brief This class handles the physics processing.
                 * @details Every delta time, this function is called to check for input and update positioning.
                 * 
                 * @param[in] delta The difference in time that passed since the last call to this method.
                 */
                void _physics_process(float delta);

                /**
                 * @brief Set the full screen object.
                 * 
                 * @param[in] new_full_screen The new full screen state.
                 */
                void set_full_screen(bool new_full_screen);

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
                 * @param[in] new_window_size The new window size.
                 */
                void set_window_size(Vector2 new_window_size);

                /**
                 * @brief Get the window size object.
                 * 
                 * @return Vector2 The window size.
                 */
                Vector2 get_window_size();

                /**
                 * @brief Set the launch screen object.
                 * 
                 * @param[in] new_launch_screen The launch screen to use.
                 */
                void set_launch_screen(int8_t new_launch_screen);

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
