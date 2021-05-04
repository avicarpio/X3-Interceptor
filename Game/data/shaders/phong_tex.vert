#version 330

in vec3 a_vertex;
in vec3 a_normal;
in vec2 a_uv;

uniform mat4 u_mvp;
uniform mat4 u_normal_matrix;
uniform vec3 u_cam_pos;

out vec3 v_normal; 
out vec3 v_camera;
out vec2 v_uv;

void main()
{
	v_uv = a_uv;

	//calculate vector to camera
	v_camera = u_cam_pos - a_vertex; 

	//multiply normal by cam space normal matrix
	v_normal = (u_normal_matrix * vec4( a_normal, 1.0)).xyz;

	//calculate the position of the vertex using the matrices
	gl_Position = u_mvp * vec4( a_vertex, 1.0 );

}




