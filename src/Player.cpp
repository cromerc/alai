#include "Player.h"

#include <Camera2D.hpp>
#include <TileMap.hpp>
#include <VisibilityNotifier2D.hpp>
#include <SceneTree.hpp>
#include <Texture.hpp>

using namespace godot;

void Player::_register_methods()
{
    register_method("_ready", &Player::_ready);
    register_method("_physics_process", &Player::_physics_process);
    register_method("_on_Player_player_moved", &Player::_on_Player_player_moved);
    //register_property<Player, Ref<SpriteFrames>>("sprite_frames", &Player::set_sprite_frames, &Player::get_sprite_frames, Ref<SpriteFrames>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("SpriteFrames"));
    register_property<Player, float>("speed", &Player::set_speed, &Player::get_speed, ALAI_PLAYER_SPEED);
    register_property<Player, float>("jump_force", &Player::set_jump_force, &Player::get_jump_force, ALAI_PLAYER_JUMP_FORCE);
    register_property<Player, float>("gravity", &Player::set_gravity, &Player::get_gravity, ALAI_PLAYER_GRAVITY);
    register_property<Player, float>("run_speed", &Player::set_run_speed, &Player::get_run_speed, ALAI_PLAYER_RUN_SPEED);
    register_signal<Player>("player_moved", "position", GODOT_VARIANT_TYPE_VECTOR2);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::_init()
{
    _os = OS::get_singleton();
    _input = Input::get_singleton();
    _resource_loader = ResourceLoader::get_singleton();

    //sprite_frames = _resource_loader->load(ALAI_PLAYER_SPRITE_FRAMES);
    set_speed(ALAI_PLAYER_SPEED);
    set_jump_force(ALAI_PLAYER_JUMP_FORCE);
    set_gravity(ALAI_PLAYER_GRAVITY);
    set_run_speed(ALAI_PLAYER_RUN_SPEED);

    coins = 0;

    velocity = Vector2();

    jumping = 0;
}

void Player::_ready()
{
    animated_sprite = get_node<AnimatedSprite>("AnimatedSprite");
    if (!animated_sprite)
    {
        WARN_PRINT("AnimateSprite not found!");
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
    auto current_speed = get_speed();
    velocity.x = 0;
    if (_input->is_action_pressed("run"))
    {
        current_speed *= get_run_speed();
    }

    if (_input->is_action_pressed("right"))
    {
        velocity.x += current_speed;
    }

    if (_input->is_action_pressed("left"))
    {
        velocity.x += -current_speed;
    }

    if (velocity.x > 0)
    {
        animated_sprite->play("move");
        animated_sprite->set_flip_h(true);
    }
    else if (velocity.x < 0)
    {
        animated_sprite->play("move");
        animated_sprite->set_flip_h(false);
    }
    else
    {
        animated_sprite->stop();
        animated_sprite->set_animation("idle");
    }

    if (jumping > 0 && is_on_floor())
    {
        animated_sprite->set_frame(1);
        jumping = 0;
    }

    if (!is_on_floor())
    {
        animated_sprite->stop();
        animated_sprite->set_animation("air");
        if (jumping == 0)
        {
            jumping = 2;
        }
    }

    velocity.y += get_gravity();
    if (_input->is_action_just_pressed("jump") && jumping < 2)
    {
        velocity.y = -get_jump_force();
        jumping++;
    }

    if (_input->is_action_just_released("jump"))
    {
        if (velocity.y < -100)
        {
            velocity.y = -100;
        }
    }

    if (velocity.x < 0 || velocity.x > 0)
    {
        //emit_signal("player_moved", get_position());
    }

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
                Godot::print("Off screen");
                auto error = get_tree()->change_scene("res://Main.tscn");
                if (error != Error::OK)
                {
                    ERR_PRINT(String().num((int) error) + " Could not load scene!");
                }
            }
        }
    }
}

void Player::set_sprite_frames(Ref<SpriteFrames> new_sprite_frames)
{
    sprite_frames = new_sprite_frames;
}

Ref<SpriteFrames> Player::get_sprite_frames()
{
    return sprite_frames;
}

void Player::set_speed(float new_speed)
{
    speed = new_speed;
}

float Player::get_speed()
{
    return speed;
}

void Player::set_jump_force(float new_jump_force)
{
    jump_force = new_jump_force;
}

float Player::get_jump_force()
{
    return jump_force;
}

void Player::set_gravity(float new_gravity)
{
    gravity = new_gravity;
}

float Player::get_gravity()
{
    return gravity;
}

void Player::set_run_speed(float new_run_speed)
{
    run_speed = new_run_speed;
}

float Player::get_run_speed()
{
    return run_speed;
}

void Player::_on_Player_player_moved(Vector2 position)
{
    Godot::print(position);
}
