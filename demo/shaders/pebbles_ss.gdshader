shader_type spatial;



render_mode blend_mix;
//render_mode alpha_to_coverage;
// DO NOT CHANGE -- YOU WILL GET A 0 -- YOU MUST INCLUDE THIS IN YOUR OTHER SHADERS FOR THIS ASSIGNMENT
render_mode unshaded; // without this line, the world will attempt to apply lighting to the quad, which will make *everything* look darker (or lighter, depending)
render_mode skip_vertex_transform;
// END (DO NOT CHANGE -- YOU WILL GET A 0)

uniform sampler2D texture_image;
uniform float num_particles;

varying float timestep;
varying float particle_id;
varying float lifespan;

const float plane_height = 0.0;


void vertex() {    
    // Define particle ID
    particle_id = COLOR.r; // Use particle ID to stagger motion slightly

    // Define time normalized to particle's lifetime
    float t = mod(TIME / INSTANCE_CUSTOM.w, 1.0); 
    
    // launch motion: quadratic curve 
    float launch_height = 0.3; 
    float vertical_offset = launch_height * 4.0 * 2.0 * t * (1.0 - 2.0*t); 
    
	vertical_offset = max(vertical_offset, plane_height);
    
	// Horizontal velocity 
    vec3 velocity = INSTANCE_CUSTOM.xyz; 
    vec3 horizontal_offset = velocity * t; 
	
    // Combine vertical and horizontal motion to create projectile motion
    vec3 offset = horizontal_offset + vec3(0.0, vertical_offset, 0.0);
    
	// BILLBOARDING
    MODELVIEW_MATRIX = VIEW_MATRIX * mat4(INV_VIEW_MATRIX[0], INV_VIEW_MATRIX[1], INV_VIEW_MATRIX[2], vec4(offset, 0.0) + MODEL_MATRIX[3]);
    MODELVIEW_NORMAL_MATRIX = mat3(MODELVIEW_MATRIX);

    //// Called for every vertex the material is visible on.
    POSITION = (PROJECTION_MATRIX * MODELVIEW_MATRIX * vec4(VERTEX, 1.0));
	
    lifespan = INSTANCE_CUSTOM.w;
    timestep = t;
}


// Set color of dirt
const vec3 object_color = vec3(0.3, 0.1, 0.05);

void fragment() {
    // Get pixel from texture
    vec2 uv = UV;
    uv.y *= 1.0f;

    vec4 outval = texture(texture_image, uv);
    vec3 color = object_color;

    // Use texture alpha for transparency
    float alpha = outval.a * COLOR.a;

    // Adjust specified object color according to the grayscale texture value
    outval = vec4(outval.r*color.r, outval.g*color.g, outval.b*color.b, sqrt(sqrt(outval.r))*COLOR.a);

    // Set output fragment color
    ALBEDO = outval.rgb * outval.a;
}
