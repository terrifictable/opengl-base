/*
 * Credit: some guy on glslsandbox.com
 * Source: https://glslsandbox.com/e#103931.0
 */


#version 330 core


uniform float time;
uniform vec2 resolution;

uniform int u_size;
uniform int u_data[256]; // requires at least 256 bytes on gpu vram
uniform float u_anim_strength;
uniform vec2 u_text_pos;

#define CHAR_SIZE vec2(6, 7)
#define CHAR_SPACING vec2(6, 9)

#define DOWN_SCALE 2.0

vec2 res = resolution.xy / DOWN_SCALE;
vec2 start_pos = vec2(0);
vec2 print_pos = vec2(0);
vec2 print_pos_pre_move = vec2(0);
vec3 text_color = vec3(1);

/*
Top left pixel is the most significant bit.
Bottom right google pixel 6 is the least significant bit.

 ███  |
█   █ |
█   █ |  
█   █ |
███|
█   █ |
█   █ |

000000 
100010
100010  
100010
111110
100010
100010

100000
100000
100000
100
   000
100000
100000
000000

011100 (upper 21 bits)
100010 -> 011100 100010 100010 100 -> 935188
100010  
100
   010 (lower 21 bits)
111110 -> 010 111110 100010 100010 -> 780450
100010
100010

vec2(935188.0,780450.0)
*/

//Text coloring
#define HEX(i) text_color = mod(vec3(i / 65536,i / 256,i),vec3(256.0))/255.0;
#define RGB(r,g,b) text_color = vec3(r,g,b);

#define STRWIDTH(c) (c * CHAR_SPACING.x)
#define STRHEIGHT(c) (c * CHAR_SPACING.y)
#define BEGIN_TEXT(x,y) print_pos = floor(vec2(x,y)); start_pos = floor(vec2(x,y));

