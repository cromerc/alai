#ifndef ALAI_EVENT_H
#define ALAI_EVENT_H

#include <Godot.hpp>
#include <Node.hpp>

namespace alai
{
    /**
     * @brief This class provides an event bus for the project.
     * 
     * @details This class should be an auto-loaded singleton for the project.
     * To use this use Event.connect() and Event.emit_signal() to have global signals.
     */
    class Event : public godot::Node
    {
        GODOT_CLASS(Event, godot::Node)
        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new Event object.
             * 
             */
            Event();

            /**
             * @brief Destroy the Event object.
             * 
             */
            ~Event();

            /**
             * @brief Initialize the class from Godot.
             * 
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();
    };
}

#endif
