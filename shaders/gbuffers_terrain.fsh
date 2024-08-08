#version 120

#include "tools.glsl"

varying vec4 uv;
varying vec3 normal;
varying vec4 color;

uniform sampler2D texture;

uniform mat4 gbuffersModelView;
varying vec3 worldPosition;

vec3 getCameraPosition() {
    return vec3(-gbuffersModelView[3][0], -gbuffersModelView[3][1], -gbuffersModelView[3][2]);
}

void main() {

    vec3 cameraPosition = getCameraPosition();
    float d = (100 - length(cameraPosition - worldPosition))/100;

    vec4 col4 = texture2D(texture, uv.xy) * color;
    col4.rgb = hdr(col4.rgb, 1.2);

    gl_FragData[0] = col4;
}