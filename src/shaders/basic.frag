#version 460 core

out vec4 FragColor;
in vec4 fColor;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float circle(float radius, vec2 position, float blurFact)
{
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    
    vec2 stToPos = st - position;
    float d = dot(stToPos, stToPos) * 4.0;
    float d2 = radius * blurFact;
    return smoothstep(d - d2, d + d2, radius);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
	st = (st * vec2(2.0)) - vec2(1.0);
    
    float radius = 0.364;
    float blur = 0.010;
    vec2 position = vec2(0.360,0.580);
    float anim = sin(u_time * 10.0) / 50.;
    float c1 = circle(radius + anim, position, blur);
    vec3 color1 = vec3(0.792,0.508,1.000);
    
    float radius1 = 0.092;
    float blur1 = 0.034;
    vec2 position1 = vec2(0.670,0.320);
    float anim1 = sin(u_time * 10.0 + 5.0) / 100.0;
    float c2 = circle(radius1 + anim1, u_mouse.xy/u_resolution.xy, blur1);
    vec3 color2 = vec3(0.775,1.000,0.144);
    
    vec3 color = vec3((c1 * color1) + (c2 * color2));

    FragColor = vec4(color,1.0);
}
