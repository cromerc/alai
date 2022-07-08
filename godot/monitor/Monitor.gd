extends Node


export var enabled: bool = false
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
	game_version = get_parent().game_version

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

	player["rut"] = clean_rut(player["rut"])

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
	game["timestamp"] = OS.get_unix_time()
	game["frames"] = frames

	var err = $HTTPRequest.connect("request_completed", self, "_on_request_completed")
	if err != OK:
		print(err)

	err = $MonitorGUI.find_node("Button").connect("input_validated", self, "_on_input_validated")
	if err != OK:
		print(err)


func _physics_process(_delta: float) -> void:
	if enabled:
		if started:
			var frame = empty_frame.duplicate(true)
			frame["coins"] = coins
			frame["points"] = points
			frame["fps"] = Engine.get_frames_per_second()
			frame["elapsed_time"] = OS.get_ticks_msec() - start_time

			var frame_objects = objects.duplicate()
			frame["objects"] = frame_objects

			frames.append(frame)

			if Input.is_action_just_pressed("Send"):
				stop_monitor()
				send_data()
		else:
			if Input.is_action_just_pressed("Send"):
				start_monitor()


func _on_input_validated(validated_player: Dictionary) -> void:
	$MonitorGUI.queue_free()
	get_tree().paused = false
	player = validated_player.duplicate(true)


func _object_created(name: String, state: String, position: Vector2, velocity: Vector2) -> void:
	if enabled and started:
		add_object(name, state, position, velocity)


func _object_updated(name: String, state: String, position: Vector2, velocity: Vector2) -> void:
	if enabled and started:
		remove_object(name)
		add_object(name, state, position, velocity)


func _object_removed(name: String) -> void:
	if enabled and started:
		remove_object(name)


func start_monitor() -> void:
	frames.clear()
	game["level_id"] = 2 # PrototypeR
	game["won"] = false
	game["timestamp"] = OS.get_unix_time()
	start_time = OS.get_ticks_msec()
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

	$HTTPRequest.request(url + "/game", headers, false, HTTPClient.METHOD_POST, body)


func compress_payload(payload: String) -> String:
	var bytes = payload.to_utf8()
	var compressed = bytes.compress(File.COMPRESSION_GZIP)

	var new_payload = Marshalls.raw_to_base64(compressed)

	return new_payload


func clean_rut(rut: String) -> String:
	rut = rut.strip_escapes()
	rut = rut.strip_edges(true, true)
	rut = rut.to_lower()
	rut = rut.replace(".", "")
	rut = rut.replace("-", "")

	var rutTemp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)

	var regex = RegEx.new()
	regex.compile("\\D")
	rutTemp = regex.sub(rutTemp, "", true)

	regex.compile("[^kK\\d]")
	verifier = regex.sub(verifier, "", true)

	rut = rutTemp + verifier

	return rut


func pretty_rut(rut: String) -> String:
	rut = clean_rut(rut)

	var rutTemp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)

	var regex = RegEx.new()
	regex.compile("[^kK\\d]")
	verifier = regex.sub(verifier, "", true)

	var byteArray = rutTemp.to_utf8()
	byteArray.invert()

	var newByteArray: PoolByteArray = PoolByteArray()
	var i = 1
	for symbol in byteArray:
		newByteArray.append(symbol)
		if i == 3:
			newByteArray.append(".".to_utf8()[0])
			i = 0
		i = i + 1
	if newByteArray.size() > 0 and newByteArray[newByteArray.size() - 1] == ".".to_utf8()[0]:
		newByteArray.resize(newByteArray.size() - 1)

	newByteArray.invert()
	rutTemp = newByteArray.get_string_from_utf8()

	if rutTemp.length() == 0 and verifier.length() > 0:
		rutTemp = verifier
	elif rutTemp.length() > 0 and verifier.length() > 0:
		rutTemp = rutTemp + "-" + verifier

	return rutTemp


func is_rut_valid(rut: String) -> bool:
	rut = clean_rut(rut)
	if rut.length() < 8 or rut.length() > 9:
		print_debug("RUT length is invalid!")
		return false

	var rutTemp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)
	print("Rut: " + rutTemp)
	print("Verifier: " + verifier)

	if not rutTemp.is_valid_integer():
		print_debug("RUT isn't a valid integer!")
		return false

	if rutTemp.to_int() > 50000000:
		print_debug("RUT is too large, that is a company!")
		return false

	if verifier != generate_verifier(rut):
		return false

	return true


func generate_verifier(rut: String) -> String:
	if not rut.is_valid_integer():
		print_debug("RUT isn't a valid integer!")
		return ""

	var multiplier: int = 2
	var sum: int = 0
	var remainder: int = 0
	var division: int = 0
	var rutLength: int = rut.length()

	var i: int = rutLength - 1
	while i >= 0:
		sum = sum + rut.substr(i, i + 1).to_int() * multiplier
		multiplier = multiplier + 1
		if multiplier == 8:
			multiplier = 2
		i = i - 1

	var tempSum: float = int(sum)
	division = int(floor(tempSum / 11))
	division = division * 11
	remainder = sum - division

	if remainder != 0:
		remainder = 11 - remainder

	if remainder == 10:
		return "k"
	else:
		return String(remainder)
