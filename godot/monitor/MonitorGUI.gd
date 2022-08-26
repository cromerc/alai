extends CanvasLayer


export var default_name = ""
export var default_rut = ""
export var default_email = ""


func _ready() -> void:
	get_node("%Name").text = default_name
	get_node("%Rut").text = default_rut
	get_node("%Email").text = default_email
