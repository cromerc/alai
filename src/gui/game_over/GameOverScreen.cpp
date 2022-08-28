#include "gui/game_over/GameOverScreen.h"
#include "Event.h"

#include <Resource.hpp>
#include <Ref.hpp>
#include <Node.hpp>
#include <SceneTree.hpp>
#include <PackedScene.hpp>
#include <Viewport.hpp>


using namespace godot;

void GameOverScreen::_register_methods()
{  
    register_method("_on_botonreiniciar_pressed", &GameOverScreen::_on_botonreiniciar_pressed);
    register_method("_ready", &GameOverScreen::_ready);
    register_method("connect_signal", &GameOverScreen::connect_signal);
    register_method("_on_player_died", &GameOverScreen::_on_player_died);
}

GameOverScreen::GameOverScreen()
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::_init()
{
     _resource_loader = ResourceLoader::get_singleton();

}

void GameOverScreen::_ready()
{
    connect_signal();
}

void GameOverScreen::_on_botonreiniciar_pressed()
{
    if (_resource_loader->exists("res://levels/Prototype.tscn")) //CAMBIAR A DINAMICO
    {
        Ref<PackedScene> level_scene = _resource_loader->load("res://levels/Prototype.tscn");
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

void GameOverScreen::_on_player_died() //eliminar nivel
{
    auto event = get_node<alai::Event>("/root/Event");
    event->disconnect("player_died", this, "_on_player_died");
    Godot::print("player ded");
    set_visible(true);
    auto level_node = get_tree()->get_root()->get_node("Main")->find_node("Level");
    if (level_node != nullptr)
    {
        auto child = level_node->get_child(0); 
        if (child != nullptr)
        {
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

void GameOverScreen::connect_signal()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("player_died", this, "_on_player_died");
}



