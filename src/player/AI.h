#ifndef ALAI_PLAYER_AI_H
#define ALAI_PLAYER_AI_H

#include "Event.h"
#include "obelisk.h"
#include "player/Player.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <Node.hpp>
#include <Vector2.hpp>
#include <queue>

namespace alai
{
    namespace player
    {
        class Entity
        {
            public:
                godot::String name;
                godot::String state;
                godot::Vector2 position;
                godot::Vector2 velocity;
        };

        class AI : public godot::Node
        {
                GODOT_CLASS(AI, godot::Node)

            private:
                /**
                 * @brief Input singleton.
                 *
                 */
                godot::Input* _input;

                /**
                 * @brief The obelisk object.
                 *
                 */
                std::unique_ptr<obelisk::Obelisk> obelisk;

                alai::Event* event;

                std::queue<alai::player::Entity> entities;

                alai::player::Player* parent;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 *
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void
                    _register_methods();

                AI();
                ~AI();

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
                 * @brief The physics processed every delta time.
                 *
                 * @param[in] delta The time since the method was last run.
                 */
                void _physics_process(float delta);

                void _on_object_report(godot::String name, godot::String state, godot::Vector2 position, godot::Vector2 velocity);
        };
    } // namespace player
} // namespace alai

#endif
