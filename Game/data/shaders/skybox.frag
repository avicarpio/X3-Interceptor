#version 330
 
in vec2 v_uv;
in vec3 v_normals;

out vec4 fragColor;

uniform vec3 u_light_dir;
uniform vec3 u_color;
uniform sampler2D u_texture;

void main (void){
	//vec3 L = normalize(u_light_dir);
	//float NdotL = max( dot(v_normals,L) , 0.0 );

	vec4 texture_color = texture2D (u_texture, v_uv);
	fragColor = vec4 (texture_color.xyz, 1.0);
	//fragColor = vec4 (v_normals, 1.0);
	//vec3 final_color = texture_color.xyz * NdotL;
	//fragColor = vec4(final_color, 1.0);
}

