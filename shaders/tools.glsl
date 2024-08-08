vec3 desaturate(vec3 col) {
    return col * 2;
}

vec3 amplify(vec3 col) {
    return col * 2;
}

vec3 hdr(vec3 col, float exposure) {

    vec3 result = vec3(0);
    result.rgb = vec3(1.0) - exp(-col.rgb * exposure);
    result.rgb = pow(result.rgb, vec3(1.0 / 1.2));

    return result;
}

vec4 sharpen(sampler2D texture, float sharpen_factor, vec4 color, vec4 uv) {

    float block_offset    = 0.000075;

    vec2 uvOffset = vec2(0, 0);
    vec4 center_albedo  = texture2D(texture, uv.xy + uvOffset) * color;

    vec4 up_albedo      = texture2D(texture, uv.xy + uvOffset + vec2( 0,            block_offset)) * color;
    vec4 down_albedo    = texture2D(texture, uv.xy + uvOffset + vec2(-block_offset, 0))            * color;
    vec4 left_albedo    = texture2D(texture, uv.xy + uvOffset + vec2( block_offset, 0))            * color;
    vec4 right_albedo   = texture2D(texture, uv.xy + uvOffset + vec2( 0,           -block_offset)) * color;

    vec4 col4 = (1.0 + 4.0 * sharpen_factor)*center_albedo - sharpen_factor*(up_albedo + down_albedo + left_albedo + right_albedo);
    col4.rgb = col4.rgb * 1.3;
    return col4;
}