//Automatically generated from the sprite sheet here: http://uzebox.org/wiki/index.php?title=File:Font6x8.png
#define _ col+=char(vec2(0.0,0.0),uv);
#define _spc col+=char(vec2(0.0,0.0),uv)*text_color;
#define _exc col+=char(vec2(276705.0,32776.0),uv)*text_color;
#define _quo col+=char(vec2(1797408.0,0.0),uv)*text_color;
#define _hsh col+=char(vec2(10738.0,1134484.0),uv)*text_color;
#define _dol col+=char(vec2(538883.0,19976.0),uv)*text_color;
#define _pct col+=char(vec2(1664033.0,68006.0),uv)*text_color;
#define _amp col+=char(vec2(545090.0,174362.0),uv)*text_color;
#define _apo col+=char(vec2(798848.0,0.0),uv)*text_color;
#define _lbr col+=char(vec2(270466.0,66568.0),uv)*text_color;
#define _rbr col+=char(vec2(528449.0,33296.0),uv)*text_color;
#define _ast col+=char(vec2(10471.0,1688832.0),uv)*text_color;
#define _crs col+=char(vec2(4167.0,1606144.0),uv)*text_color;
#define _per col+=char(vec2(0.0,1560.0),uv)*text_color;
#define _dsh col+=char(vec2(7.0,1572864.0),uv)*text_color;
#define _com col+=char(vec2(0.0,1544.0),uv)*text_color;
#define _lsl col+=char(vec2(1057.0,67584.0),uv)*text_color;
#define _0 col+=char(vec2(935221.0,731292.0),uv)*text_color;
#define _1 col+=char(vec2(274497.0,33308.0),uv)*text_color;
#define _2 col+=char(vec2(934929.0,1116222.0),uv)*text_color;
#define _3 col+=char(vec2(934931.0,1058972.0),uv)*text_color;
#define _4 col+=char(vec2(137380.0,1302788.0),uv)*text_color;
#define _5 col+=char(vec2(2048263.0,1058972.0),uv)*text_color;
#define _6 col+=char(vec2(401671.0,1190044.0),uv)*text_color;
#define _7 col+=char(vec2(2032673.0,66576.0),uv)*text_color;
#define _8 col+=char(vec2(935187.0,1190044.0),uv)*text_color;
#define _9 col+=char(vec2(935187.0,1581336.0),uv)*text_color;
#define _col col+=char(vec2(195.0,1560.0),uv)*text_color;
#define _scl col+=char(vec2(195.0,1544.0),uv)*text_color;
#define _les col+=char(vec2(135300.0,66052.0),uv)*text_color;
#define _equ col+=char(vec2(496.0,3968.0),uv)*text_color;
#define _grt col+=char(vec2(528416.0,541200.0),uv)*text_color;
#define _que col+=char(vec2(934929.0,1081352.0),uv)*text_color;
#define _ats col+=char(vec2(935285.0,714780.0),uv)*text_color;
#define _A col+=char(vec2(935188.0,780450.0),uv)*text_color;
#define _B col+=char(vec2(1983767.0,1190076.0),uv)*text_color;
#define _C col+=char(vec2(935172.0,133276.0),uv)*text_color;
#define _D col+=char(vec2(1983764.0,665788.0),uv)*text_color;
#define _E col+=char(vec2(2048263.0,1181758.0),uv)*text_color;
#define _F col+=char(vec2(2048263.0,1181728.0),uv)*text_color;
#define _G col+=char(vec2(935173.0,1714334.0),uv)*text_color;
#define _H col+=char(vec2(1131799.0,1714338.0),uv)*text_color;
#define _I col+=char(vec2(921665.0,33308.0),uv)*text_color;
#define _J col+=char(vec2(66576.0,665756.0),uv)*text_color;
#define _K col+=char(vec2(1132870.0,166178.0),uv)*text_color;
#define _L col+=char(vec2(1065220.0,133182.0),uv)*text_color;
#define _M col+=char(vec2(1142100.0,665762.0),uv)*text_color;
#define _N col+=char(vec2(1140052.0,1714338.0),uv)*text_color;
#define _O col+=char(vec2(935188.0,665756.0),uv)*text_color;
#define _P col+=char(vec2(1983767.0,1181728.0),uv)*text_color;
#define _Q col+=char(vec2(935188.0,698650.0),uv)*text_color;
#define _R col+=char(vec2(1983767.0,1198242.0),uv)*text_color;
#define _S col+=char(vec2(935171.0,1058972.0),uv)*text_color;
#define _T col+=char(vec2(2035777.0,33288.0),uv)*text_color;
#define _U col+=char(vec2(1131796.0,665756.0),uv)*text_color;
#define _V col+=char(vec2(1131796.0,664840.0),uv)*text_color;
#define _W col+=char(vec2(1131861.0,699028.0),uv)*text_color;
#define _X col+=char(vec2(1131681.0,84130.0),uv)*text_color;
#define _Y col+=char(vec2(1131794.0,1081864.0),uv)*text_color;
#define _Z col+=char(vec2(1968194.0,133180.0),uv)*text_color;
#define _lsb col+=char(vec2(925826.0,66588.0),uv)*text_color;
#define _rsl col+=char(vec2(16513.0,16512.0),uv)*text_color;
#define _rsb col+=char(vec2(919584.0,1065244.0),uv)*text_color;
#define _pow col+=char(vec2(272656.0,0.0),uv)*text_color;
#define _usc col+=char(vec2(0.0,62.0),uv)*text_color;
#define _a col+=char(vec2(224.0,649374.0),uv)*text_color;
#define _b col+=char(vec2(1065444.0,665788.0),uv)*text_color;
#define _c col+=char(vec2(228.0,657564.0),uv)*text_color;
#define _d col+=char(vec2(66804.0,665758.0),uv)*text_color;
#define _e col+=char(vec2(228.0,772124.0),uv)*text_color;
#define _f col+=char(vec2(401543.0,1115152.0),uv)*text_color;
#define _g col+=char(vec2(244.0,665474.0),uv)*text_color;
#define _h col+=char(vec2(1065444.0,665762.0),uv)*text_color;
#define _i col+=char(vec2(262209.0,33292.0),uv)*text_color;
#define _j col+=char(vec2(131168.0,1066252.0),uv)*text_color;
#define _k col+=char(vec2(1065253.0,199204.0),uv)*text_color;
#define _l col+=char(vec2(266305.0,33292.0),uv)*text_color;
#define _m col+=char(vec2(421.0,698530.0),uv)*text_color;
#define _n col+=char(vec2(452.0,1198372.0),uv)*text_color;
#define _o col+=char(vec2(228.0,665756.0),uv)*text_color;
#define _p col+=char(vec2(484.0,667424.0),uv)*text_color;
#define _q col+=char(vec2(244.0,665474.0),uv)*text_color;
#define _r col+=char(vec2(354.0,590904.0),uv)*text_color;
#define _s col+=char(vec2(228.0,114844.0),uv)*text_color;
#define _t col+=char(vec2(8674.0,66824.0),uv)*text_color;
#define _u col+=char(vec2(292.0,1198868.0),uv)*text_color;
#define _v col+=char(vec2(276.0,664840.0),uv)*text_color;
#define _w col+=char(vec2(276.0,700308.0),uv)*text_color;
#define _x col+=char(vec2(292.0,1149220.0),uv)*text_color;
#define _y col+=char(vec2(292.0,1163824.0),uv)*text_color;
#define _z col+=char(vec2(480.0,1148988.0),uv)*text_color;
#define _lpa col+=char(vec2(401542.0,66572.0),uv)*text_color;
#define _bar col+=char(vec2(266304.0,33288.0),uv)*text_color;
#define _rpa col+=char(vec2(788512.0,1589528.0),uv)*text_color;
#define _tid col+=char(vec2(675840.0,0.0),uv)*text_color;
#define _lar col+=char(vec2(8387.0,1147904.0),uv)*text_color;
#define _nl print_pos = start_pos - vec2(0,CHAR_SPACING.y);
#define _nl2 print_pos = start_pos - vec2(0,CHAR_SPACING.y + 8.);
#define _nl3 print_pos = start_pos - vec2(0,CHAR_SPACING.y + 16.);
#define _nlx(x) print_pos = start_pos - vec2(0,CHAR_SPACING.y + (8. * (x - 1)));

