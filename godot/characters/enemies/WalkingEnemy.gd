extends KinematicBody2D


signal player_touched


var velocity = Vector2()
export var direction = -1
export var detect_edges = true
export var speed = 25
export var gravity = 9.8


func _ready() -> void:
	if direction == 1:
		$AnimatedSprite.flip_h = true
	$FloorChecker.position.x = $CollisionShape2D.shape.get_extents().x * direction
	$FloorChecker.enabled = detect_edges


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
			emit_signal("player_touched")


func squash() -> void:
	queue_free()
