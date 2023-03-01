extends Area2D


var timer := Timer.new()


func _ready() -> void:
	add_child(timer)
	timer.wait_time = 0.1
	var err = timer.connect("timeout", self, "_on_timer_timeout")
	if err == OK:
		timer.start()


func _on_timer_timeout() -> void:
	Event.emit_signal("report_object", self.get_name(), "not collected", global_position, Vector2())
	timer.start()
