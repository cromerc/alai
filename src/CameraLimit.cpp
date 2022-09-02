#include "CameraLimit.h"

#include <Camera2D.hpp>
#include <SceneTree.hpp>
#include <TileMap.hpp>
#include <Viewport.hpp>

void alai::CameraLimit::_register_methods()
{
    godot::register_method("_ready", &CameraLimit::_ready);
}

alai::CameraLimit::CameraLimit()
{
}

alai::CameraLimit::~CameraLimit()
{
}

void alai::CameraLimit::_init()
{
}

void alai::CameraLimit::_ready()
{
    auto node = find_node("Middleground");
    auto middle_ground = cast_to<godot::TileMap>(node);
    if (middle_ground != NULL)
    {
        auto used_rect = middle_ground->get_used_rect();
        auto bounds = godot::Vector2(used_rect.position.x + used_rect.size.x, used_rect.position.y + used_rect.size.y);
        node = get_tree()->get_root()->find_node("Camera2D", true, false);
        auto camera = cast_to<godot::Camera2D>(node);
        if (camera != NULL)
        {
            camera->set_limit(2, bounds.x * middle_ground->get_cell_size().x);
            camera->set_limit(3, bounds.y * middle_ground->get_cell_size().y);
        }
        else
        {
            ERR_PRINT("Could not find Camera2D node!");
        }
    }
    else
    {
        ERR_PRINT("Could not find Middleground node!");
    }
}
