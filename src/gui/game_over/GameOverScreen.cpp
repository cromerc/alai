#include "gui/game_over/GameOverScreen.h"
#include "Event.h"

#include <PackedScene.hpp>
#include <Ref.hpp>
#include <Resource.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

void alai::GameOverScreen::_register_methods()
{  
    register_method("_on_restart_button_pressed", &GameOverScreen::_on_restart_button_pressed);
    register_method("_ready", &GameOverScreen::_ready);
    register_method("connect_signal", &GameOverScreen::connect_signal);
    register_method("_on_player_died", &GameOverScreen::_on_player_died);
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
    if (_resource_loader->exists("res://levels/Prototype.tscn"))
    {
        godot::Ref<godot::PackedScene> level_scene = _resource_loader->load("res://levels/Prototype.tscn");
        auto level = level_scene->instance(); 
        auto level_node = get_tree()->get_root()->get_node("Main")->find_node("Level");

        if (level_node != nullptr)
        {
            level_node->add_child(level);
            set_visible(false);
            call_deferred("connect_signal");
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

void alai::GameOverScreen::connect_signal()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("player_died", this, "_on_player_died");
}
