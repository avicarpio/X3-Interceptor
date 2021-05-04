#version 330
 
uniform mat4 u_mvp;

//out vec3 v_color;

in vec3 a_vertex;
in vec3 a_normals;
in vec2 a_uv;
out vec2 v_uv;
out vec3 v_normals;

void main(){
	v_uv = a_uv;
	v_normals = a_normals;

	//position of the vertex
	gl_Position = u_mvp * vec4(a_vertex, 1.0);
	
}
