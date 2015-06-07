#version 430

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 out_color;

uniform layout(location= 10) sampler2D sampler;

void main()
{
	//Map the texture to UV coordinates
	vec4 textureColor = texture(sampler, fragmentUV);
	
	out_color = fragmentColor * textureColor;
}