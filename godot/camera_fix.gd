extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var used_rect = get_node("Middleground").get_used_rect()
	var bounds = Vector2(used_rect.position.x + used_rect.size.x, used_rect.position.y + used_rect.size.y - 1)
	var camera : Camera2D = $"../../Player/Camera2D"
	camera.limit_right = bounds.x * get_node("Middleground").cell_size.x
	camera.limit_bottom = bounds.y * get_node("Middleground").cell_size.y
