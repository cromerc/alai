#include "gui/game_won/GameWonScreen.h"

#include "Event.h"

#include <AudioStreamPlayer.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

void alai::GameWonScreen::_register_methods()
{  
    godot::register_method("_ready", &GameWonScreen::_ready);
    godot::register_method("connect_signal", &GameWonScreen::connect_signal);
    godot::register_method("_on_player_won", &GameWonScreen::_on_player_won);
    godot::register_method("_on_quit_button_pressed", &GameWonScreen::_on_quit_button_pressed);
    godot::register_method("_on_visibility_changed", &GameWonScreen::_on_visibility_changed);
}

alai::GameWonScreen::GameWonScreen()
{
}

alai::GameWonScreen::~GameWonScreen()
{
}

void alai::GameWonScreen::_init()
{
}

void alai::GameWonScreen::_ready()
{
    connect_signal();
}

void alai::GameWonScreen::_on_quit_button_pressed()
{
    get_tree()->quit();
}

void alai::GameWonScreen::_on_player_won()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->disconnect("player_won", this, "_on_player_won");
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

void alai::GameWonScreen::connect_signal()
{
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("player_won", this, "_on_player_won");
}

void alai::GameWonScreen::_on_visibility_changed()
{
    auto victorysound = get_node<godot::AudioStreamPlayer>("VictorySound");
    if (is_visible()) 
    { 
        victorysound->play();
    }
    else
    {
        victorysound->stop();
    }
}
