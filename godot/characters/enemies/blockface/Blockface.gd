extends KinematicBody2D


signal player_touched


onready var start_position = position
var velocity = Vector2()
export var speed = 50.0
export var fall_speed = 75.0
var return_to_start: bool = false


func _physics_process(delta: float) -> void:
	if return_to_start:
		position = position.move_toward(start_position, speed * delta)
	else:
		var collision = move_and_collide(Vector2(0, (position.y + fall_speed) * delta))
		if collision:
			return_to_start = true
			$AnimatedSprite.play("normal")
			if collision.collider.name == "Player":
				emit_signal("player_touched")

	if position.y <= start_position.y:
		return_to_start = false
		$AnimatedSprite.play("angry")
