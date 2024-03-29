extends KinematicBody2D


var velocity = Vector2()
export var direction = -1
export var detect_edges = true
export var speed = 25
export var gravity = 9.8
var timer := Timer.new()


func _ready() -> void:
	if direction == 1:
		$AnimatedSprite.flip_h = true
	$FloorChecker.position.x = $CollisionShape2D.shape.get_extents().x * direction
	$FloorChecker.enabled = detect_edges
	Event.connect("level_loaded", self, "_on_level_loaded")

	add_child(timer)
	timer.wait_time = 0.1
	var err = timer.connect("timeout", self, "_on_timer_timeout")
	if err == OK:
		timer.start()


func _physics_process(_delta: float) -> void:
	if is_on_wall() or not $FloorChecker.is_colliding() and is_on_floor() and $FloorChecker.enabled:
		direction *= -1
		$AnimatedSprite.flip_h = not $AnimatedSprite.flip_h
		$FloorChecker.position.x = $CollisionShape2D.shape.get_extents().x * direction

	velocity.y += gravity
	velocity.x = speed * direction
	velocity = move_and_slide(velocity, Vector2.UP)

	for i in get_slide_count():
		var collision = get_slide_collision(i)
		if collision.collider.name == "Player":
			Event.emit_signal("player_touched", 3)

	Event.emit_signal("object_updated", self.get_name(), "Walking", global_position, velocity)


func squash() -> void:
	Event.emit_signal("object_removed", self.get_name())
	queue_free()


func _on_level_loaded() -> void:
	Event.emit_signal("object_created", self.get_name(), "Walking", global_position, Vector2(0, 0))


func _on_timer_timeout() -> void:
	Event.emit_signal("report_object", self.get_name(), "walking", global_position, velocity)
	timer.start()
