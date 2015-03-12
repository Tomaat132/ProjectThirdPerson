#version 330

uniform sampler2D colorMap;
uniform vec3 light;
uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform vec3 camera;
uniform vec4 outlineColor;
uniform float alpha;

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

    float diffused =  0.5 + 0.5 * dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex
    specular =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex

    vec4 cameraDirection = wCamera - wVertex;

    float toonish;
    if(diffused > 0.9)   toonish = 1;
    else if(diffused > 0.8)   toonish = 0.8;
    else if(diffused > 0.7)   toonish = 0.7;
    else if(diffused > 0.5)   toonish = 0.6;
    else if(diffused > 0.35)   toonish = 0.4;
    else if(diffused > 0.2)   toonish = 0.3;
    else toonish = 0.2;
    if(dot(wNormal, normalize(cameraDirection)) < 0.2) {
        diffused = 0.0f;
     //   if(outlineColor != 0)
        fragment = outlineColor * vec4(1.0, 1.0, 1.0, alpha);        // color for the outline
       // else fragment = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else fragment = diffused * texture( colorMap, texCoord ) * vec4(1.0, 1.0, 1.0, alpha);

	//fragment = diffused * vec4(1.0, 1.0, 1.0, 0.75);

}
