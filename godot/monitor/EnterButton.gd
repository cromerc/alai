extends Button


signal input_validated(player)


func is_valid_name(name: String) -> bool:
	if name.strip_edges() == "":
		print_debug("Name is empty!")
		return false
	if name.split(" ").size() == 1:
		print_debug("Doesn't contain at least a first and last name!")
		return false
	return true


func is_valid_rut(rut: String) -> bool:
	var rut_node = get_node("%Rut")
	rut = rut_node.clean_rut(rut)
	if rut.length() < 8 or rut.length() > 9:
		print_debug("RUT length is invalid!")
		return false

	var rut_temp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)

	if not rut_temp.is_valid_integer():
		print_debug("RUT isn't a valid integer!")
		return false

	if rut_temp.to_int() > 50000000:
		print_debug("RUT is too large, that is a company!")
		return false

	if verifier != generate_verifier(rut_temp):
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
	var rut_length: int = rut.length()

	var i: int = rut_length - 1
	while i >= 0:
		sum = sum + rut.substr(i, 1).to_int() * multiplier
		multiplier = multiplier + 1
		if multiplier == 8:
			multiplier = 2
		i = i - 1

	var tempSum: float = sum
	division = int(floor(tempSum / 11))
	division = division * 11
	remainder = sum - division

	if remainder != 0:
		remainder = 11 - remainder

	if remainder == 10:
		return "k"
	else:
		return String(remainder)


func is_valid_email(email: String) -> bool:
	var regex = RegEx.new()
	regex.compile("\\w+([\\.-]?\\w+)*@\\w+([\\.-]?\\w+)*(\\.\\w{2,3})+")
	if regex.search(email) == null:
		print_debug("Isn't a valid email address!")
		return false
	return true


func _on_Button_pressed() -> void:
	var name = get_node("%Name")
	var rut = get_node("%Rut")
	var email = get_node("%Email")
	var player: Dictionary = {
		"name" : name.text,
		"rut" : get_node("%Rut").clean_rut(rut.text),
		"email" : email.text
	}

	if not is_valid_name(player.name):
		show_error_message("Ingresa un nombre completo valido por favor!")
		return

	if not is_valid_rut(player.rut):
		show_error_message("Ingresa un RUT valido por favor!")
		return

	if not is_valid_email(player.email):
		show_error_message("Ingresa un email valido por favor!")
		return

	emit_signal("input_validated", player)


func show_error_message(message: String) -> void:
	var popup = get_node("%PopupDialog")
	popup.get_node("ErrorMessage").text = message
	popup.popup()
	popup.focus_mode = Control.FOCUS_ALL
	popup.grab_focus()


func _on_PopupDialog_gui_input(event: InputEvent) -> void:
	var popup = get_node("%PopupDialog")
	if popup.visible and event.is_pressed():
		popup.call_deferred("hide")


func _on_text_entered(_new_text: String) -> void:
	call_deferred("_on_Button_pressed")
