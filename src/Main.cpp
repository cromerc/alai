#include "Main.h"

#include <SceneTree.hpp>

using namespace godot;
using namespace main;

void Main::_register_methods()
{
    register_method("_ready", &Main::_ready);
    register_method("_physics_process", &Main::_physics_process);
    register_property<Main, String>("game_version", &Main::set_game_version, &Main::get_game_version, String(main::game_version.c_str()));
    register_property<Main, Ref<PackedScene>>("level", &Main::set_level, &Main::get_level, NULL, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("PackedScene"));
    register_property<Main, bool>("full_screen", &Main::set_full_screen, &Main::get_full_screen, main::full_screen);
    register_property<Main, Vector2>("window_size", &Main::set_window_size, &Main::get_window_size, main::window_size);
    register_property<Main, int8_t>("launch_screen", &Main::set_launch_screen, &Main::get_launch_screen, main::launch_screen);
}

Main::Main()
{
}

Main::~Main()
{
}

void Main::_init()
{
    _os = OS::get_singleton();
    _input = Input::get_singleton();

    game_version = String(main::game_version.c_str());
    full_screen = main::full_screen;
    window_size = main::window_size;
    launch_screen = main::launch_screen;
}

void Main::_ready()
{
    get_tree()->set_pause(true);
    if (get_full_screen())
    {
        _os->set_window_fullscreen(true);
    }
    else
    {
        _os->set_window_size(window_size);
        _os->set_window_position(
            _os->get_screen_position(get_launch_screen()) + _os->get_screen_size() *  0.5 - _os->get_window_size() * 0.5
        );
    }

    if (level != NULL)
    {
        add_child(level->instance());
    }
}

void Main::_physics_process(float delta)
{
    if (_input->is_action_just_pressed("ui_cancel"))
    {
        get_tree()->quit();
    }
}

void Main::set_level(Ref<PackedScene> level)
{
    this->level = level;
}

Ref<PackedScene> Main::get_level()
{
    return this->level;
}

void Main::set_game_version(String game_version)
{
    this->game_version = game_version;
}

String Main::get_game_version()
{
    return this->game_version;
}

void Main::set_full_screen(bool full_screen)
{
    this->full_screen = full_screen;
}

bool Main::get_full_screen()
{
    return this->full_screen;
}

void Main::set_window_size(Vector2 window_size)
{
    this-> window_size = window_size;
}

Vector2 Main::get_window_size()
{
    return this->window_size;
}

void Main::set_launch_screen(int8_t launch_screen)
{
    this->launch_screen = launch_screen;
}

int8_t Main::get_launch_screen()
{
    if (this->launch_screen == -1)
    {
        return _os->get_current_screen();
    }
    else
    {
        return this->launch_screen;
    }
}
