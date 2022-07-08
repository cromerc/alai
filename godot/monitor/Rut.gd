extends TextEdit


func _on_Rut_text_changed() -> void:
	_on_Rut_focus_exited()


func _on_Rut_focus_exited() -> void:
	var monitor = get_tree().get_current_scene().get_node("Monitor")
	if text.length() > 12:
		text = text.substr(0, 12)
	text = monitor.pretty_rut(text)
	cursor_set_column(text.length())
