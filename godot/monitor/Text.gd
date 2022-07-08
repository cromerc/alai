extends TextEdit


onready var previousText: String = text


func _on_text_changed() -> void:
	var col = cursor_get_column()
	# if a scroll bar appears, reset to the previous good string
	if text.length() > 50:
		text = previousText
		col = col - 1
	previousText = text
	cursor_set_column(col)
