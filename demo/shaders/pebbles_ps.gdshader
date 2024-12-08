shader_type particles;

uniform float num_particles;

const float circle_radius = 0.5; 

const vec3 base_color = vec3(1.0, 1.0, 1.0);

#include "res://shaders/helpers.gdshaderinc"

// TRANSFORM[3].xyz is starting position/orientation in this function
// VELOCITY
// COLOR
void start(){
    float u = pseudo_random_from_inputs(float(INDEX), 0.23678); // Random angle factor
    float v = pseudo_random_from_inputs(float(INDEX), 0.6321); // Random radius factor

    // calculate starting position
    float theta = u * 2.0 * PI;       // Random angle
    float r = sqrt(v) * circle_radius; // Random radius within the disk (sqrt ensures uniform distribution)
	float phase = pseudo_random_from_inputs(float(INDEX), 0.92857) * 2.0 * PI;
	
   
    vec3 position = vec3(r * cos(theta), 0.0, r * sin(theta));

    // Assign random initial horizontal velocity 
    vec3 velocity = vec3(r * 0.5 * pseudo_random_from_inputs(float(INDEX), 0.98765) - 0.5, 0.0f, r * 0.5 * pseudo_random_from_inputs(float(INDEX), 0.54321) - 0.5);

	// calculated above to position the particles at their 'birth' location!
    TRANSFORM[3].xyz = position;

    COLOR = vec4(base_color, 1.0);

	// EMISSION_TRANSFORM is the transformation for the GPUParticles3D Node
	TRANSFORM = EMISSION_TRANSFORM * TRANSFORM; // if you want the transform to be in local space rather than working in world space

	CUSTOM.xyz = vec3(velocity.x, 0.0f, velocity.z);
	CUSTOM.w = LIFETIME + phase;
}

void process(){
}