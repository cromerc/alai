#include "CameraLimit.h"

#include <SceneTree.hpp>
#include <TileMap.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <Node.hpp>

using namespace godot;

void CameraLimit::_register_methods()
{
    register_method("_ready", &CameraLimit::_ready);
}

CameraLimit::CameraLimit()
{
}

CameraLimit::~CameraLimit()
{
}

void CameraLimit::_init()
{
}

void CameraLimit::_ready()
{
    auto node = find_node("Middleground");
    auto middle_ground = cast_to<TileMap>(node);
    if (middle_ground != NULL)
    {
        auto used_rect = middle_ground->get_used_rect();
        auto bounds = Vector2(used_rect.position.x + used_rect.size.x, used_rect.position.y + used_rect.size.y);
        node = get_tree()->get_root()->find_node("Camera2D", true, false);
        auto camera = cast_to<Camera2D>(node);
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
