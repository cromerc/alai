extends CanvasLayer

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta):
	if get_tree().paused:
		visible = false
	else:
		visible = true
