#version 410

//uniform sampler2D tex;


uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect maskTex;

in vec2 vTexCoord;
//in vec4 colorVarying;

out vec4 vFragColor;

void main(void)
{
    vec2 pos = vTexCoord;
    
    vec4 src = texture(tex0, pos);
    vec4 gTxt = texture(tex1, pos);
    vec4 mask = texture(maskTex, pos);
    
    vec4 color = vec4(0,0,0,0);
    color = mix(color, src, mask.r );
    color = mix(color, gTxt, mask.g );

    vFragColor = color;
    
    //texture(tex, gl_PointCoord) * colorVarying;
}
