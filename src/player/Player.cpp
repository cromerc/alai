#include "player/Player.h"

#include <Camera2D.hpp>
#include <TileMap.hpp>
#include <VisibilityNotifier2D.hpp>
#include <SceneTree.hpp>
#include <Texture.hpp>

using namespace godot;
using namespace player;

void Player::_register_methods()
{
    register_method("_ready", &Player::_ready);
    register_method("_physics_process", &Player::_physics_process);
    register_method("set_velocity", &Player::set_velocity);
    register_method("get_velocity", &Player::get_velocity);
    //register_property<Player, Ref<SpriteFrames>>("sprite_frames", &Player::set_sprite_frames, &Player::get_sprite_frames, Ref<SpriteFrames>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("SpriteFrames"));
    register_property<Player, float>("speed", &Player::set_speed, &Player::get_speed, player::speed);
    register_property<Player, float>("jump_force", &Player::set_jump_force, &Player::get_jump_force, player::jump_force);
    register_property<Player, float>("gravity", &Player::set_gravity, &Player::get_gravity, player::gravity);
    register_property<Player, float>("run_speed", &Player::set_run_speed, &Player::get_run_speed, player::run_speed);
    register_property<Player, bool>("double_jump", &Player::set_double_jump, &Player::get_double_jump, player::double_jump);
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

void Player::_physics_process(float delta)
{
    velocity.y += get_gravity();

    velocity = move_and_slide(velocity, Vector2::UP, true);
    velocity.x = Math::lerp((float) velocity.x, (float) 0, (float) 0.2);

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
