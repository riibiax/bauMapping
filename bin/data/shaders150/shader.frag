#version 150

#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D maskTex;

void main(void)
{
    vec2 pos = gl_PointCoord;
    
    vec4 src = texture2DRect(tex0, pos);
    vec4 gTxt = texture2DRect(tex1, pos);
    vec4 mask = texture2DRect(maskTex, pos);
    
    vec4 color = vec4(0,0,0,0);
    color = mix(color, src, mask.r );
    color = mix(color, gTxt, mask.g );
    // color=mix(color,texture2D(tex, gl_TexCoord[0].st) * gl_Color, mask.b);
    
    fragColor = color;
}
