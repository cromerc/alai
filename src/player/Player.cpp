#include "player/Player.h"

#include "Event.h"

#include <Camera2D.hpp>
#include <KinematicCollision2D.hpp>
#include <RayCast2D.hpp>
#include <SceneTree.hpp>
#include <Texture.hpp>
#include <TileMap.hpp>
#include <Viewport.hpp>
#include <VisibilityNotifier2D.hpp>

void alai::player::Player::_register_methods()
{
    godot::register_method("_ready", &Player::_ready);
    godot::register_method("_physics_process", &Player::_physics_process);
    godot::register_method("set_velocity", &Player::set_velocity);
    godot::register_method("get_velocity", &Player::get_velocity);
    godot::register_method("_on_player_touched", &Player::_on_player_touched);
    godot::register_method("_on_monitor_loaded", &Player::_on_monitor_loaded);
    //godot::register_property<Player, godot::Ref<godot::SpriteFrames>>("sprite_frames", &Player::set_sprite_frames, &Player::get_sprite_frames, godot::Ref<godot::SpriteFrames>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, godot::String("SpriteFrames"));
    godot::register_property<Player, float>("speed", &Player::set_speed, &Player::get_speed, player::speed);
    godot::register_property<Player, float>("jump_force", &Player::set_jump_force, &Player::get_jump_force, player::jump_force);
    godot::register_property<Player, float>("bounce_force", &Player::set_bounce_force, &Player::get_bounce_force, player::bounce_force);
    godot::register_property<Player, float>("gravity", &Player::set_gravity, &Player::get_gravity, player::gravity);
    godot::register_property<Player, float>("run_speed", &Player::set_run_speed, &Player::get_run_speed, player::run_speed);
    godot::register_property<Player, bool>("double_jump", &Player::set_double_jump, &Player::get_double_jump, player::double_jump);
}

alai::player::Player::Player()
{
}

alai::player::Player::~Player()
{
}

void alai::player::Player::_init()
{
    _resource_loader = godot::ResourceLoader::get_singleton();

    //sprite_frames = _resource_loader->load(player::sprite_frames);
    set_speed(player::speed);
    set_jump_force(player::jump_force);
    set_bounce_force(player::bounce_force);
    set_gravity(player::gravity);
    set_run_speed(player::run_speed);
    set_double_jump(player::double_jump);

    coins = 0;

    velocity = godot::Vector2();
}

void alai::player::Player::_ready()
{
    animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
    if (!animated_sprite)
    {
        ERR_PRINT("AnimateSprite not found!");
        animated_sprite = godot::AnimatedSprite()._new();
    }
    //animated_sprite->set_sprite_frames(sprite_frames);

    auto node = get_parent()->find_node("Middleground");
    if (node != nullptr)
    {
        auto tile_map = Object::cast_to<godot::TileMap>(node);
        get_parent()->call_deferred("remove_child", this);
        tile_map->call_deferred("add_child", this);
    }
    else
    {
        WARN_PRINT("Middleground not found!");
    }
}

void alai::player::Player::_on_monitor_loaded() {
    auto state = get_node("StateMachine")->get_child(0);
    if (state != nullptr)
    {
        auto event = get_node<alai::Event>("/root/Event");
        event->emit_signal("object_created", this->get_name(), state->get_name(), get_global_position(), velocity);
    }
    else
    {
        WARN_PRINT("State not found!");
    }
}

