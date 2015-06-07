#version 430

in layout(location=0) vec2 in_vertexPosition;
in layout(location=1) vec4 in_vertexColor;
in layout(location=2) vec2 in_vertexUV;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform layout(location = 11) mat4 mainCameraMatrix;

void main()
{
	gl_Position = (mainCameraMatrix * vec4(in_vertexPosition, 0.0, 1.0)); 
	
	fragmentColor = in_vertexColor;
	fragmentPosition = in_vertexPosition;
	fragmentUV = vec2(in_vertexUV.x, 1-in_vertexUV.y);
}
