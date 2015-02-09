#version 330


in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform vec3 light; // point light in world

out float diffuse; // for diffuse light
out vec2 texCoord; // forward uv

void main() {
	vec4 wLight  = vec4( light, 1.0f );
	vec4 wVertex = model * vec4( vertex, 1.0f ); // transform vertex to world
	vec4 wNormal = model * vec4( normal, 0.0f ); // rotate normal to world, note the 0.0 for w. Only works with symetric scaling

	diffuse =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex

	gl_Position = projection * view * wVertex;

	texCoord = uv; // forward to fs
}
