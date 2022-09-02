#include "gui/game_over/GameOverScreen.h"

#include "Event.h"

#include <AudioStreamPlayer.hpp>
#include <PackedScene.hpp>
#include <Ref.hpp>
#include <Resource.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

void alai::GameOverScreen::_register_methods()
{
    godot::register_method("_on_restart_button_pressed", &GameOverScreen::_on_restart_button_pressed);
    godot::register_method("_ready", &GameOverScreen::_ready);
    godot::register_method("restart_game", &GameOverScreen::restart_game);
    godot::register_method("connect_signal", &GameOverScreen::connect_signal);
    godot::register_method("_on_player_died", &GameOverScreen::_on_player_died);
	godot::register_method("_on_visibility_changed", &GameOverScreen::_on_visibility_changed);
}

alai::GameOverScreen::GameOverScreen()
{
}

alai::GameOverScreen::~GameOverScreen()
{
}

void alai::GameOverScreen::_init()
{
    _resource_loader = godot::ResourceLoader::get_singleton();
}

void alai::GameOverScreen::_ready()
{
    connect_signal();
}

void alai::GameOverScreen::_on_restart_button_pressed()
{
    if (_resource_loader->exists("res://levels/PrototypeR.tscn"))
    {
        godot::Ref<godot::PackedScene> level_scene = _resource_loader->load("res://levels/PrototypeR.tscn");
        auto level = level_scene->instance(); 
        auto level_node = get_tree()->get_root()->get_node("Main")->find_node("Level");

        if (level_node != nullptr)
        {
            level_node->add_child(level);
            set_visible(false);
            call_deferred("restart_game");
        }
        else
        {
            WARN_PRINT("Node level not found!");
        }
    }
}

void alai::GameOverScreen::_on_player_died()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->disconnect("player_died", this, "_on_player_died");
    set_visible(true);
    auto level_node = get_tree()->get_root()->get_node("Main")->find_node("Level");
    if (level_node != nullptr)
    {
        auto child = level_node->get_child(0); 
        if (child != nullptr)
        {
            // Delete the currently active level from the tree.
            child->queue_free();
        }
        else
        {
            WARN_PRINT("Child not found!");
        }
    }
    else
    {
        WARN_PRINT("Node level not found!");
    }
}

void alai::GameOverScreen::restart_game()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->emit_signal("game_started");
    connect_signal();
}

void alai::GameOverScreen::connect_signal()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("player_died", this, "_on_player_died");
}

void alai::GameOverScreen::_on_visibility_changed()
{
    auto gameoversound = get_node<godot::AudioStreamPlayer>("GameOverMusic");
    if (is_visible()) 
    { 
        gameoversound->play();
    }
    else
    {
        gameoversound->stop();
    }
}
