
shader_type spatial;

// START -- DO NOT CHANGE -- YOU WILL GET A ZERO
render_mode skip_vertex_transform; // self-explanatory
render_mode unshaded; // turns off environment lighting
// END -- DO NOT CHANGE -- YOU WILL GET A ZERO

// you can give a hint to uniforms, but do make sure that you are passing them correctly to the shader.
uniform vec3 color_in; // = vec3(1, 0, 0);
// TODO add uniform for light position! It must move around the scene, not be stationary. 
uniform vec3 light_position;     
// TODO add uniform for specular power!
uniform float specular_power;    

varying smooth vec3 position_interp; // what does "smooth" do? can you think of a situation where you would want a 'varying' to be "flat?"

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = (PROJECTION_MATRIX * VIEW_MATRIX * (MODEL_MATRIX * vec4(VERTEX, 1.0)));
    
	// VIEW SPACE FOR LIGHTING CALCULATIONS !
    position_interp = (VIEW_MATRIX * (MODEL_MATRIX * vec4(VERTEX, 1.0))).xyz;
	
   	NORMAL = vec3(MODELVIEW_NORMAL_MATRIX * NORMAL);
}

void fragment() {
	// Called for every pixel the material is visible on.
	vec4 pixel; 

	pixel = vec4(color_in, 1.0f);

	vec4 light_color = vec4(1, 1, 1, 1);
	
	vec3 view_position = vec3(0, 0, 0); // origin in view space
	
	vec3 vv = normalize(view_position - position_interp); // view direction
	vec3 lv = normalize(light_position - position_interp); // light direction, object position as origin
	vec3 h = normalize((vv+lv)/2.0f); // halfway vector -- note /2 pointless, just there for clarity
	vec3 n = normalize(NORMAL); // must normalize interpolated normal
	vec3 r = -lv + 2.0f * dot(lv,n) * n;
	// n.x += 0.2*sin(uv_interp.x*500); // messing with normal to show effect
	// n  = normalize(n); // renormalize now that the vector is not a unit vector

	float diffuse = dot(n,lv); // N.L -- anything wrong with this line?
	float spec = max(0.0,dot(r,vv)); // cannot be negative - BLINN-PHONG

	spec = pow(spec, specular_power); // specular power -- instead of hardcoded number, should have uniform here too
	vec4 ambcol = pixel; // ambient light -- in this case red, could be anything; should make uniform

	//spec = 0.0f;  // turn off specular
	//diffuse = 0.0f; // turn off diffuse
    float amb = 0.7; // ambient coefficient
	
    // Use variable "pixel", surface color, to help determine fragment color
    ALBEDO = (light_color*pixel*diffuse +
	   light_color*vec4(1,1,1,1)*spec + // specular might not be colored
	   light_color*pixel*amb).xyz; // ambcol not used, could be included here
		
   //ALBEDO = vec4(1,position_interp.x,0,1); // try this -- why does it have the effect it does?

}
