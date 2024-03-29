extends KinematicBody2D


export var direction = -1
export var speed = 50
export var follow_path = false
var target: Vector2 = Vector2(0, 0)
var target_id = 0
var start_position = Vector2()


func _ready() -> void:
	start_position = position
	if follow_path:
		if $Path.get_child_count() == 0:
			follow_path = false
		else:
			target = $Path.get_child(0).position
	if direction == 1:
		$AnimatedSprite.flip_h = true

	Event.connect("level_loaded", self, "_on_level_loaded")


func _physics_process(delta: float) -> void:
	if $LeftWallChecker.is_colliding():
		wall_checker_collided($LeftWallChecker)
	elif $RightWallChecker.is_colliding():
		wall_checker_collided($RightWallChecker)

	var velocity: Vector2 = Vector2(0, 0)
	if not follow_path:
		var target_position = position
		target_position.x *= 2 * direction
		position = position.move_toward(target_position, round(speed * delta))

		velocity = get_velocity_towards_target(delta)
		var collision = move_and_collide(velocity, true, true, true)
		if collision and collision.collider.name != "Player":
			var _collision = move_and_collide(velocity)
	else:
		velocity = get_velocity_towards_target(delta)

		var collision = move_and_collide(velocity, true, true, true)
		if collision and collision.collider.name != "Player":
			var _collision = move_and_collide(velocity)
		else:
			position = position.move_toward(start_position + target, round(speed * delta))

		if position == start_position + target:
			if $Path.get_child_count() - 1 == target_id:
				target_id = -1
				target = $Path.position
			else:
				target_id += 1
				target = $Path.get_child(target_id).position

			if start_position.x + target.x > position.x:
				$AnimatedSprite.flip_h = true
			elif start_position.x + target.x < position.x:
				$AnimatedSprite.flip_h = false

	Event.emit_signal("object_updated", self.get_name(), "Flying", global_position, velocity)


func get_velocity_towards_target(delta: float) -> Vector2:
	var velocity = Vector2(0, 0)
	if start_position.x + target.x > position.x:
		velocity.x = speed * delta
	elif start_position.x + target.x < position.x:
		velocity.x = -speed * delta

	if start_position.y + target.y > position.y:
		velocity.y = speed * delta
	elif start_position.y + target.y < position.y:
		velocity.y = -speed * delta
	return velocity


func wall_checker_collided(wall_checker: RayCast2D) -> void:
	if wall_checker.get_collider().name == "Player":
		Event.emit_signal("player_touched", 3)
	direction *= -1
	$AnimatedSprite.flip_h = not $AnimatedSprite.flip_h


func _on_level_loaded() -> void:
	Event.emit_signal("object_created", self.get_name(), "Flying", global_position, Vector2(0, 0))
