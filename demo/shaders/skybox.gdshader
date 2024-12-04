shader_type spatial;

render_mode unshaded, cull_front, skip_vertex_transform; 

uniform sampler2D sky_texture;

void fragment() {
    ALBEDO = texture(sky_texture, UV).rgb;
}
