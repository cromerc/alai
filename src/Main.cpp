#include "Main.h"

#include <SceneTree.hpp>

using namespace godot;

void Main::_register_methods()
{
    register_method("_ready", &Main::_ready);
    register_method("_physics_process", &Main::_physics_process);
    register_property<Main, bool>("full_screen", &Main::set_full_screen, &Main::get_full_screen, JUEGO_MAIN_FULL_SCREEN);
    register_property<Main, Vector2>("window_size", &Main::set_window_size, &Main::get_window_size, JUEGO_MAIN_WINDOW_SIZE);
    register_property<Main, int8_t>("launch_screen", &Main::set_launch_screen, &Main::get_launch_screen, JUEGO_MAIN_LAUNCH_SCREEN);
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

    full_screen = JUEGO_MAIN_FULL_SCREEN;
    window_size = JUEGO_MAIN_WINDOW_SIZE;
    launch_screen = JUEGO_MAIN_LAUNCH_SCREEN;
}

void Main::_ready()
{
    if (get_full_screen())
    {
        _os->set_window_fullscreen(true);
    }
    else
    {
        String resolution = String("Resolution before: " + String().num(_os->get_window_size().x) + "x" + String().num(_os->get_window_size().y));
        Godot::print(resolution);

        _os->set_window_size(window_size);
        _os->set_window_position(
            _os->get_screen_position(get_launch_screen()) + _os->get_screen_size() *  0.5 - _os->get_window_size() * 0.5
        );

        resolution = String("Resolution after: " + String().num(_os->get_window_size().x) + "x" + String().num(_os->get_window_size().y));

        Godot::print(resolution);
    }
}

void Main::_physics_process(float delta)
{
    if (_input->is_action_just_pressed("ui_cancel"))
    {
        get_tree()->quit();
    }
}

void Main::set_full_screen(bool new_full_screen)
{
    full_screen = new_full_screen;
}

bool Main::get_full_screen()
{
    return full_screen;
}

void Main::set_window_size(Vector2 new_window_size)
{
    window_size = new_window_size;
}

Vector2 Main::get_window_size()
{
    return window_size;
}

void Main::set_launch_screen(int8_t new_launch_screen)
{
    launch_screen = new_launch_screen;
}

int8_t Main::get_launch_screen()
{
    if (launch_screen == -1)
    {
        return _os->get_current_screen();
    }
    else
    {
        return launch_screen;
    }
}