void alai::player::Player::_physics_process(float delta)
{
    velocity.y += get_gravity();

    auto snap_vector = godot::Vector2::ZERO;
    if (!is_on_floor())
    {
        snap_vector = godot::Vector2::DOWN * 20.0;
    }

    auto platform_detector = get_node<godot::RayCast2D>("PlatformDetector");
    auto is_on_platform = platform_detector->is_colliding();

    velocity = move_and_slide_with_snap(velocity, snap_vector, godot::Vector2::UP, !is_on_platform, 4, 0.9, false);
    //velocity = move_and_slide(velocity, Vector2::UP, !is_on_platform);
    velocity.x = godot::Math::lerp((float) velocity.x, (float) 0, (float) 0.2);

    auto count = get_slide_count();
    for (int64_t i = 0; i < count; i++)
    {
        auto collision = get_slide_collision(i);
        auto collision_object = collision->get_collider();
        auto collider = Object::cast_to<Node>(collision_object);
        if (collider->is_in_group("squashable") && godot::Vector2::UP.dot(collision->get_normal()) > 0.1)
        {
            collider->call_deferred("squash");
            /*auto dup_node = collider->duplicate();
            auto dup = Object::cast_to<KinematicBody2D>(dup_node);
            auto dup_pos = dup->get_position();
            dup_pos.x += 24;
            dup->set_position(dup_pos);
            auto enemies = get_tree()->get_root()->get_node("Main")->find_node("Enemies", true, false);
            if (enemies != nullptr) {
                enemies->add_child(dup);
            }
            else
            {
                WARN_PRINT("Enemies not found!");
                dup->queue_free();
            }*/
            velocity.y = -get_bounce_force();
        }
        else if (collider->is_in_group("enemy") && (collider->is_in_group("rideable") && godot::Vector2::DOWN.dot(collision->get_normal()) > 0))
        {
            _on_player_touched();
        }
        else if (collider->is_in_group("enemy") && !collider->is_in_group("rideable"))
        {
            _on_player_touched();
        }
    }

    // Clamp the player's position inside the camera's limits
    auto camera = get_node<godot::Camera2D>("Camera2D");
    auto position = get_global_position();
    auto sprite_node = get_node<godot::AnimatedSprite>("AnimatedSprite");
    if (sprite_node != nullptr)
    {
        position.x = godot::Math::clamp((float) position.x, (float) camera->get_limit(0), (float) camera->get_limit(2) - sprite_node->get_sprite_frames()->get_frame("idle", 0)->get_size().x);
        position.y = godot::Math::clamp((float) position.y, (float) camera->get_limit(1), (float) camera->get_limit(3) + sprite_node->get_sprite_frames()->get_frame("idle", 0)->get_size().y);
    }
    else {
        WARN_PRINT("Could not clamp player based on sprite frame size!");
        position.x = godot::Math::clamp((float) position.x, (float) camera->get_limit(0), (float) camera->get_limit(2));
        position.y = godot::Math::clamp((float) position.y, (float) camera->get_limit(1), (float) camera->get_limit(3));
    }
    set_global_position(position);

    // If the player is off screen reload the scene
    auto notifier = get_node<godot::VisibilityNotifier2D>("Camera2D/VisibilityNotifier2D");
    if (notifier != nullptr)
    {
        if (!notifier->is_on_screen())
        {
            auto event = get_node<alai::Event>("/root/Event");
            event->emit_signal("player_died");
            /*if (get_parent()->get_class() == "TileMap")
            {
                auto error = get_tree()->change_scene("res://Main.tscn");
                if (error != godot::Error::OK)
                {
                    ERR_PRINT(godot::String().num((int) error) + " Could not load scene!");
                }
            }*/
        }
    }

    auto state = get_node("StateMachine")->get_child(0);
    if (state != nullptr)
    {
        auto event = get_node<alai::Event>("/root/Event");
        event->emit_signal("object_updated", this->get_name(), state->get_name(), get_global_position(), velocity);
    }
    else
    {
        WARN_PRINT("State not found!");
    }
}

void alai::player::Player::set_sprite_frames(godot::Ref<godot::SpriteFrames> sprite_frames)
{
    this->sprite_frames = sprite_frames;
}

godot::Ref<godot::SpriteFrames> alai::player::Player::get_sprite_frames()
{
    return this->sprite_frames;
}

void alai::player::Player::set_speed(float speed)
{
    this->speed = speed;
}

float alai::player::Player::get_speed()
{
    return this->speed;
}

void alai::player::Player::set_jump_force(float jump_force)
{
    this->jump_force = jump_force;
}

float alai::player::Player::get_jump_force()
{
    return this->jump_force;
}

void alai::player::Player::set_bounce_force(float bounce_force)
{
    this->bounce_force = bounce_force;
}

float alai::player::Player::get_bounce_force()
{
    return this->bounce_force;
}

void alai::player::Player::set_gravity(float gravity)
{
    this->gravity = gravity;
}

float alai::player::Player::get_gravity()
{
    return this->gravity;
}

void alai::player::Player::set_run_speed(float run_speed)
{
    this->run_speed = run_speed;
}

float alai::player::Player::get_run_speed()
{
    return this->run_speed;
}

void alai::player::Player::set_double_jump(bool double_jump)
{
    this->double_jump = double_jump;
}

bool alai::player::Player::get_double_jump()
{
    return this->double_jump;
}

void alai::player::Player::set_velocity(godot::Vector2 velocity)
{
    this->velocity = velocity;
}

godot::Vector2 alai::player::Player::get_velocity()
{
    return this->velocity;
}

void alai::player::Player::_on_player_touched()
{
    auto error = get_tree()->change_scene("res://Main.tscn");
    if (error != godot::Error::OK)
    {
        ERR_PRINT(godot::String().num((int) error) + " Could not load scene!");
    }
}
