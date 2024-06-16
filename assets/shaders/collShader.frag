uniform sampler2D collMap;
uniform vec2 resolution;
uniform vec2 u_position;

bool isIn(vec2 pos){
    vec4 color = texture2D(collMap, pos);
    if(color.x*255 <= 50)
    {
        return false;
    }
    else{
        return true;
    }
}

float dist(vec2 pt1, vec2 pt2){
return sqrt((pt1.y-pt2.y)*(pt1.y-pt2.y)+(pt1.x-pt2.x)*(pt1.x-pt2.x));
}

bool canReach(vec2 start, vec2 destination){
    vec2 stDest = destination-start;
    for(int iter = 0;iter<200;iter++){
        vec2 checkPos = start+stDest*(float(iter)/200.);
        if(isIn(checkPos)){
            return false;
        }
    }
    return true;
}

void main() {
    vec2 st = gl_FragCoord.xy/resolution.xy;
    st.y =0.261-st.y;
    st+=(u_position-vec2(1920/2,1080/2))/resolution.xy;
    vec3 color;

    float fadeStart = 500;
    float fadeEnd =900;
    float pD = dist(u_position, gl_FragCoord.xy+(u_position-vec2(1920/2,1080/2)));


    if(pD<=fadeEnd){
        if(canReach(st,u_position/resolution.xy))
        {
            if(pD>=fadeStart){
                gl_FragColor = vec4(0,0,0,(pD-fadeStart)/(fadeEnd-fadeStart));
            }
            else{
                 gl_FragColor = vec4(0,0,0,0);
            }
        }
        else{
             if(pD>=fadeStart){
                 gl_FragColor = vec4(0,0,0,(pD-fadeStart)/(fadeEnd-fadeStart)+0.5);
             }
             else{
                  gl_FragColor = vec4(0,0,0,0.5);
             }

        }
    }
    else{
        gl_FragColor = vec4(0,0,0,1);
    }

}