#include "Main.h"

#include <SceneTree.hpp>

void alai::main::Main::_register_methods()
{
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("_physics_process", &Main::_physics_process);
    godot::register_method("_on_monitor_loaded", &Main::_on_monitor_loaded);
    godot::register_property<Main, godot::String>("game_version", &Main::set_game_version, &Main::get_game_version, godot::String(main::game_version.c_str()));
    godot::register_property<Main, godot::Ref<godot::PackedScene>>("level", &Main::set_level, &Main::get_level, NULL, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, godot::String("PackedScene"));
    godot::register_property<Main, bool>("full_screen", &Main::set_full_screen, &Main::get_full_screen, main::full_screen);
    godot::register_property<Main, godot::Vector2>("window_size", &Main::set_window_size, &Main::get_window_size, main::window_size);
    godot::register_property<Main, int8_t>("launch_screen", &Main::set_launch_screen, &Main::get_launch_screen, main::launch_screen);
    godot::register_signal<Main>("monitor_loaded");
}

alai::main::Main::Main()
{
}

alai::main::Main::~Main()
{
}

void alai::main::Main::_init()
{
    _os = godot::OS::get_singleton();
    _input = godot::Input::get_singleton();
    _project_settings = godot::ProjectSettings::get_singleton();
    _resource_loader = godot::ResourceLoader::get_singleton();

    game_version = godot::String(main::game_version.c_str());
    full_screen = main::full_screen;
    window_size = main::window_size;
    launch_screen = main::launch_screen;
}

void alai::main::Main::_ready()
{
    auto success = _project_settings->load_resource_pack("monitor.pck");
    if (success)
    {
        // Load monitor from pck
        godot::Godot::print("Monitor pck found, loading...");
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
        godot::Godot::print("CRT pck found, loading...");
        godot::Ref<godot::PackedScene> crt_scene = _resource_loader->load("res://shaders/crt/crt.tscn");
        add_child(crt_scene->instance());
    }
    else if (_resource_loader->exists("res://shaders/crt/crt.tscn"))
    {
        // Load crt from alai's pck
        godot::Ref<godot::PackedScene> crt_scene = _resource_loader->load("res://shaders/crt/crt.tscn");
        add_child(crt_scene->instance());
    }
}

void alai::main::Main::_on_monitor_loaded()
{
    if (level != nullptr)
    {
        auto level_node = load_level();
        connect("monitor_loaded", level_node->get_child(0)->find_node("Player", true, false), "_on_monitor_loaded");
        emit_signal("monitor_loaded");
    }
}

void alai::main::Main::load_monitor()
{
    godot::Ref<godot::PackedScene> monitor_scene = _resource_loader->load("res://monitor/Monitor.tscn");
    add_child(monitor_scene->instance());
    auto monitor = get_node("Monitor");
    monitor->connect("monitor_loaded", this, "_on_monitor_loaded");
    get_tree()->set_pause(true);
}

godot::Node *alai::main::Main::load_level()
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

void alai::main::Main::_physics_process(float delta)
{
    if (_input->is_action_just_pressed("ui_cancel"))
    {
        get_tree()->quit();
    }
}

void alai::main::Main::set_level(godot::Ref<godot::PackedScene> level)
{
    this->level = level;
}

godot::Ref<godot::PackedScene> alai::main::Main::get_level()
{
    return this->level;
}

void alai::main::Main::set_game_version(godot::String game_version)
{
    this->game_version = game_version;
}

godot::String alai::main::Main::get_game_version()
{
    return this->game_version;
}

void alai::main::Main::set_full_screen(bool full_screen)
{
    this->full_screen = full_screen;
}

bool alai::main::Main::get_full_screen()
{
    return this->full_screen;
}

void alai::main::Main::set_window_size(godot::Vector2 window_size)
{
    this-> window_size = window_size;
}

godot::Vector2 alai::main::Main::get_window_size()
{
    return this->window_size;
}

void alai::main::Main::set_launch_screen(int8_t launch_screen)
{
    this->launch_screen = launch_screen;
}

int8_t alai::main::Main::get_launch_screen()
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
