#include "player/AI.h"

void alai::player::AI::_register_methods()
{
    godot::register_method("_ready", &AI::_ready);
    godot::register_method("_physics_process", &AI::_physics_process);
    godot::register_method("_on_object_report", &AI::_on_object_report);
}

alai::player::AI::AI()
{
}

alai::player::AI::~AI()
{
}

void alai::player::AI::_init()
{
    _input  = godot::Input::get_singleton();
    obelisk = std::unique_ptr<obelisk::Obelisk> {new obelisk::Obelisk("alai.kb")};
}

void alai::player::AI::_ready()
{
    parent = Object::cast_to<Player>(get_parent());

    event = get_node<alai::Event>("/root/Event");
    event->connect("report_object", this, "_on_object_report");
}

void alai::player::AI::_physics_process(float delta)
{
    while (!entities.empty())
    {
        const auto& entity = entities.front();

        if (obelisk->query(entity.name.utf8().get_data(), "is", "touchable") > 0)
        {
            auto player_position = parent->get_global_position();
            if (entity.position.x > player_position.x)
            {
                _input->action_press("right");
            }
            else
            {
                _input->action_press("left");
            }
        }

        if (obelisk->query(entity.name.utf8().get_data(), "is", "bouncable") > 0)
        {
            auto player_position = parent->get_global_position();
            auto distance        = sqrt(pow(player_position.x - entity.position.x, 2) + pow(player_position.y - entity.position.y, 2));
            int jump_distance    = 0;

            auto player_direction = parent->get_velocity();

            auto action = obelisk->queryAction(entity.name.utf8().get_data(), "is", "bouncable");
            if (action == "jump on")
            {
                jump_distance = 100;
            }
            else if (action == "jump over")
            {
                jump_distance = 50;
            }

            if (distance < jump_distance)
            {
                if (_input->is_action_pressed("right") && player_position.x < entity.position.x)
                {
                    _input->action_press("jump");
                }
                else if (_input->is_action_pressed("left") && player_position.x > entity.position.x)
                {
                    _input->action_press("jump");
                }
            }
        }

        if (obelisk->query(entity.name.utf8().get_data(), "is", "gold") > 0 && obelisk->query(std::string("gold ") + entity.name.utf8().get_data(), "is", "collectable") > 0)
        {
            auto player_position = parent->get_global_position();
            float distance       = player_position.x - entity.position.x;
            if (distance > -10 && distance < 10 && player_position.y - entity.position.y > 20)
            {
                _input->action_press("jump");
            }
        }

        entities.pop();
    }
}

void alai::player::AI::_on_object_report(godot::String name, godot::String state, godot::Vector2 position, godot::Vector2 velocity)
{
    auto entity     = Entity();
    entity.name     = name.to_lower().rstrip("0123456789");
    entity.state    = state;
    entity.position = position;
    entity.velocity = velocity;
    entities.push(entity);
}
