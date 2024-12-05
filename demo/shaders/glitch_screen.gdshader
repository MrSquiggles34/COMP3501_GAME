shader_type spatial;

render_mode unshaded; // without this line, the world will attempt to apply lighting to the quad, which will make *everything* look darker (or lighter, depending)
render_mode skip_vertex_transform;
render_mode fog_disabled; // we aren't going to use fog, but putting this here anyways so that you know it would be necessary

uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;

#include "res://shaders/helpers.gdshaderinc"

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = vec4(VERTEX, 1.0f);
}

// this shader just shows the screen; it's see-through completely aka there is no effect
void fragment() {
	vec4 pixel = textureLod(screen_texture, SCREEN_UV, 0.0);
	vec2 pos = SCREEN_UV;

	// Blur/Glow effect
	float x_shift = 1.0/VIEWPORT_SIZE.x;
	float y_shift = 1.0/VIEWPORT_SIZE.y;

	vec4 n_pixel = textureLod(screen_texture, pos + vec2(0.0,-y_shift), 0.0);
	vec4 ne_pixel = textureLod(screen_texture, pos + vec2(x_shift,-y_shift), 0.0);
	vec4 e_pixel = textureLod(screen_texture, pos + vec2(x_shift,0.0), 0.0);
	vec4 se_pixel = textureLod(screen_texture, pos + vec2(x_shift,y_shift), 0.0);
	vec4 s_pixel = textureLod(screen_texture, pos + vec2(0.0,y_shift), 0.0);
	vec4 sw_pixel = textureLod(screen_texture, pos + vec2(-x_shift,y_shift), 0.0);
	vec4 w_pixel = textureLod(screen_texture, pos + vec2(-x_shift,0.0), 0.0);
	vec4 nw_pixel = textureLod(screen_texture, pos + vec2(-x_shift,-y_shift), 0.0);

	float n = 4.0;
	for (float i=1.0; i<n; i+=1.0){
		x_shift = x_shift * i;
		y_shift = y_shift * i;
		n_pixel = n_pixel + textureLod(screen_texture, pos + vec2(0.0,-y_shift), 0.0);
		ne_pixel = ne_pixel + textureLod(screen_texture, pos + vec2(x_shift,-y_shift), 0.0);
		e_pixel = e_pixel + textureLod(screen_texture, pos + vec2(x_shift,0.0), 0.0);
		se_pixel = se_pixel + textureLod(screen_texture, pos + vec2(x_shift,y_shift), 0.0);
		s_pixel = s_pixel + textureLod(screen_texture, pos + vec2(0.0,y_shift), 0.0);
		sw_pixel = sw_pixel + textureLod(screen_texture, pos + vec2(-x_shift,y_shift), 0.0);
		w_pixel = w_pixel + textureLod(screen_texture, pos + vec2(-x_shift,0.0), 0.0);
		nw_pixel = nw_pixel + textureLod(screen_texture, pos + vec2(-x_shift,-y_shift), 0.0);
	}

	pixel = pixel+n_pixel+ne_pixel+e_pixel+se_pixel+s_pixel+sw_pixel+w_pixel+nw_pixel;
	pixel = pixel / (n*n*2.0);

	// Moving distortion
	float circle = 1.0 - abs(sin(mod(TIME*0.25,pi_over_two)));
	if((pos.y > circle && pos.y < circle + 0.1) || 
	(pos.y > circle + 0.2 && pos.y < circle + 0.23) ||  
	(pos.y > circle + 0.35 && pos.y < circle + 0.32) || 
	(pos.y > circle + 0.46 && pos.y < circle + 0.51) ||
	(pos.y > circle + 0.56 && pos.y < circle + 0.57) ||  
	(pos.y > circle + 0.6 && pos.y < circle + 0.65) ||
	(pos.y > circle + 0.78 && pos.y < circle + 0.82) ||
	(pos.y > circle + 0.9 && pos.y < circle + 0.93)){
		float offset  = 0.025*(sin(25.0*pos.y));
    	pos.x = pos.x + offset;
	
    	pixel = texture(screen_texture, pos) ;
		pixel = pixel*0.9;
	}
	
	ALBEDO = pixel.rgb;
}
