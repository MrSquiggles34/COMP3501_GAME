shader_type spatial;
render_mode unshaded;
render_mode skip_vertex_transform;
render_mode fog_disabled;
uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;
uniform float curvature = 10.0; // Define curvature
float random(vec2 st) {
    // Pseudo-random generator
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}
void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = vec4(VERTEX, 1.0f); // which space is this? (clip space)
	//POSITION = vec4(VERTEX * 0.75, 1.0f); // what does this do?
}
void fragment() {
    // Data Corruption Effect
    // Pseudo-random offsets for screen distortion
    float distort_intensity = 0.01; // Adjust for stronger/weaker distortion
    float random_x = (random(vec2(TIME, SCREEN_UV.y)) - 0.5) * distort_intensity * 2.0; // Random X offset
    float random_y = (random(vec2(SCREEN_UV.x, TIME)) - 0.5) * distort_intensity; // Random Y offset
    // Apply the distortion to UV coordinates
    vec2 distortion_uv = SCREEN_UV + vec2(random_x, random_y);
    // Fetch the base screen color with distortion
    vec4 distorted_pixel = texture(screen_texture, distortion_uv);
    // Add Red Highlights
    float highlight_intensity = step(0.5, random(vec2(TIME * 10.0, SCREEN_UV.x))) * 0.6; // Random red flashes
    vec3 red_highlight = vec3(1.0, 0.0, 0.0) * highlight_intensity;
    // Add Blackout Zones
    float blackout_threshold = 0.4 + 0.2 * random(vec2(SCREEN_UV * 15.0)); // Randomized blackout zones
    float blackout = step(blackout_threshold, random(vec2(SCREEN_UV * 20.0 + TIME * 5.0))); // Stripe-like blackout
    vec3 blackout_color = vec3(0.0) * blackout;
    // Combine both effects
    pixel.rgb = mix(distorted_pixel.rgb, red_highlight, 0.7); // Blend with red highlights
    pixel.rgb = mix(pixel.rgb, blackout_color, blackout);  // Apply blackout zone
    ALBEDO = pixel.rgb;
    
}
//void light() {
	//// Called for every pixel for every light affecting the material.
	//// Uncomment to replace the default light processing function with this one.
//}
// Attribution: This effect has been adapted from the one provided in the OpenGL delivery of the course. 