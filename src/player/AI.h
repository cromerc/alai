#ifndef ALAI_PLAYER_AI_H
#define ALAI_PLAYER_AI_H

#include "Event.h"
#include "obelisk.h"
#include "player/Player.h"

#include <Godot.hpp>
#include <Input.hpp>
#include <Node.hpp>
#include <Timer.hpp>
#include <Vector2.hpp>
#include <queue>

namespace alai
{
    namespace player
    {
        class Entity
        {
            public:
                godot::String originalName;
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

                std::deque<alai::player::Entity> entities;

                alai::player::Player* parent;

                godot::String lastEntity;

                godot::Timer* timer = godot::Timer()._new();

            public:
                /**
                 * @brief This method registers classes with Godot.
                 *
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void
                    _register_methods();

                /**
                 * @brief Construct a new AI object.
                 *
                 */
                AI();

                /**
                 * @brief Destroy the AI object.
                 *
                 */
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

                void _on_timer_timeout();

                void unset_action(godot::String action);

                /**
                 * @brief Callback that receives information about the game environment.
                 *
                 * @param[in] name The name of the object.
                 * @param[in] state The state the object is in.
                 * @param[in] position The position of the object.
                 * @param[in] velocity The object's velocity.
                 */
                void _on_object_report(godot::String name, godot::String state, godot::Vector2 position, godot::Vector2 velocity);
        };
    } // namespace player
} // namespace alai

#endif
