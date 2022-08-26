#include "gui/game_over/GameOverScreen.h"
#include <Node.hpp>
#include <SceneTree.hpp>

using namespace godot;

void GameOverScreen::_register_methods()
{
    register_method("_on_restart_button_pressed", &GameOverScreen::_on_restart_button_pressed);
}

GameOverScreen::GameOverScreen()
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::_init()
{

}
void GameOverScreen::_on_restart_button_pressed()
{
    get_tree()->change_scene("res://monitor/GUI.tscn");
}
