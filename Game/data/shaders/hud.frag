in vec3 v_camera;
in vec2 v_uv;

uniform vec3 u_light;
uniform sampler2D u_texture_diffuse;

varying out vec4 fragColor;

void main (void){

	
	

	fragColor = vec4(texture2D(u_texture_diffuse, v_uv).xyz,texture2D(u_texture_diffuse, v_uv).a);	
	
}