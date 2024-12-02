shader_type spatial;

render_mode unshaded; 
render_mode skip_vertex_transform;
render_mode fog_disabled; 

uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = vec4(VERTEX, 1.0f); 
}

void fragment() {
    vec4 pixel = textureLod(screen_texture, SCREEN_UV, 0.0); // the third argument has to do with the mip-map level
    ALBEDO = pixel.rgb;
}