//Extracts bit b from the given number.
float extract_bit(float n, float b) {
	b = clamp(b,-1.0,22.0);
	return floor(mod(floor(n / pow(2.0,floor(b))),2.0));   
}

//Returns the pixel at uv in the given bit-packed sprite.
float sprite(vec2 spr, vec2 size, vec2 uv) {
	uv = floor(uv);
	float bit = (size.x-uv.x-1.0) + uv.y * size.x;  
	bool bounds = all(greaterThanEqual(uv,vec2(0)))&& all(lessThan(uv,size)); 
	return bounds ? extract_bit(spr.x, bit - 21.0) + extract_bit(spr.y, bit) : 0.0;
}

//Prints a character and moves the print position forward by 1 character width.
vec3 char(vec2 ch, vec2 uv) {
	float px = sprite(ch, CHAR_SIZE, uv - print_pos);
	print_pos.x += CHAR_SPACING.x;
	return vec3(px);
}

vec3 hsv2rgb(vec3 c) {
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


/* #define text() \
    _spc _T _e _r _r _i _f _i _c _T _a _b _l _e */
// #define text() \
//     _spc _O _p _e _n _G _L _spc _B _a _s _e _nl2 \
//     _spc _spc _lar _spc _b _y _spc _T _e _r _r _i _f _i _c _T _a _b _l _e
#define text()


vec3 Text(vec2 uv) {
    vec2 position = (gl_FragCoord.xy / resolution.xy);
    vec3 rgb = hsv2rgb(vec3(position.x + position.y + (time / 2.0), 0.5, 0.5));

    vec3 col = vec3(0.0);

    vec2 center_pos = u_text_pos;
    if (center_pos.x == -1) {
        center_pos = vec2(res.x/2.0 - STRWIDTH(17.5)/2.0,res.y/2.0 - STRHEIGHT(1.0)/2.0);
    }

    BEGIN_TEXT(center_pos.x,center_pos.y + 10.);
    uv.y += sin(time+uv.x*0.05)*u_anim_strength;

    RGB(rgb.x, rgb.y, rgb.z) 

    if (u_size > 0) {
        int n = 1;
        for (int i=0; i < u_size; i++) {
            switch (u_data[i]) {
                case 48: _0; break;
                case 49: _1; break;
                case 50: _2; break;
                case 51: _3; break;
                case 52: _4; break;
                case 53: _5; break;
                case 54: _6; break;
                case 55: _7; break;
                case 56: _8; break;
                case 57: _9; break;

                case 32: _spc; break;
                case 33: _exc; break;
                case 35: _hsh; break;
                case 36: _dol; break;
                case 37: _pct; break;
                case 38: _amp; break;
                case 39: _apo; break;
                case 40: _lbr; break;
                case 41: _rbr; break;
                case 42: _ast; break;
                case 43: _crs; break;
                case 44: _com; break;
                case 45: _dsh; break;
                case 46: _per; break;
                case 47: _lsl; break;
                case 58: _col; break;
                case 62: _lar; break;
                case 63: _que; break;

                case 65: _A; break;
                case 66: _B; break;
                case 67: _C; break;
                case 68: _D; break;
                case 69: _E; break;
                case 70: _F; break;
                case 71: _G; break;
                case 72: _H; break;
                case 73: _I; break;
                case 74: _J; break;
                case 75: _K; break;
                case 76: _L; break;
                case 77: _M; break;
                case 78: _N; break;
                case 79: _O; break;
                case 80: _P; break;
                case 81: _Q; break;
                case 82: _R; break;
                case 83: _S; break;
                case 84: _T; break;
                case 85: _U; break;
                case 86: _V; break;
                case 87: _W; break;
                case 88: _X; break;
                case 89: _Y; break;
                case 90: _Z; break;

                case 97:  _a; break;
                case 98:  _b; break;
                case 99:  _c; break;
                case 100: _d; break;
                case 101: _e; break;
                case 102: _f; break;
                case 103: _g; break;
                case 104: _h; break;
                case 105: _i; break;
                case 106: _j; break;
                case 107: _k; break;
                case 108: _l; break;
                case 109: _m; break;
                case 110: _n; break;
                case 111: _o; break;
                case 112: _p; break;
                case 113: _q; break;
                case 114: _r; break;
                case 115: _s; break;
                case 116: _t; break;
                case 117: _u; break;
                case 118: _v; break;
                case 119: _w; break;
                case 120: _x; break;
                case 121: _y; break;
                case 122: _z; break;

                case 123: _lpa; break;
                case 124: _bar; break;
                case 125: _rpa; break;
                case 126: _tid; break;

                case 10: _nlx(n); n++; break;
            }
        }
    }

    text();

    // BEGIN _TEXT(res.x/2.0-STRWIDTH(11.0)/2.0,res.y/2.0)
    // print_pos += vec2(cos(time)*96.,sin(time)*96.);

    // RGB(1,0,0) _M RGB(1,.5,0)_o RGB(1,1,0)_v RGB(0,1,0)_i RGB(0,.5,1)_n RGB(0.5,0,1)_g _ RGB(1,0,0)_T RGB(1,.5,0)_e RGB(1,1,0)_x RGB(0,1,0)_t

    return col;
}

void main( void ) {
    vec2 uv = gl_FragCoord.xy / DOWN_SCALE;
    vec2 duv = floor(gl_FragCoord.xy / DOWN_SCALE);

    vec3 pixel = Text(duv);

    vec3 col = pixel*0.9+0.1;
    col *= (1.-distance(mod(uv,vec2(1.0)),vec2(0.65)))*1.2;

    gl_FragColor = vec4(vec3(col), 1.0);
}

