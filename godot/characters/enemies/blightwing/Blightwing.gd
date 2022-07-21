extends KinematicBody2D


# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	var velocity = Vector2()
	velocity.x += 1 * 50
	#velocity.y -= 1 * 50
	velocity = move_and_slide(velocity, Vector2(0, 0), true, 2)
	for i in get_slide_count():
		var collision = get_slide_collision(i)
		#if collision.collider.name == "Player":
		#	print("Blightwing: " + String(OS.get_unix_time()) + " " + collision.collider.name)


func _on_Area2D_body_entered(body: Node) -> void:
	print(body.name)
