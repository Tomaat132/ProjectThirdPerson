#version 330

uniform sampler2D colorMap;
uniform vec3 light;
uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform vec3 camera;
uniform vec4 outlineColor;
uniform float alpha;
uniform float time;

in vec2 texCoord;

in vec3 aVertex;
in vec3 aNormal;

out vec4 fragment; // to screenbuffer

void main() {
    float specular = 1f;
    vec4 wLight  = vec4( light, 1.0f );
    vec4 wCamera  = vec4( camera, 1.0f );
	vec4 wVertex = model * vec4( aVertex, 1.0f ); // transform vertex to world
	vec4 wNormal = model * vec4( aNormal, 0.0f ); // rotate normal to world, note the 0.0 for w. Only works with symetric scaling

    float diffused =  0.3 + 0.7 * dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex
    specular =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex
    gl_FrontLightProduct[0].diffuse * max(dot(N, L))
    vec4 cameraDirection = wCamera - wVertex;

    vec2 coordOffset = vec2( 0.01 * sin( 3 * time ), 0.04 * time );

    fragment = diffused * texture( colorMap, texCoord + coordOffset ) * vec4(1.0, 1.0, 1.0, alpha);
}
