#include "player/AI.h"

#include <InputEventAction.hpp>

void alai::player::AI::_register_methods()
{
    godot::register_method("_ready", &AI::_ready);
    godot::register_method("_physics_process", &AI::_physics_process);
    godot::register_method("_on_object_report", &AI::_on_object_report);
    godot::register_method("_on_timer_timeout", &AI::_on_timer_timeout);
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

    add_child(timer);
    timer->set_wait_time(1);
    auto err = timer->connect("timeout", this, "_on_timer_timeout");
    if (err != godot::Error::OK)
    {
        godot::Godot::print("Timer could not be connected!");
    }
}

void alai::player::AI::_physics_process(float delta)
{
    auto player_position  = parent->get_global_position();
    auto player_direction = parent->get_velocity();
    bool walking          = false;

    std::sort(entities.begin(), entities.end(), [](const Entity &a, const Entity &b) -> bool
        {
        return a.position.x < b.position.x;
    });

    while (!entities.empty())
    {
        const auto &entity = entities.front();

        auto entityName = entity.name.utf8().get_data();

        double distance = std::abs(player_position.x - entity.position.x);

        int jump_distance = -1;
        auto action       = obelisk->queryAction(entityName, "is", "bouncable");
        if (action == "jump on")
        {
            jump_distance = 100;
        }
        else if (action == "jump over")
        {
            jump_distance = 50;
        }

        if (lastEntity == "")
        {
            if (jump_distance != -1 && distance < jump_distance)
            {
                lastEntity = entity.originalName;
                timer->start();
                if (player_position.x < entity.position.x)
                {
                    auto ev = godot::InputEventAction()._new();
                    ev->set_action("jump");
                    ev->set_pressed(true);
                    _input->parse_input_event(ev);
                }
                else if (player_position.x > entity.position.x)
                {
                    auto ev = godot::InputEventAction()._new();
                    ev->set_action("jump");
                    ev->set_pressed(true);
                    _input->parse_input_event(ev);
                }
            }
        }

        if (obelisk->query(entityName, "is", "gold") > 0 && obelisk->query(std::string("gold ") + entityName, "is", "collectable") > 0)
        {
            if (entity.position.x > player_position.x)
            {
                if (!walking && !_input->is_action_pressed("left") && !_input->is_action_pressed("right"))
                {
                    walking = true;
                    _input->action_press("right");
                }
            }
            else
            {
                if (!walking && !_input->is_action_pressed("left") && !_input->is_action_pressed("right"))
                {
                    walking = true;
                    _input->action_press("left");
                }
            }

            if (distance > -10 && distance < 10 && player_position.y - entity.position.y > 20)
            {
                timer->stop();
                lastEntity = "";
                if (!_input->is_action_pressed("jump"))
                {
                    _input->action_press("jump");
                }
            }
        }

        if (obelisk->query(entityName, "is", "touchable") > 0)
        {
            if (!walking && !_input->is_action_pressed("left") && !_input->is_action_pressed("right"))
            {
                walking = true;
                if (entity.position.x > player_position.x)
                {
                    _input->action_press("right");
                }
                else
                {
                    _input->action_press("left");
                }
            }
        }

        entities.pop_front();
    }
}

void alai::player::AI::unset_action(godot::String action)
{
    auto ev = godot::InputEventAction()._new();
    ev->set_action(action);
    ev->set_pressed(false);
    _input->parse_input_event(ev);
}

void alai::player::AI::_on_timer_timeout()
{
    unset_action("left");
    unset_action("right");
    unset_action("jump");
    lastEntity = "";
}

void alai::player::AI::_on_object_report(godot::String name, godot::String state, godot::Vector2 position, godot::Vector2 velocity)
{
    auto entity         = Entity();
    entity.originalName = name;
    entity.name         = name.to_lower().rstrip("0123456789");
    entity.state        = state;
    entity.position     = position;
    entity.velocity     = velocity;
    entities.emplace_front(entity);
}
