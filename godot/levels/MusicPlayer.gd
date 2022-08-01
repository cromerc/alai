extends AudioStreamPlayer


# there is currently a bug with AudioStreamPlayer
# it doesn't pause when the tree is paused
# so let's manually check if paused and pause the audio
# for this to work pause mode for the node is set to process instead of inherit


func _physics_process(_delta: float) -> void:
	if get_tree().paused and playing:
		stop()
		playing = false
	elif not get_tree().paused and not playing:
		play()
		playing = true
