extends Node


var player: Dictionary


func _ready() -> void:
	pass


func _on_set_player(player_info: Dictionary) -> void:
	player["name"] = player_info["name"]
	player["rut"] = player_info["rut"]
	player["email"] = player_info["email"]
