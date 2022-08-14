#include "Main.h"

#include <SceneTree.hpp>

using namespace godot;
using namespace main;

void Main::_register_methods()
{
    register_method("_ready", &Main::_ready);
    register_method("_physics_process", &Main::_physics_process);
    register_method("_on_monitor_loaded", &Main::_on_monitor_loaded);
    register_property<Main, String>("game_version", &Main::set_game_version, &Main::get_game_version, String(main::game_version.c_str()));
    register_property<Main, Ref<PackedScene>>("level", &Main::set_level, &Main::get_level, NULL, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("PackedScene"));
    register_property<Main, bool>("full_screen", &Main::set_full_screen, &Main::get_full_screen, main::full_screen);
    register_property<Main, Vector2>("window_size", &Main::set_window_size, &Main::get_window_size, main::window_size);
    register_property<Main, int8_t>("launch_screen", &Main::set_launch_screen, &Main::get_launch_screen, main::launch_screen);
    register_signal<Main>("monitor_loaded");
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
    _project_settings = ProjectSettings::get_singleton();
    _resource_loader = ResourceLoader::get_singleton();

    game_version = String(main::game_version.c_str());
    full_screen = main::full_screen;
    window_size = main::window_size;
    launch_screen = main::launch_screen;
}

void Main::_ready()
{
    auto success = _project_settings->load_resource_pack("monitor.pck");
    if (success)
    {
        // Load monitor from pck
        Godot::print("Monitor pck found, loading...");
        load_monitor();
    }
    else if (_resource_loader->exists("res://monitor/Monitor.tscn"))
    {
        // Load monitor from alai's pck
        load_monitor();
    }
    else
    {
        // There is no monitor included
        _on_monitor_loaded();
    }

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

    success = _project_settings->load_resource_pack("crt.pck");
    if (success)
    {
        // Load crt from pck
        Godot::print("CRT pck found, loading...");
        Ref<PackedScene> crt_scene = _resource_loader->load("res://shaders/crt/crt.tscn");
        add_child(crt_scene->instance());
    }
    else if (_resource_loader->exists("res://shaders/crt/crt.tscn"))
    {
        // Load crt from alai's pck
        Ref<PackedScene> crt_scene = _resource_loader->load("res://shaders/crt/crt.tscn");
        add_child(crt_scene->instance());
    }
}

void Main::_on_monitor_loaded()
{
    if (level != nullptr)
    {
        auto level_node = load_level();
        connect("monitor_loaded", level_node->get_child(0)->find_node("Player", true, false), "_on_monitor_loaded");
        emit_signal("monitor_loaded");
    }
}

void Main::load_monitor()
{
    Ref<PackedScene> monitor_scene = _resource_loader->load("res://monitor/Monitor.tscn");
    add_child(monitor_scene->instance());
    auto monitor = get_node("Monitor");
    monitor->connect("monitor_loaded", this, "_on_monitor_loaded");
    get_tree()->set_pause(true);
}

Node *Main::load_level()
{
    if (level != nullptr)
    {
        auto path = level->get_path();
        auto loaded_level = level->instance();
        auto level_node = get_node("Level");
        level_node->add_child(loaded_level);
        return level_node;
    }
    return nullptr;
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
