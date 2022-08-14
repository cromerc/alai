#include "player/Player.h"

#include <Camera2D.hpp>
#include <TileMap.hpp>
#include <VisibilityNotifier2D.hpp>
#include <SceneTree.hpp>
#include <Texture.hpp>
#include <Viewport.hpp>
#include <RayCast2D.hpp>
#include <KinematicCollision2D.hpp>

using namespace godot;
using namespace player;

void Player::_register_methods()
{
    register_method("_ready", &Player::_ready);
    register_method("_physics_process", &Player::_physics_process);
    register_method("set_velocity", &Player::set_velocity);
    register_method("get_velocity", &Player::get_velocity);
    register_method("_on_player_touched", &Player::_on_player_touched);
    register_method("_on_monitor_loaded", &Player::_on_monitor_loaded);
    //register_property<Player, Ref<SpriteFrames>>("sprite_frames", &Player::set_sprite_frames, &Player::get_sprite_frames, Ref<SpriteFrames>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("SpriteFrames"));
    register_property<Player, float>("speed", &Player::set_speed, &Player::get_speed, player::speed);
    register_property<Player, float>("jump_force", &Player::set_jump_force, &Player::get_jump_force, player::jump_force);
    register_property<Player, float>("bounce_force", &Player::set_bounce_force, &Player::get_bounce_force, player::bounce_force);
    register_property<Player, float>("gravity", &Player::set_gravity, &Player::get_gravity, player::gravity);
    register_property<Player, float>("run_speed", &Player::set_run_speed, &Player::get_run_speed, player::run_speed);
    register_property<Player, bool>("double_jump", &Player::set_double_jump, &Player::get_double_jump, player::double_jump);
    register_signal<Player>("object_created", "name", GODOT_VARIANT_TYPE_STRING, "state", GODOT_VARIANT_TYPE_STRING, "position", GODOT_VARIANT_TYPE_VECTOR2, "velocity", GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<Player>("object_updated", "name", GODOT_VARIANT_TYPE_STRING, "state", GODOT_VARIANT_TYPE_STRING, "position", GODOT_VARIANT_TYPE_VECTOR2, "velocity", GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<Player>("object_removed", "name", GODOT_VARIANT_TYPE_STRING);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::_init()
{
    _resource_loader = ResourceLoader::get_singleton();

    //sprite_frames = _resource_loader->load(player::sprite_frames);
    set_speed(player::speed);
    set_jump_force(player::jump_force);
    set_bounce_force(player::bounce_force);
    set_gravity(player::gravity);
    set_run_speed(player::run_speed);
    set_double_jump(player::double_jump);

    coins = 0;

    velocity = Vector2();
}

void Player::_ready()
{
    animated_sprite = get_node<AnimatedSprite>("AnimatedSprite");
    if (!animated_sprite)
    {
        ERR_PRINT("AnimateSprite not found!");
        animated_sprite = AnimatedSprite()._new();
    }
    //animated_sprite->set_sprite_frames(sprite_frames);

    auto node = get_parent()->find_node("Middleground");
    if (node != nullptr)
    {
        auto tile_map = Object::cast_to<TileMap>(node);
        get_parent()->call_deferred("remove_child", this);
        tile_map->call_deferred("add_child", this);
    }
    else
    {
        WARN_PRINT("Middleground not found!");
    }
}

void Player::_on_monitor_loaded() {
    auto object_node = get_tree()->get_root()->get_node("Main")->find_node("Monitor", true);
    if (object_node != nullptr)
    {
        auto state = get_node("StateMachine")->get_child(0);
        if (state != nullptr)
        {
            connect("object_created", object_node, "_object_created");
            connect("object_updated", object_node, "_object_updated");
            connect("object_removed", object_node, "_object_removed");
            emit_signal("object_created", this->get_name(), state->get_name(), get_global_position(), velocity);
        }
        else
        {
            WARN_PRINT("State not found!");
        }
    }
    else
    {
        WARN_PRINT("Monitor not found!");
    }
}

void Player::_physics_process(float delta)
{
    velocity.y += get_gravity();

    auto snap_vector = Vector2::ZERO;
    if (!is_on_floor())
    {
        snap_vector = Vector2::DOWN * 20.0;
    }

    auto platform_detector = get_node<RayCast2D>("PlatformDetector");
    auto is_on_platform = platform_detector->is_colliding();

    velocity = move_and_slide_with_snap(velocity, snap_vector, Vector2::UP, !is_on_platform, 4, 0.9, false);
    //velocity = move_and_slide(velocity, Vector2::UP, !is_on_platform);
    velocity.x = Math::lerp((float) velocity.x, (float) 0, (float) 0.2);

    auto count = get_slide_count();
    for (int64_t i = 0; i < count; i++)
    {
        auto collision = get_slide_collision(i);
        auto collision_object = collision->get_collider();
        auto collider = Object::cast_to<Node>(collision_object);
        if (collider->is_in_group("squashable") && Vector2::UP.dot(collision->get_normal()) > 0.1)
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
        else if (collider->is_in_group("enemy") && (collider->is_in_group("rideable") && Vector2::DOWN.dot(collision->get_normal()) > 0))
        {
            _on_player_touched();
        }
        else if (collider->is_in_group("enemy") && !collider->is_in_group("rideable"))
        {
            _on_player_touched();
        }
    }

    // Clamp the player's position inside the camera's limits
    auto camera = get_node<Camera2D>("Camera2D");
    auto position = get_global_position();
    auto sprite_node = get_node<AnimatedSprite>("AnimatedSprite");
    if (sprite_node != nullptr)
    {
        position.x = Math::clamp((float) position.x, (float) camera->get_limit(0), (float) camera->get_limit(2) - sprite_node->get_sprite_frames()->get_frame("idle", 0)->get_size().x);
        position.y = Math::clamp((float) position.y, (float) camera->get_limit(1), (float) camera->get_limit(3) + sprite_node->get_sprite_frames()->get_frame("idle", 0)->get_size().y);
    }
    else {
        WARN_PRINT("Could not clamp player based on sprite frame size!");
        position.x = Math::clamp((float) position.x, (float) camera->get_limit(0), (float) camera->get_limit(2));
        position.y = Math::clamp((float) position.y, (float) camera->get_limit(1), (float) camera->get_limit(3));
    }
    set_global_position(position);

    // If the player is off screen reload the scene
    auto notifier = get_node<VisibilityNotifier2D>("Camera2D/VisibilityNotifier2D");
    if (notifier != nullptr)
    {
        if (!notifier->is_on_screen())
        {
            if (get_parent()->get_class() == "TileMap")
            {
                auto error = get_tree()->change_scene("res://Main.tscn");
                if (error != Error::OK)
                {
                    ERR_PRINT(String().num((int) error) + " Could not load scene!");
                }
            }
        }
    }

    auto state = get_node("StateMachine")->get_child(0);
    if (state != nullptr)
    {
        emit_signal("object_updated", this->get_name(), state->get_name(), get_global_position(), velocity);
    }
    else
    {
        WARN_PRINT("State not found!");
    }
}

void Player::set_sprite_frames(Ref<SpriteFrames> sprite_frames)
{
    this->sprite_frames = sprite_frames;
}

Ref<SpriteFrames> Player::get_sprite_frames()
{
    return this->sprite_frames;
}

void Player::set_speed(float speed)
{
    this->speed = speed;
}

float Player::get_speed()
{
    return this->speed;
}

void Player::set_jump_force(float jump_force)
{
    this->jump_force = jump_force;
}

float Player::get_jump_force()
{
    return this->jump_force;
}

void Player::set_bounce_force(float bounce_force)
{
    this->bounce_force = bounce_force;
}

float Player::get_bounce_force()
{
    return this->bounce_force;
}

void Player::set_gravity(float gravity)
{
    this->gravity = gravity;
}

float Player::get_gravity()
{
    return this->gravity;
}

void Player::set_run_speed(float run_speed)
{
    this->run_speed = run_speed;
}

float Player::get_run_speed()
{
    return this->run_speed;
}

void Player::set_double_jump(bool double_jump)
{
    this->double_jump = double_jump;
}

bool Player::get_double_jump()
{
    return this->double_jump;
}

void Player::set_velocity(Vector2 velocity)
{
    this->velocity = velocity;
}

Vector2 Player::get_velocity()
{
    return this->velocity;
}

void Player::_on_player_touched()
{
    auto error = get_tree()->change_scene("res://Main.tscn");
    if (error != Error::OK)
    {
        ERR_PRINT(String().num((int) error) + " Could not load scene!");
    }
}
