#include "gui/game_over/GameOverScreen.h"
#include <Node.hpp>
using namespace godot;

void GameOverScreen::_register_methods()
{
   register_method("_on_botonreiniciar_pressed", &GameOverScreen::_on_botonreiniciar_pressed);
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
void GameOverScreen::_on_botonreiniciar_pressed()
{
    get_tree().change_scene("res://monitor/GUI.tscn");

}