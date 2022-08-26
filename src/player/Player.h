#ifndef ALAI_PLAYER_H
#define ALAI_PLAYER_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Sprite.hpp>
#include <AnimatedSprite.hpp>
#include <SpriteFrames.hpp>
#include <ResourceLoader.hpp>

namespace godot
{
    /**
     * @brief This namespace contains the global variables related to the player and its states.
     * 
     */
    namespace player
    {
        /**
         * @brief The default sprite resource of the player.
         * 
         */
        const char player_sprite_frames[] = "res://characters/player/sprites/green.tres";
        /**
         * @brief The default speed of the player.
         * 
         */
        const float speed = 60.0;
        /**
         * @brief The default jump force applied when jumping.
         * 
         */
        const float jump_force = 300.0;
        /**
         * @brief The default bounce force applied when bouncing on something.
         * 
         */
        const float bounce_force = 200.0;
        /**
         * @brief The default gravity applied to the player.
         * 
         */
        const float gravity = 9.81;
        /**
         * @brief The default run speed multiplier.
         * 
         */
        const float run_speed = 2.0;
        /**
         * @brief The default double jump activation state.
         * 
         */
        const bool double_jump = true;

        /**
         * @brief This class is used to control the player.
         * 
         * @details This class allows the player to move, run, and jump as well as controls the sprite displayed for those actions.
         */
        class Player : public KinematicBody2D
        {
            GODOT_CLASS(Player, KinematicBody2D)

            private:
                /**
                 * @brief ResourceLoader singleton.
                 * 
                 */
                ResourceLoader *_resource_loader;

                /**
                 * @brief The animated sprite connected to the KinematicBody2D.
                 * 
                 */
                AnimatedSprite *animated_sprite;
                /**
                 * @brief The sprite frames used in the animated sprite.
                 * 
                 */
                Ref<SpriteFrames> sprite_frames;
                /**
                 * @brief The coins the player has collected.
                 * 
                 */
                uint8_t coins;
                /**
                 * @brief The velocity at which moves the player moves.
                 * 
                 */
                Vector2 velocity;
                /**
                 * @brief The speed that the player moves in.
                 * 
                 */
                float speed;
                /**
                 * @brief The force applied to the player when jumping.
                 * 
                 */
                float jump_force;
                /**
                 * @brief The force applied to the player when bouncing off something.
                 * 
                 */
                float bounce_force;
                /**
                 * @brief The gravity applied to the player.
                 * 
                 */
                float gravity;
                /**
                 * @brief The speed multiplier used to make the player move faster.
                 * 
                 */
                float run_speed;
                /**
                 * @brief If double jump is enabled or not.
                 * 
                 */
                bool double_jump;

            public:
                /**
                 * @brief This method registers classes with Godot.
                 * 
                 * @details This method registers methods, properties, and signals with the Godot engine.
                 */
                static void _register_methods();

                /**
                 * @brief Construct a new Player object.
                 * 
                 */
                Player();

                /**
                 * @brief Destroy the Player object.
                 * 
                 */
                ~Player();

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
                 * @brief This class handles the physics processing.
                 * 
                 * @details Every delta time, this function is called to check for input and update positioning.
                 * 
                 * @param[in] delta The difference in time that passed since the last call to this method.
                 */
                void _physics_process(float delta);

                /**
                 * @brief Set the sprite frames object.
                 * 
                 * @param[in] sprite_frames The new sprite frame.
                 */
                void set_sprite_frames(Ref<SpriteFrames> sprite_frames);

                /**
                 * @brief Get the sprite frames object.
                 * 
                 * @return Ref<SpriteFrames> A reference to the sprite frames object.
                 */
                Ref<SpriteFrames> get_sprite_frames();

                /**
                 * @brief Set the speed object.
                 * 
                 * @param[in] speed The new speed.
                 */
                void set_speed(float speed);

                /**
                 * @brief Get the speed object.
                 * 
                 * @return float The current speed of the player.
                 */
                float get_speed();

                /**
                 * @brief Set the jump force object.
                 * 
                 * @param[in] jump_force The new force applied to the player to make him jump.
                 */
                void set_jump_force(float jump_force);

                /**
                 * @brief Get the jump force object.
                 * 
                 * @return float The current force being applied to the player.
                 */
                float get_jump_force();

                /**
                 * @brief Set the bounce force object.
                 * 
                 * @param[in] bounce_force The new force applied to the player to make him bounce.
                 */
                void set_bounce_force(float bounce_force);

                /**
                 * @brief Get the bounce force object.
                 * 
                 * @return float The current force being applied to the player.
                 */
                float get_bounce_force();

                /**
                 * @brief Set the gravity object.
                 * 
                 * @param[in] gravity The new gravity to apply to the player.
                 */
                void set_gravity(float gravity);

                /**
                 * @brief Get the gravity object.
                 * 
                 * @return float The current gravity applied to the player.
                 */
                float get_gravity();

                /**
                 * @brief Set the run speed object.
                 * 
                 * @param[in] run_speed The new speed for running.
                 */
                void set_run_speed(float run_speed);

                /**
                 * @brief Get the run speed object.
                 * 
                 * @return float The current run speed of the player.
                 */
                float get_run_speed();

                /**
                 * @brief Set the double jump object.
                 * 
                 * @param[in] double_jump The new double dump value.
                 */
                void set_double_jump(bool double_jump);

                /**
                 * @brief Get the double jump object.
                 * 
                 * @return true If double jump is enabled.
                 * @return false If double jump is disabled.
                 */
                bool get_double_jump();

                /**
                 * @brief Set the velocity object.
                 * 
                 * @param[in] velocity The new velocity of the player.
                 */
                void set_velocity(Vector2 velocity);

                /**
                 * @brief Get the velocity object.
                 * 
                 * @return Vector2 Returns the velocity of the player.
                 */
                Vector2 get_velocity();

                /**
                 * @brief This function is called when an enemy touches the player.
                 * 
                 */
                void _on_player_touched();

                void _on_monitor_loaded();
        };
    }
}

#endif
