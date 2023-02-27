extends Area2D


func _process(_delta: float) -> void:
    Event.emit_signal("report_object", self.get_name(), "not collected", global_position, Vector2())
