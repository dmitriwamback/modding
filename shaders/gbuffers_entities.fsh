#version 120

#include "tools.glsl"

varying vec4 uv;
varying vec3 normal;
varying vec4 color;

uniform sampler2D texture;

void main() {
    float sharpen_factor = 8.0;

    vec4 col4 = texture2D(texture, uv.xy) * color;
    col4.rgb = hdr(col4.rgb, 1.2);

    gl_FragData[0] = col4;
}