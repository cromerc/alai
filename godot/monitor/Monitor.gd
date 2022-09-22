extends Node


export var monitor_enabled: bool = false
export var anonymous: bool = true
export var debug: bool = false
export var development_url: String = "http://localhost:4050/api/v1"
var url_real: String = "https://alai.cromer.cl/api/v1"
export var use_development_url: bool = false
onready var url: String = development_url if use_development_url else url_real

var start_time: int = 0
var started: bool = false

var player: Dictionary = {}
var os_id: int = 0
var godot_version: Dictionary = Engine.get_version_info()
var processor_count: int = OS.get_processor_count()
var screen_count: int = OS.get_screen_count()
var screen_dpi: int = OS.get_screen_dpi()
var screen_size: Vector2 = OS.get_screen_size()
var machine_id: String = OS.get_unique_id()
var locale: String = OS.get_locale()
var game_version: String
var frames: Array = []

var coins: int = 0
var points: int = 0
var objects: Array = []

const empty_object: Dictionary = {
	"name": "Object Name",
	"state": "Object State",
	"position_x": 0,
	"position_y": 0,
	"velocity_x": 0,
	"velocity_y": 0
}
const empty_frame: Dictionary = {
	"coins": 0,
	"points": 0,
	"fps": 0,
	"elapsed_time": 0,
	"objects": [],
}

# The game dictionary holds all data to be sent to the server
var game: Dictionary = {}


func _ready() -> void:
	Event.connect("object_created", self, "_object_created")
	Event.connect("object_updated", self, "_object_updated")
	Event.connect("object_removed", self, "_object_removed")
	Event.connect("game_started", self, "_on_game_started")
	Event.connect("player_died", self, "_on_game_over")
	Event.connect("player_won", self, "_on_game_won")
	Event.connect("coin_collected", self, "_on_coin_update")

	game_version = get_parent().game_version

	if not anonymous:
		player["rut"] = ""
		player["name"] = ""
		player["email"] = ""

	var os_name = OS.get_name()
	if os_name == "Android":
		os_id = 1
	elif os_name == "iOS":
		os_id = 2
	elif os_name == "HTML5":
		os_id = 3
	elif os_name == "OSX":
		os_id = 4
	elif os_name == "Server":
		os_id = 5
	elif os_name == "Windows":
		os_id = 6
	elif os_name == "UWP":
		os_id = 7
	elif os_name == "X11":
		os_id = 8
	else:
		os_id = 0

	if not anonymous:
		game["player"] = player
	game["level_id"] = 0
	game["os_id"] = os_id
	game["godot_version"] = godot_version
	game["processor_count"] = processor_count
	game["machine_id"] = machine_id
	game["locale"] = locale
	game["screen_count"] = screen_count
	game["screen_dpi"] = screen_dpi
	game["screen_size"] = screen_size
	game["game_version"] = game_version
	game["won"] = false
	game["timestamp"] = int(Time.get_unix_time_from_system())
	game["frames"] = frames

	var err = $HTTPRequest.connect("request_completed", self, "_on_request_completed")
	if err != OK:
		print(err)

	err = $MonitorGUI.find_node("Button").connect("input_validated", self, "_on_input_validated")
	if err != OK:
		print(err)


func _physics_process(_delta: float) -> void:
	if monitor_enabled:
		if anonymous and has_node("MonitorGUI"):
			$MonitorGUI.queue_free()
			Event.emit_signal("monitor_loaded")
			get_tree().paused = false
			start_monitor()
		else:
			if has_node("MonitorGUI") and not $MonitorGUI.visible:
				$MonitorGUI.visible = true
				Event.emit_signal("monitor_loaded")

		if started and not get_tree().paused:
			var frame = empty_frame.duplicate(true)
			frame["coins"] = coins
			frame["points"] = points
			frame["fps"] = Engine.get_frames_per_second()
			frame["elapsed_time"] = Time.get_ticks_msec() - start_time

			var frame_objects = objects.duplicate()
			frame["objects"] = frame_objects

			frames.append(frame)

			if debug and Input.is_action_just_pressed("Send"):
				stop_monitor()
				send_data()
		else:
			if debug and Input.is_action_just_pressed("Send"):
				start_monitor()
	else:
		get_tree().paused = false
		Event.emit_signal("monitor_loaded")
		queue_free()


