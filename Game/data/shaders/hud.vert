in vec3 a_vertex;

in vec2 a_uv;

varying out vec2 v_uv;

uniform mat4 u_mvp;

void main(){
	gl_Position = u_mvp * vec4(a_vertex, 1.0);
	
	v_uv = a_uv;
}