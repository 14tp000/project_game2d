uniform float filled;
uniform vec2 start;
uniform vec2 end;
uniform vec4 fillColor;
uniform vec4 bgColor;



void main() {
    vec2 st = gl_FragCoord.xy;
    float sizeX = end.x-start.x;
    if(st.x>start.x&&st.x<end.x&&st.y>start.y&&st.y<end.y){
        if(st.x<start.x+sizeX*filled){
        gl_FragColor = fillColor;
        }
        else{
        gl_FragColor = bgColor;
        }
    }
    else{
         gl_FragColor = vec4(0.170,0.170,0.170,0.000);
    }
}