func _on_input_validated(validated_player: Dictionary) -> void:
	if not anonymous:
		$MonitorGUI.queue_free()
		get_tree().paused = false
		Event.emit_signal("game_started")
		player = validated_player.duplicate(true)
		game["player"] = player
		start_monitor()


func _object_created(name: String, state: String, position: Vector2, velocity: Vector2) -> void:
	if monitor_enabled:
		add_object(name, state, position, velocity)


func _object_updated(name: String, state: String, position: Vector2, velocity: Vector2) -> void:
	if monitor_enabled:
		remove_object(name)
		add_object(name, state, position, velocity)


func _object_removed(name: String) -> void:
	if monitor_enabled:
		remove_object(name)


func start_monitor() -> void:
	frames.clear()
	game["level_id"] = 2 # PrototypeR
	game["won"] = false
	coins = 0
	points = 0
	game["timestamp"] = int(Time.get_unix_time_from_system())
	start_time = Time.get_ticks_msec()
	started = true


func stop_monitor() -> void:
	started = false


func add_object(name: String, state: String, position: Vector2, velocity: Vector2) -> void:
	var object = empty_object.duplicate(true)
	object["name"] = name
	object["state"] = state
	object["position_x"] = position.x
	object["position_y"] = position.y
	object["velocity_x"] = velocity.x
	object["velocity_y"] = velocity.y

	objects.append(object)


func remove_object(name: String) -> void:
	for i in range(0, objects.size()):
		if objects[i]["name"] == name:
			objects.remove(i)
			return


func _on_coin_update(amount: int) -> void:
	coins = coins + amount


func _on_request_completed(result: int, response_code: int, headers: PoolStringArray, body: PoolByteArray) -> void:
	if result != HTTPRequest.RESULT_SUCCESS:
		print_debug("Error: Failed to connect with error code: " + str(result))
		return

	if response_code != HTTPClient.RESPONSE_OK:
		print_debug("Error: Failed response with error code: " + str(response_code))

	print_debug(headers)
	if body.size() > 0:
		var json = JSON.parse(body.get_string_from_utf8())
		print_debug(JSON.print(json.result, "\t"))


func send_data() -> void:
	var json = JSON.print(game)
	var headers = ["Content-Type: application/json", "Content-Encoding: gzip", "Content-Transfer-Encoding: base64"]

	var body = compress_payload(json)

	print("JSON B: " + String(json.length()))
	print("JSON MB: " + String(json.length() / pow(2, 20)))
	print("Body B: " + String(body.length()))
	print("Body MB: " + String(body.length() / pow(2, 20)))

	if not debug:
		$HTTPRequest.request(url + "/game", headers, false, HTTPClient.METHOD_POST, body)
	else:
		var file = File.new()
		if file.open("user://game.json", File.WRITE) != 0:
			print_debug("Could not open game.json for writing!")
			return

		file.store_string(json)
		file.close()


func compress_payload(payload: String) -> String:
	var bytes = payload.to_utf8()
	var compressed = bytes.compress(File.COMPRESSION_GZIP)

	var new_payload = Marshalls.raw_to_base64(compressed)

	return new_payload


func _on_game_started() -> void:
	print_debug("started game")
	if not started:
		start_monitor()


func _on_game_over() -> void:
	if started:
		stop_monitor()
		game["won"] = false
		send_data()


func _on_game_won() -> void:
	if started:
		stop_monitor()
		game["won"] = true
		send_data()
