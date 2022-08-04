shader_type canvas_item;

const float PI = 3.14159;

uniform vec2 resolution = vec2(1024.0, 576.0);

uniform bool show_curve = false;
uniform bool show_vignette = false;
uniform bool show_horizontal_scan_lines = true;
uniform bool show_vertical_scan_lines = false;
uniform bool gray_scale = false;

uniform float curvature_x_amount : hint_range(3.0, 15.0, 0.01) = 6.0; 
uniform float curvature_y_amount : hint_range(3.0, 15.0, 0.01) = 6.0;
uniform vec4 corner_color : hint_color = vec4(0.0, 0.0, 0.0, 1.0);

uniform float vignette_size : hint_range(1, 300, 0.1) = 4.0;
uniform float vignette_opacity : hint_range(0.0, 1.0, 0.01) = 1.0;

const float brightness = 3.0;

vec2 uv_curve(vec2 uv) {
	if (show_curve) {
		uv = uv * 2.0 - 1.0;
		vec2 offset = abs(uv.yx) / vec2(curvature_x_amount, curvature_y_amount);
		uv = uv + uv * offset * offset;
		uv = uv * 0.5 + 0.5;
	}
	return uv;
}

void fragment() {
	vec2 screen_uv = uv_curve(SCREEN_UV);
	vec3 color = texture(SCREEN_TEXTURE, screen_uv).rgb;
	
	if (show_horizontal_scan_lines || show_vertical_scan_lines) {
		color.r = texture(SCREEN_TEXTURE, uv_curve(SCREEN_UV) + vec2(SCREEN_PIXEL_SIZE.x * 0.0), 0.0).r;
		color.g = texture(SCREEN_TEXTURE, uv_curve(SCREEN_UV) + vec2(SCREEN_PIXEL_SIZE.x * 0.0), 0.0).g;
		color.b = texture(SCREEN_TEXTURE, uv_curve(SCREEN_UV) + vec2(SCREEN_PIXEL_SIZE.x * 0.0), 0.0).b;
	}
	
	if (show_vignette) {
		float vignette = UV.x * UV.y * (1.0 - UV.x) * (1.0 - UV.y);
		vignette = clamp(pow((resolution.x / vignette_size) * vignette, vignette_opacity), 0.0, 1.0);
		color *= vignette;
	}
	
	if (show_horizontal_scan_lines) {
		float s = sin(uv_curve(SCREEN_UV).y * resolution.y / 2.0 * PI);
		s = (s * 0.5 + 0.5) * 0.9 + 0.1;
		vec4 scan_line = vec4(vec3(pow(s, 0.25)), 1.0);
		color *= scan_line.rgb;
	}
	
	if (show_vertical_scan_lines) {
		float s = sin(uv_curve(SCREEN_UV).x * resolution.x / 2.0 * PI);
		s = (s * 0.5 + 0.5) * 0.9 + 0.1;
		vec4 scan_line = vec4(vec3(pow(s, 0.25)), 1.0);
		color *= scan_line.rgb;
	}
	
	if (show_curve) {
		if (screen_uv.x < 0.0 || screen_uv.x > 1.0 || screen_uv.y < 0.0 || screen_uv.y > 1.0) {
			color = corner_color.rgb;
		}
	}

	if (gray_scale) {
		float avg = (color.r + color.g + color.b) / brightness;
		color = vec3(avg);
	}
	COLOR = vec4(color, 1.0);
}