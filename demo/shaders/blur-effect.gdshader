shader_type spatial;

render_mode unshaded; 
render_mode skip_vertex_transform;
render_mode fog_disabled; 

uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;

const float wave_amplitude = 0.01; 
const float wave_frequency = 5.0;  
const float wave_speed = 2.0;

const float kernel[9] = float[](
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0
);

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = vec4(VERTEX, 1.0f); 
}

void fragment() {
    
    // Waving displacement
    float diagonal = SCREEN_UV.x + SCREEN_UV.y; 
    float wave_displacement = wave_amplitude * sin(diagonal * wave_frequency + TIME * wave_speed);

    // Apply displacement to UV coordinates
    vec2 displaced_uv = SCREEN_UV + vec2(wave_displacement, wave_displacement);

	// Determine the size of a texel in UV coordinates
    vec2 texel_size = 1.0 / vec2(textureSize(screen_texture, 0));

    float convoluted_color = 0.0;
    
    // Offset for area of 3 pixels
    const vec2 offsets[9] = vec2[](
        vec2(-1.0, -1.0), vec2(0.0, -1.0), vec2(1.0, -1.0),
        vec2(-1.0,  0.0), vec2(0.0,  0.0), vec2(1.0,  0.0),
        vec2(-1.0,  1.0), vec2(0.0,  1.0), vec2(1.0,  1.0)
    );

    for (int i = 0; i < 9; i++) {
        
        // Get the pixels surrounding a pixel
        vec2 offset = offsets[i] * texel_size;
        vec4 pixel = textureLod(screen_texture, displaced_uv + offset, 0.0);

        // Convert the pixel to grayscale
        float luminance = dot(pixel.rgb, vec3(0.3, 0.6, 0.1));

        // Multiply weight by pixel value
        convoluted_color += luminance * kernel[i];
    }

    // Set the final grayscale result
    vec3 grayscale_color = vec3(convoluted_color);
    ALBEDO = grayscale_color;
}



//void light() {
	//// Called for every pixel for every light affecting the material.
	//// Uncomment to replace the default light processing function with this one.
//}

// Attribution: This effect has been adapted from the one provided in the OpenGL delivery of the course. 