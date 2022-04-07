#ifndef JUEGO_PLAYER_H
#define JUEGO_PLAYER_H

/**
 * @brief This resource is loaded by default for the AnimatedSprite node.
 */
#define JUEGO_PLAYER_SPRITE_FRAMES "res://characters/player/sprites/green.tres"
/**
 * @brief The speed the player should move it.
 */
#define JUEGO_PLAYER_SPEED 60.0
/**
 * @brief The force applied to the player when jumping.
 */
#define JUEGO_PLAYER_JUMP_FORCE 300.0
/**
 * @brief The gravity applied to the player.
 */
#define JUEGO_PLAYER_GRAVITY 9.81
/**
 * @brief The multiplier used to change the speed of the player when running.
 */
#define JUEGO_PLAYER_RUN_SPEED 2.0

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <OS.hpp>
#include <Sprite.hpp>
#include <Vector2.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>
#include <SpriteFrames.hpp>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>

/**
 * @brief This is the godot namespace for all the code included in the library.
 * @details This namespace is used a prefix when the Godot engine looks for classes, methods, and properties.
 */
namespace godot
{
    /**
     * @brief This class is used to control the player.
     * @details This class allows the player to move, run, and jump as well as controls the sprite displayed for those actions.
     */
    class Player : public KinematicBody2D
    {
        GODOT_CLASS(Player, KinematicBody2D)

        private:
            /**
             * @brief OS singleton.
             */
            OS *_os;
            /**
             * @brief Input singleton.
             */
            Input *_input;
            /**
             * @brief ResourceLoader singleton.
             */
            ResourceLoader *_resource_loader;

            /**
             * @brief The animated sprite connected to the KinematicBody2D.
             */
            AnimatedSprite *animated_sprite;
            /**
             * @brief The sprite frames used in the animated sprite.
             */
            Ref<SpriteFrames> sprite_frames;
            /**
             * @brief The coins the player has collected.
             */
            uint8_t coins;
            /**
             * @brief The velocity at which moves the player moves.
             */
            Vector2 velocity;
            /**
             * @brief The speed that the player moves in.
             */
            float speed;
            /**
             * @brief The force applied to the player when jumping.
             */
            float jump_force;
            /**
             * @brief The gravity applied to the player.
             */
            float gravity;
            /**
             * @brief The speed multiplier used to make the player move faster.
             */
            float run_speed;

            /**
             * @brief State of jumping of the player. To be replaced with a state machine in the future.
             */
            uint8_t jumping;

        public:
            /**
             * @brief This method registers classes with Godot.
             * @details This method registers methods, properties, and signals with the Godot engine.
             */
            static void _register_methods();

            /**
             * @brief Construct a new Player object.
             */
            Player();

            /**
             * @brief Destroy the Player object.
             */
            ~Player();

            /**
             * @brief Initialize the class from Godot.
             * @details This method is called just once when the Godot engine connects to the instance of the class.
             */
            void _init();

            /**
             * @brief Code to be run when ready.
             * @details This method is run when all the children of this node are ready.
             */
            void _ready();

            /**
             * @brief This class handles the physics processing.
             * @details Every delta time, this function is called to check for input and update positioning.
             * 
             * @param[in] delta The difference in time that passed since the last call to this method.
             */
            void _physics_process(float delta);

            /**
             * @brief Set the sprite frames object.
             * 
             * @param[in] new_sprite_frames The new sprite frame.
             */
            void set_sprite_frames(Ref<SpriteFrames> new_sprite_frames);

            /**
             * @brief Get the sprite frames object.
             * 
             * @return Ref<SpriteFrames> A reference to the sprite frames object.
             */
            Ref<SpriteFrames> get_sprite_frames();

            /**
             * @brief Set the speed object.
             * 
             * @param[in] new_speed The new speed.
             */
            void set_speed(float new_speed);

            /**
             * @brief Get the speed object.
             * 
             * @return float The current speed of the player.
             */
            float get_speed();

            /**
             * @brief Set the jump force object.
             * 
             * @param[in] new_jump_force The new force applied to the player to make him jump.
             */
            void set_jump_force(float new_jump_force);

            /**
             * @brief Get the jump force object.
             * 
             * @return float The current force being applied to the player.
             */
            float get_jump_force();

            /**
             * @brief Set the gravity object.
             * 
             * @param[in] new_gravity The new gravity to apply to the player.
             */
            void set_gravity(float new_gravity);

            /**
             * @brief Get the gravity object.
             * 
             * @return float The current gravity applied to the player.
             */
            float get_gravity();

            /**
             * @brief Set the run speed object.
             * 
             * @param[in] new_run_speed The new speed for running.
             */
            void set_run_speed(float new_run_speed);

            /**
             * @brief Get the run speed object.
             * 
             * @return float The current run speed of the player.
             */
            float get_run_speed();

            /**
             * @brief This signal is called when the player moves.
             * @details The jump action is not included in this signal, just moving left or right.
             * 
             * @param[in] position The new position of the player.
             */
            void _on_Player_player_moved(Vector2 position);
    };
}

#endif
