extends LineEdit


var previous_text: String = ""


func _on_Rut_text_changed(_new_text: String) -> void:
	var old_pos = caret_position
	if text.length() > 12:
		text = previous_text
		old_pos = old_pos - 2
	text = pretty_rut(text)
	caret_position = old_pos + 1
	previous_text = text


func clean_rut(rut: String) -> String:
	rut = rut.strip_escapes()
	rut = rut.strip_edges(true, true)
	rut = rut.to_lower()
	rut = rut.replace(".", "")
	rut = rut.replace("-", "")

	var rut_temp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)

	var regex = RegEx.new()
	regex.compile("\\D")
	rut_temp = regex.sub(rut_temp, "", true)

	regex.compile("[^kK\\d]")
	verifier = regex.sub(verifier, "", true)

	rut = rut_temp + verifier

	return rut


func pretty_rut(rut: String) -> String:
	rut = clean_rut(rut)

	var rut_temp: String = rut.substr(0, rut.length() - 1)
	var verifier: String = rut.substr(rut.length() - 1, 1)

	var regex = RegEx.new()
	regex.compile("[^kK\\d]")
	verifier = regex.sub(verifier, "", true)

	var byte_array = rut_temp.to_utf8()
	byte_array.invert()

	var new_byte_array: PoolByteArray = PoolByteArray()
	var i = 1
	for symbol in byte_array:
		new_byte_array.append(symbol)
		if i == 3:
			new_byte_array.append(".".to_utf8()[0])
			i = 0
		i = i + 1
	if new_byte_array.size() > 0 and new_byte_array[new_byte_array.size() - 1] == ".".to_utf8()[0]:
		new_byte_array.resize(new_byte_array.size() - 1)

	new_byte_array.invert()
	rut_temp = new_byte_array.get_string_from_utf8()

	if rut_temp.length() == 0 and verifier.length() > 0:
		rut_temp = verifier
	elif rut_temp.length() > 0 and verifier.length() > 0:
		rut_temp = rut_temp + "-" + verifier

	return rut_temp
