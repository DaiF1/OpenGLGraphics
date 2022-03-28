#version 460 core

out vec4 FragColor;
in vec4 fColor;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float rect(vec2 st, vec2 size, float blur) {
    size = vec2(0.5) - size*0.5;
    vec2 b = vec2(blur * 0.5);
    vec2 uv = smoothstep(size, size + b, st);
    uv *= smoothstep(size, size + b, vec2(1.0) - st);
    return uv.x * uv.y;
}

float cross(vec2 st, float size) {
    return rect(st, vec2(size, size/4.0), 0.01) + 
        rect(st, vec2(size/4.0, size), 0.01);
}

vec2 rotate2d(vec2 st, float angle) {
    st -= 0.5;
    st = mat2(cos(angle), -sin(angle),
               sin(angle), cos(angle)) * st;
    st += 0.5;
    return st;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);

    vec2 mouse = u_mouse.xy / u_resolution.xy;
    float angle = atan(mouse.y - 0.5, mouse.x - 0.5);
    st = rotate2d(st, angle);

    color = vec3(cross(st, 0.5));

    FragColor = vec4(color,1.0);
}
