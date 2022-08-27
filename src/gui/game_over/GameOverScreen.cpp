#include "gui/game_over/GameOverScreen.h"
#include <Resource.hpp>
#include <Ref.hpp>
#include <Node.hpp>
#include <SceneTree.hpp>
#include <PackedScene.hpp>
#include <Viewport.hpp>

using namespace godot;

void GameOverScreen::_register_methods()
{  
    register_method("_on_animation_finished", &GameOverScreen::_on_botonreiniciar_pressed);
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

void GameOverScreen::_on_botonreiniciar_pressed()
{

    if (_resource_loader->exists("res://levels/Prototype.tscn")) //CAMBIAR A DINAMICO
    {
        Ref<PackedScene> level_scene = _resource_loader->load("res://levels/Prototype.tscn");
        auto level = level_scene->instance(); 
        auto level_node = get_tree()->get_root()->find_node("Level");
        level_node->add_child(level);
    }
}


