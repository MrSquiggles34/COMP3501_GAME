shader_type spatial;

// START -- DO NOT CHANGE -- YOU WILL GET A ZERO
render_mode skip_vertex_transform; // self-explanitory
render_mode unshaded; // turns off environment lighting
// END -- DO NOT CHANGE -- YOU WILL GET A ZERO

uniform vec3 color_in;

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = (PROJECTION_MATRIX * VIEW_MATRIX * (MODEL_MATRIX * vec4(VERTEX, 1.0)));
}

void fragment() {
	// Called for every pixel the material is visible on.	
    ALBEDO = color_in;
}

void light() {
	// Called for every pixel for every light affecting the material.
	// Uncomment to replace the default light processing function with this one.
}
