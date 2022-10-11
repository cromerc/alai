#ifndef ALAI_CAMERA_LIMIT_H
#define ALAI_CAMERA_LIMIT_H

#include <Godot.hpp>
#include <Node2D.hpp>

namespace alai
{
    /**
     * @brief This class limits the camera's position.
     * 
     * @details The camera will be limited based on the used width and height of the Middleground tilemap.
     */
    class CameraLimit : public godot::Node2D
    {
            GODOT_CLASS(CameraLimit, godot::Node2D)

        public:
            /**
             * @brief This method registers classes with Godot.
             * 
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new CameraLimit object.
             * 
             */
            CameraLimit();

            /**
             * @brief Destroy the CameraLimit object.
             * 
             */
            ~CameraLimit();

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
    };
} // namespace alai
#endif
