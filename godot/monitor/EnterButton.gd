extends Button


signal input_validated(player)


func _on_Button_pressed() -> void:
	var name = get_node("%Name")
	var rut = get_node("%Rut")
	var email = get_node("%Email")
	var player: Dictionary = {
		"name" : name.text,
		"rut" : rut.text,
		"email" : email.text
	}
	emit_signal("input_validated", player)
