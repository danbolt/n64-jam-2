// Generated by Arabiki64 V1.0
// By Buu342

// Mesh data
#define MESHCOUNT_Tower 1

#define MESH_Tower_None 0

// Animation data
#define ANIMATIONCOUNT_Tower 0

#include "envtexture.h"


// Custom combine mode to allow mixing primitive and vertex colors
#ifndef G_CC_PRIMLITE
    #define G_CC_PRIMLITE SHADE,0,PRIMITIVE,0,0,0,0,PRIMITIVE
#endif


/*********************************
              Models
*********************************/

static Vtx vtx_Tower_None[] = {
    {13, 20, -23, 0, 256, 608, 126, 0, 13, 255}, /* 0 */
    {12, 8, -12, 0, 0, 288, 126, 0, 13, 255}, /* 1 */
    {13, 7, -23, 0, 0, 608, 126, 0, 13, 255}, /* 2 */
    {13, 7, -23, 0, 512, 576, 0, -126, 13, 255}, /* 3 */
    {1, 8, -13, 0, 256, 320, 0, -126, 13, 255}, /* 4 */
    {1, 7, -23, 0, 256, 576, 0, -126, 13, 255}, /* 5 */
    {12, 8, -12, 0, 512, 544, 80, 56, -81, 255}, /* 6 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 7 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 8 */
    {12, 8, -12, 0, 0, 288, 126, -5, 12, 255}, /* 9 */
    {12, 20, -3, 0, 256, 0, 126, -5, 12, 255}, /* 10 */
    {11, 9, -2, 0, 0, 0, 126, -5, 12, 255}, /* 11 */
    {11, 9, -2, 0, 0, 1024, 126, -9, 11, 255}, /* 12 */
    {11, 20, 7, 0, 256, 768, 126, -9, 11, 255}, /* 13 */
    {10, 10, 8, 0, 0, 768, 126, -9, 11, 255}, /* 14 */
    {1, 9, -3, 0, 256, 480, 5, -127, 7, 255}, /* 15 */
    {10, 10, 8, 0, 512, 224, 5, -127, 7, 255}, /* 16 */
    {1, 9, 7, 0, 256, 224, 5, -127, 7, 255}, /* 17 */
    {1, 8, -13, 0, 256, 320, 3, -127, 7, 255}, /* 18 */
    {11, 9, -2, 0, 512, 0, 3, -127, 7, 255}, /* 19 */
    {1, 9, -3, 0, 256, 0, 3, -127, 7, 255}, /* 20 */
    {10, 10, 8, 0, 0, 768, 124, -20, 18, 255}, /* 21 */
    {11, 20, 17, 0, 256, 544, 124, -20, 18, 255}, /* 22 */
    {9, 11, 18, 0, 0, 544, 124, -20, 18, 255}, /* 23 */
    {1, 9, 7, 0, 256, 224, 10, -126, 7, 255}, /* 24 */
    {9, 11, 18, 0, 512, 0, 10, -126, 7, 255}, /* 25 */
    {1, 10, 17, 0, 256, 0, 10, -126, 7, 255}, /* 26 */
    {1, 10, 17, 0, 256, 1024, 11, -126, 7, 255}, /* 27 */
    {8, 11, 28, 0, 512, 736, 11, -126, 7, 255}, /* 28 */
    {1, 10, 27, 0, 256, 736, 11, -126, 7, 255}, /* 29 */
    {1, 10, 27, 0, 256, 736, 12, -126, 7, 255}, /* 30 */
    {8, 12, 38, 0, 512, 320, 12, -126, 7, 255}, /* 31 */
    {1, 11, 37, 0, 256, 320, 12, -126, 7, 255}, /* 32 */
    {8, 11, 28, 0, 0, 992, 125, -24, 8, 255}, /* 33 */
    {9, 20, 37, 0, 256, 704, 125, -24, 8, 255}, /* 34 */
    {8, 12, 38, 0, 0, 704, 125, -24, 8, 255}, /* 35 */
    {9, 11, 18, 0, 0, 544, 125, -22, 8, 255}, /* 36 */
    {10, 20, 27, 0, 256, 384, 125, -22, 8, 255}, /* 37 */
    {8, 11, 28, 0, 0, 384, 125, -22, 8, 255}, /* 38 */
    {8, 12, 38, 0, 0, 704, 124, -25, 8, 255}, /* 39 */
    {9, 20, 47, 0, 256, 384, 124, -25, 8, 255}, /* 40 */
    {7, 12, 48, 0, 0, 384, 124, -25, 8, 255}, /* 41 */
    {1, 12, 47, 0, 2016, 32, -8, 8, 126, 255}, /* 42 */
    {9, 20, 47, 0, 1600, 32, -8, 8, 126, 255}, /* 43 */
    {1, 20, 47, 0, 1792, 256, -8, 8, 126, 255}, /* 44 */
    {1, 11, 37, 0, 256, 320, 13, -126, 7, 255}, /* 45 */
    {7, 12, 48, 0, 512, 0, 13, -126, 7, 255}, /* 46 */
    {1, 12, 47, 0, 256, 0, 13, -126, 7, 255}, /* 47 */
    {1, 12, 47, 0, 1888, 480, -71, 71, 78, 255}, /* 48 */
    {7, 12, 53, 0, 1888, 448, -71, 71, 78, 255}, /* 49 */
    {9, 20, 47, 0, 1824, 448, -71, 71, 78, 255}, /* 50 */
    {7, 12, 48, 0, 3392, 320, 124, -26, 0, 255}, /* 51 */
    {9, 20, 47, 0, 3680, 416, 124, -26, 0, 255}, /* 52 */
    {7, 12, 53, 0, 3424, 128, 124, -26, 0, 255}, /* 53 */
    {1, 12, 47, 0, 3680, 608, 13, -126, 0, 255}, /* 54 */
    {7, 12, 48, 0, 3936, 576, 13, -126, 0, 255}, /* 55 */
    {7, 12, 53, 0, 3936, 448, 13, -126, 0, 255}, /* 56 */
    {-12, 20, -23, 0, 256, 224, -126, 0, 13, 255}, /* 57 */
    {-11, 8, -12, 0, 512, 0, -126, 0, 13, 255}, /* 58 */
    {-11, 20, -13, 0, 256, 0, -126, 0, 13, 255}, /* 59 */
    {-12, 7, -23, 0, 0, 576, 1, -126, 13, 255}, /* 60 */
    {1, 8, -13, 0, 256, 320, 1, -126, 13, 255}, /* 61 */
    {-11, 8, -12, 0, 0, 320, 1, -126, 13, 255}, /* 62 */
    {-11, 8, -12, 0, 2432, 992, -74, 58, -85, 255}, /* 63 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 64 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 65 */
    {-11, 8, -12, 0, 512, 1024, -127, 0, 7, 255}, /* 66 */
    {-10, 20, -3, 0, 256, 800, -127, 0, 7, 255}, /* 67 */
    {-11, 20, -13, 0, 256, 1024, -127, 0, 7, 255}, /* 68 */
    {-10, 9, -2, 0, 512, 800, -127, -5, 7, 255}, /* 69 */
    {-10, 20, 7, 0, 256, 416, -127, -5, 7, 255}, /* 70 */
    {-10, 20, -3, 0, 256, 800, -127, -5, 7, 255}, /* 71 */
    {1, 9, -3, 0, 256, 480, -3, -127, 9, 255}, /* 72 */
    {-9, 10, 8, 0, 0, 224, -3, -127, 9, 255}, /* 73 */
    {-10, 9, -2, 0, 0, 480, -3, -127, 9, 255}, /* 74 */
    {1, 8, -13, 0, 256, 320, 0, -127, 10, 255}, /* 75 */
    {-10, 9, -2, 0, 0, 0, 0, -127, 10, 255}, /* 76 */
    {-11, 8, -12, 0, 0, 320, 0, -127, 10, 255}, /* 77 */
    {-9, 10, 8, 0, 512, 512, -127, -9, 7, 255}, /* 78 */
    {-9, 20, 17, 0, 256, 288, -127, -9, 7, 255}, /* 79 */
    {-10, 20, 7, 0, 256, 512, -127, -9, 7, 255}, /* 80 */
    {1, 9, 7, 0, 256, 224, -5, -126, 11, 255}, /* 81 */
    {-7, 11, 18, 0, 0, 0, -5, -126, 11, 255}, /* 82 */
    {-9, 10, 8, 0, 0, 224, -5, -126, 11, 255}, /* 83 */
    {1, 10, 17, 0, 256, 1024, -10, -126, 7, 255}, /* 84 */
    {-7, 11, 28, 0, 0, 736, -10, -126, 7, 255}, /* 85 */
    {-7, 11, 18, 0, 0, 1024, -10, -126, 7, 255}, /* 86 */
    {1, 10, 27, 0, 256, 736, -11, -126, 7, 255}, /* 87 */
    {-6, 12, 38, 0, 0, 320, -11, -126, 7, 255}, /* 88 */
    {-7, 11, 28, 0, 0, 736, -11, -126, 7, 255}, /* 89 */
    {-7, 11, 28, 0, 512, 480, -125, -22, 7, 255}, /* 90 */
    {-8, 20, 37, 0, 256, 256, -125, -22, 7, 255}, /* 91 */
    {-8, 20, 27, 0, 256, 480, -125, -22, 7, 255}, /* 92 */
    {-7, 11, 18, 0, 512, 288, -125, -21, 7, 255}, /* 93 */
    {-8, 20, 27, 0, 256, 32, -125, -21, 7, 255}, /* 94 */
    {-9, 20, 17, 0, 256, 288, -125, -21, 7, 255}, /* 95 */
    {-6, 12, 38, 0, 512, 256, -125, -24, 7, 255}, /* 96 */
    {-7, 20, 47, 0, 256, 0, -125, -24, 7, 255}, /* 97 */
    {-8, 20, 37, 0, 256, 256, -125, -24, 7, 255}, /* 98 */
    {1, 12, 47, 0, 2016, 32, 8, 8, 126, 255}, /* 99 */
    {1, 20, 47, 0, 1792, 256, 8, 8, 126, 255}, /* 100 */
    {-7, 20, 47, 0, 2016, 480, 8, 8, 126, 255}, /* 101 */
    {1, 11, 37, 0, 256, 320, -12, -126, 7, 255}, /* 102 */
    {-6, 12, 48, 0, 0, 0, -12, -126, 7, 255}, /* 103 */
    {-6, 12, 38, 0, 0, 320, -12, -126, 7, 255}, /* 104 */
    {1, 12, 47, 0, 1728, 448, 71, 71, 78, 255}, /* 105 */
    {-7, 20, 47, 0, 1760, 480, 71, 71, 78, 255}, /* 106 */
    {-6, 12, 53, 0, 1760, 448, 71, 71, 78, 255}, /* 107 */
    {-6, 12, 48, 0, 3904, 896, -124, -26, 0, 255}, /* 108 */
    {-6, 12, 53, 0, 3904, 704, -124, -26, 0, 255}, /* 109 */
    {-7, 20, 47, 0, 3616, 928, -124, -26, 0, 255}, /* 110 */
    {1, 12, 47, 0, 3680, 608, -13, -126, 0, 255}, /* 111 */
    {-6, 12, 53, 0, 3392, 448, -13, -126, 0, 255}, /* 112 */
    {-6, 12, 48, 0, 3392, 576, -13, -126, 0, 255}, /* 113 */
    {13, 20, -23, 0, 256, 608, 126, 0, 13, 255}, /* 114 */
    {12, 31, -12, 0, 512, 288, 126, 0, 13, 255}, /* 115 */
    {12, 20, -13, 0, 256, 288, 126, 0, 13, 255}, /* 116 */
    {13, 32, -23, 0, 0, 512, -1, 126, 13, 255}, /* 117 */
    {1, 31, -13, 0, 256, 256, -1, 126, 13, 255}, /* 118 */
    {12, 31, -12, 0, 0, 256, -1, 126, 13, 255}, /* 119 */
    {12, 31, -12, 0, 512, 992, 43, 111, -44, 255}, /* 120 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 121 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 122 */
    {12, 31, -12, 0, 512, 288, 127, 0, 7, 255}, /* 123 */
    {12, 20, -3, 0, 256, 0, 127, 0, 7, 255}, /* 124 */
    {12, 20, -13, 0, 256, 288, 127, 0, 7, 255}, /* 125 */
    {12, 20, -13, 0, 384, 512, 58, 95, -61, 255}, /* 126 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 127 */
    {12, 20, -13, 0, 384, 512, 58, 95, -61, 255}, /* 128 */
    {11, 30, -2, 0, 512, 1024, 127, 5, 7, 255}, /* 129 */
    {11, 20, 7, 0, 256, 768, 127, 5, 7, 255}, /* 130 */
    {12, 20, -3, 0, 256, 1024, 127, 5, 7, 255}, /* 131 */
    {1, 30, -3, 0, 256, 1024, 3, 127, 9, 255}, /* 132 */
    {10, 30, 8, 0, 0, 736, 3, 127, 9, 255}, /* 133 */
    {11, 30, -2, 0, 0, 1024, 3, 127, 9, 255}, /* 134 */
    {1, 31, -13, 0, 256, 256, 0, 127, 10, 255}, /* 135 */
    {11, 30, -2, 0, 0, 0, 0, 127, 10, 255}, /* 136 */
    {12, 31, -12, 0, 0, 256, 0, 127, 10, 255}, /* 137 */
    {10, 30, 8, 0, 512, 768, 127, 9, 7, 255}, /* 138 */
    {11, 20, 17, 0, 256, 544, 127, 9, 7, 255}, /* 139 */
    {11, 20, 7, 0, 256, 768, 127, 9, 7, 255}, /* 140 */
    {1, 30, 7, 0, 256, 736, 5, 126, 11, 255}, /* 141 */
    {9, 29, 18, 0, 0, 416, 5, 126, 11, 255}, /* 142 */
    {10, 30, 8, 0, 0, 736, 5, 126, 11, 255}, /* 143 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 144 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 145 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 146 */
    {1, 29, 17, 0, 256, 512, 10, 126, 7, 255}, /* 147 */
    {8, 28, 28, 0, 0, 256, 10, 126, 7, 255}, /* 148 */
    {9, 29, 18, 0, 0, 512, 10, 126, 7, 255}, /* 149 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 150 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 151 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 152 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 153 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 154 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 155 */
    {1, 29, 27, 0, 256, 256, 11, 126, 7, 255}, /* 156 */
    {8, 28, 38, 0, 0, 0, 11, 126, 7, 255}, /* 157 */
    {8, 28, 28, 0, 0, 256, 11, 126, 7, 255}, /* 158 */
    {8, 28, 28, 0, 512, 992, 125, 22, 7, 255}, /* 159 */
    {9, 20, 37, 0, 256, 704, 125, 22, 7, 255}, /* 160 */
    {10, 20, 27, 0, 256, 992, 125, 22, 7, 255}, /* 161 */
    {9, 29, 18, 0, 512, 544, 125, 21, 7, 255}, /* 162 */
    {10, 20, 27, 0, 256, 384, 125, 21, 7, 255}, /* 163 */
    {11, 20, 17, 0, 256, 544, 125, 21, 7, 255}, /* 164 */
    {9, 20, 37, 0, 384, 512, 28, 58, 109, 255}, /* 165 */
    {9, 20, 47, 0, 384, 512, 22, 48, 115, 255}, /* 166 */
    {9, 20, 37, 0, 384, 512, 28, 58, 109, 255}, /* 167 */
    {8, 28, 38, 0, 512, 704, 125, 24, 7, 255}, /* 168 */
    {9, 20, 47, 0, 256, 384, 125, 24, 7, 255}, /* 169 */
    {9, 20, 37, 0, 256, 704, 125, 24, 7, 255}, /* 170 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 171 */
    {9, 20, 37, 0, 384, 512, 28, 58, 109, 255}, /* 172 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 173 */
    {1, 28, 47, 0, 1600, 480, -8, -8, 126, 255}, /* 174 */
    {1, 20, 47, 0, 1792, 256, -8, -8, 126, 255}, /* 175 */
    {9, 20, 47, 0, 1600, 32, -8, -8, 126, 255}, /* 176 */
    {1, 28, 37, 0, 256, 512, 12, 126, 7, 255}, /* 177 */
    {7, 27, 48, 0, 0, 256, 12, 126, 7, 255}, /* 178 */
    {8, 28, 38, 0, 0, 512, 12, 126, 7, 255}, /* 179 */
    {1, 28, 47, 0, 1728, 480, -71, -71, 78, 255}, /* 180 */
    {9, 20, 47, 0, 1728, 416, -71, -71, 78, 255}, /* 181 */
    {7, 27, 53, 0, 1696, 448, -71, -71, 78, 255}, /* 182 */
    {7, 27, 48, 0, 3968, 416, 124, 26, 0, 255}, /* 183 */
    {7, 27, 53, 0, 4000, 224, 124, 26, 0, 255}, /* 184 */
    {9, 20, 47, 0, 3680, 416, 124, 26, 0, 255}, /* 185 */
    {1, 28, 47, 0, 3552, 384, 13, 126, 0, 255}, /* 186 */
    {7, 27, 53, 0, 3200, 64, 13, 126, 0, 255}, /* 187 */
    {7, 27, 48, 0, 3168, 352, 13, 126, 0, 255}, /* 188 */
    {-12, 20, -23, 0, 256, 224, -126, 0, 13, 255}, /* 189 */
    {-11, 31, -12, 0, 0, 0, -126, 0, 13, 255}, /* 190 */
    {-12, 32, -23, 0, 0, 224, -126, 0, 13, 255}, /* 191 */
    {-12, 32, -23, 0, 512, 512, 0, 126, 13, 255}, /* 192 */
    {1, 31, -13, 0, 256, 256, 0, 126, 13, 255}, /* 193 */
    {1, 32, -23, 0, 256, 512, 0, 126, 13, 255}, /* 194 */
    {-11, 31, -12, 0, 2432, 544, -38, 113, -44, 255}, /* 195 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 196 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 197 */
    {-11, 31, -12, 0, 0, 1024, -126, 5, 12, 255}, /* 198 */
    {-10, 20, -3, 0, 256, 800, -126, 5, 12, 255}, /* 199 */
    {-10, 30, -2, 0, 0, 800, -126, 5, 12, 255}, /* 200 */
    {-11, 20, -13, 0, 384, 512, -52, 97, -63, 255}, /* 201 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 202 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 203 */
    {-10, 30, -2, 0, 0, 800, -126, 9, 11, 255}, /* 204 */
    {-10, 20, 7, 0, 256, 416, -126, 9, 11, 255}, /* 205 */
    {-9, 30, 8, 0, 0, 416, -126, 9, 11, 255}, /* 206 */
    {1, 30, -3, 0, 256, 1024, -5, 127, 7, 255}, /* 207 */
    {-9, 30, 8, 0, 512, 736, -5, 127, 7, 255}, /* 208 */
    {1, 30, 7, 0, 256, 736, -5, 127, 7, 255}, /* 209 */
    {1, 31, -13, 0, 256, 256, -3, 127, 7, 255}, /* 210 */
    {-10, 30, -2, 0, 512, 0, -3, 127, 7, 255}, /* 211 */
    {1, 30, -3, 0, 256, 0, -3, 127, 7, 255}, /* 212 */
    {-9, 30, 8, 0, 0, 512, -124, 20, 18, 255}, /* 213 */
    {-9, 20, 17, 0, 256, 288, -124, 20, 18, 255}, /* 214 */
    {-7, 29, 18, 0, 0, 288, -124, 20, 18, 255}, /* 215 */
    {1, 30, 7, 0, 256, 736, -10, 126, 7, 255}, /* 216 */
    {-7, 29, 18, 0, 512, 416, -10, 126, 7, 255}, /* 217 */
    {1, 29, 17, 0, 256, 416, -10, 126, 7, 255}, /* 218 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 219 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 220 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 221 */
    {1, 29, 17, 0, 256, 512, -11, 126, 7, 255}, /* 222 */
    {-7, 28, 28, 0, 512, 256, -11, 126, 7, 255}, /* 223 */
    {1, 29, 27, 0, 256, 256, -11, 126, 7, 255}, /* 224 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 225 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 226 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 227 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 228 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 229 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 230 */
    {1, 29, 27, 0, 256, 256, -12, 126, 7, 255}, /* 231 */
    {-6, 28, 38, 0, 512, 0, -12, 126, 7, 255}, /* 232 */
    {1, 28, 37, 0, 256, 0, -12, 126, 7, 255}, /* 233 */
    {-7, 28, 28, 0, 0, 480, -125, 24, 8, 255}, /* 234 */
    {-8, 20, 37, 0, 256, 256, -125, 24, 8, 255}, /* 235 */
    {-6, 28, 38, 0, 0, 256, -125, 24, 8, 255}, /* 236 */
    {-7, 29, 18, 0, 0, 288, -125, 22, 8, 255}, /* 237 */
    {-8, 20, 27, 0, 256, 32, -125, 22, 8, 255}, /* 238 */
    {-7, 28, 28, 0, 0, 32, -125, 22, 8, 255}, /* 239 */
    {-8, 20, 37, 0, 384, 512, -24, 58, 110, 255}, /* 240 */
    {-8, 20, 37, 0, 384, 512, -24, 58, 110, 255}, /* 241 */
    {-7, 20, 47, 0, 384, 512, -18, 48, 116, 255}, /* 242 */
    {-6, 28, 38, 0, 0, 256, -124, 25, 8, 255}, /* 243 */
    {-7, 20, 47, 0, 256, 0, -124, 25, 8, 255}, /* 244 */
    {-6, 27, 48, 0, 0, 0, -124, 25, 8, 255}, /* 245 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 246 */
    {-8, 20, 37, 0, 384, 512, -24, 58, 110, 255}, /* 247 */
    {-8, 20, 37, 0, 384, 512, -24, 58, 110, 255}, /* 248 */
    {1, 28, 47, 0, 1600, 480, 8, -8, 126, 255}, /* 249 */
    {-7, 20, 47, 0, 2016, 480, 8, -8, 126, 255}, /* 250 */
    {1, 20, 47, 0, 1792, 256, 8, -8, 126, 255}, /* 251 */
    {1, 28, 37, 0, 256, 512, -13, 126, 7, 255}, /* 252 */
    {-6, 27, 48, 0, 512, 256, -13, 126, 7, 255}, /* 253 */
    {1, 28, 47, 0, 256, 256, -13, 126, 7, 255}, /* 254 */
    {1, 28, 47, 0, 1760, 480, 71, -71, 78, 255}, /* 255 */
    {-6, 27, 53, 0, 1824, 480, 71, -71, 78, 255}, /* 256 */
    {-7, 20, 47, 0, 1824, 448, 71, -71, 78, 255}, /* 257 */
    {-6, 27, 48, 0, 3328, 896, -124, 26, 0, 255}, /* 258 */
    {-7, 20, 47, 0, 3616, 928, -124, 26, 0, 255}, /* 259 */
    {-6, 27, 53, 0, 3328, 704, -124, 26, 0, 255}, /* 260 */
    {1, 28, 47, 0, 3552, 384, -13, 126, 0, 255}, /* 261 */
    {-6, 27, 48, 0, 3968, 384, -13, 126, 0, 255}, /* 262 */
    {-6, 27, 53, 0, 3968, 96, -13, 126, 0, 255}, /* 263 */
    {13, 20, -23, 0, 256, 608, 126, 0, 13, 255}, /* 264 */
    {12, 20, -13, 0, 256, 288, 126, 0, 13, 255}, /* 265 */
    {12, 8, -12, 0, 0, 288, 126, 0, 13, 255}, /* 266 */
    {13, 7, -23, 0, 512, 576, -1, -126, 13, 255}, /* 267 */
    {12, 8, -12, 0, 512, 320, -1, -126, 13, 255}, /* 268 */
    {1, 8, -13, 0, 256, 320, -1, -126, 13, 255}, /* 269 */
    {12, 8, -12, 0, 512, 544, 80, 56, -81, 255}, /* 270 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 271 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 272 */
    {12, 8, -12, 0, 0, 288, 127, 0, 7, 255}, /* 273 */
    {12, 20, -13, 0, 256, 288, 127, 0, 7, 255}, /* 274 */
    {12, 20, -3, 0, 256, 0, 127, 0, 7, 255}, /* 275 */
    {11, 9, -2, 0, 0, 1024, 127, -5, 7, 255}, /* 276 */
    {12, 20, -3, 0, 256, 1024, 127, -5, 7, 255}, /* 277 */
    {11, 20, 7, 0, 256, 768, 127, -5, 7, 255}, /* 278 */
    {1, 9, -3, 0, 256, 480, 3, -127, 9, 255}, /* 279 */
    {11, 9, -2, 0, 512, 480, 3, -127, 9, 255}, /* 280 */
    {10, 10, 8, 0, 512, 224, 3, -127, 9, 255}, /* 281 */
    {1, 8, -13, 0, 256, 320, 0, -127, 10, 255}, /* 282 */
    {12, 8, -12, 0, 512, 320, 0, -127, 10, 255}, /* 283 */
    {11, 9, -2, 0, 512, 0, 0, -127, 10, 255}, /* 284 */
    {10, 10, 8, 0, 0, 768, 127, -9, 7, 255}, /* 285 */
    {11, 20, 7, 0, 256, 768, 127, -9, 7, 255}, /* 286 */
    {11, 20, 17, 0, 256, 544, 127, -9, 7, 255}, /* 287 */
    {1, 9, 7, 0, 256, 224, 5, -126, 11, 255}, /* 288 */
    {10, 10, 8, 0, 512, 224, 5, -126, 11, 255}, /* 289 */
    {9, 11, 18, 0, 512, 0, 5, -126, 11, 255}, /* 290 */
    {1, 10, 17, 0, 256, 1024, 10, -126, 7, 255}, /* 291 */
    {9, 11, 18, 0, 512, 1024, 10, -126, 7, 255}, /* 292 */
    {8, 11, 28, 0, 512, 736, 10, -126, 7, 255}, /* 293 */
    {1, 10, 27, 0, 256, 736, 11, -126, 7, 255}, /* 294 */
    {8, 11, 28, 0, 512, 736, 11, -126, 7, 255}, /* 295 */
    {8, 12, 38, 0, 512, 320, 11, -126, 7, 255}, /* 296 */
    {8, 11, 28, 0, 0, 992, 125, -22, 7, 255}, /* 297 */
    {10, 20, 27, 0, 256, 992, 125, -22, 7, 255}, /* 298 */
    {9, 20, 37, 0, 256, 704, 125, -22, 7, 255}, /* 299 */
    {9, 11, 18, 0, 0, 544, 125, -21, 7, 255}, /* 300 */
    {11, 20, 17, 0, 256, 544, 125, -21, 7, 255}, /* 301 */
    {10, 20, 27, 0, 256, 384, 125, -21, 7, 255}, /* 302 */
    {8, 12, 38, 0, 0, 704, 125, -24, 7, 255}, /* 303 */
    {9, 20, 37, 0, 256, 704, 125, -24, 7, 255}, /* 304 */
    {9, 20, 47, 0, 256, 384, 125, -24, 7, 255}, /* 305 */
    {1, 11, 37, 0, 256, 320, 12, -126, 7, 255}, /* 306 */
    {8, 12, 38, 0, 512, 320, 12, -126, 7, 255}, /* 307 */
    {7, 12, 48, 0, 512, 0, 12, -126, 7, 255}, /* 308 */
    {-12, 20, -23, 0, 256, 224, -126, 0, 13, 255}, /* 309 */
    {-12, 7, -23, 0, 512, 224, -126, 0, 13, 255}, /* 310 */
    {-11, 8, -12, 0, 512, 0, -126, 0, 13, 255}, /* 311 */
    {-12, 7, -23, 0, 0, 576, 0, -126, 13, 255}, /* 312 */
    {1, 7, -23, 0, 256, 576, 0, -126, 13, 255}, /* 313 */
    {1, 8, -13, 0, 256, 320, 0, -126, 13, 255}, /* 314 */
    {-11, 8, -12, 0, 2432, 992, -74, 58, -85, 255}, /* 315 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 316 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 317 */
    {-11, 8, -12, 0, 512, 1024, -126, -5, 12, 255}, /* 318 */
    {-10, 9, -2, 0, 512, 800, -126, -5, 12, 255}, /* 319 */
    {-10, 20, -3, 0, 256, 800, -126, -5, 12, 255}, /* 320 */
    {-10, 9, -2, 0, 512, 800, -126, -9, 11, 255}, /* 321 */
    {-9, 10, 8, 0, 512, 416, -126, -9, 11, 255}, /* 322 */
    {-10, 20, 7, 0, 256, 416, -126, -9, 11, 255}, /* 323 */
    {1, 9, -3, 0, 256, 480, -5, -127, 7, 255}, /* 324 */
    {1, 9, 7, 0, 256, 224, -5, -127, 7, 255}, /* 325 */
    {-9, 10, 8, 0, 0, 224, -5, -127, 7, 255}, /* 326 */
    {1, 8, -13, 0, 256, 320, -3, -127, 7, 255}, /* 327 */
    {1, 9, -3, 0, 256, 0, -3, -127, 7, 255}, /* 328 */
    {-10, 9, -2, 0, 0, 0, -3, -127, 7, 255}, /* 329 */
    {-9, 10, 8, 0, 512, 512, -124, -20, 18, 255}, /* 330 */
    {-7, 11, 18, 0, 512, 288, -124, -20, 18, 255}, /* 331 */
    {-9, 20, 17, 0, 256, 288, -124, -20, 18, 255}, /* 332 */
    {1, 9, 7, 0, 256, 224, -10, -126, 7, 255}, /* 333 */
    {1, 10, 17, 0, 256, 0, -10, -126, 7, 255}, /* 334 */
    {-7, 11, 18, 0, 0, 0, -10, -126, 7, 255}, /* 335 */
    {1, 10, 17, 0, 256, 1024, -11, -126, 7, 255}, /* 336 */
    {1, 10, 27, 0, 256, 736, -11, -126, 7, 255}, /* 337 */
    {-7, 11, 28, 0, 0, 736, -11, -126, 7, 255}, /* 338 */
    {1, 10, 27, 0, 256, 736, -12, -126, 7, 255}, /* 339 */
    {1, 11, 37, 0, 256, 320, -12, -126, 7, 255}, /* 340 */
    {-6, 12, 38, 0, 0, 320, -12, -126, 7, 255}, /* 341 */
    {-7, 11, 28, 0, 512, 480, -125, -24, 8, 255}, /* 342 */
    {-6, 12, 38, 0, 512, 256, -125, -24, 8, 255}, /* 343 */
    {-8, 20, 37, 0, 256, 256, -125, -24, 8, 255}, /* 344 */
    {-7, 11, 18, 0, 512, 288, -125, -22, 8, 255}, /* 345 */
    {-7, 11, 28, 0, 512, 32, -125, -22, 8, 255}, /* 346 */
    {-8, 20, 27, 0, 256, 32, -125, -22, 8, 255}, /* 347 */
    {-6, 12, 38, 0, 512, 256, -124, -25, 8, 255}, /* 348 */
    {-6, 12, 48, 0, 512, 0, -124, -25, 8, 255}, /* 349 */
    {-7, 20, 47, 0, 256, 0, -124, -25, 8, 255}, /* 350 */
    {1, 11, 37, 0, 256, 320, -13, -126, 7, 255}, /* 351 */
    {1, 12, 47, 0, 256, 0, -13, -126, 7, 255}, /* 352 */
    {-6, 12, 48, 0, 0, 0, -13, -126, 7, 255}, /* 353 */
    {13, 20, -23, 0, 256, 608, 126, 0, 13, 255}, /* 354 */
    {13, 32, -23, 0, 512, 608, 126, 0, 13, 255}, /* 355 */
    {12, 31, -12, 0, 512, 288, 126, 0, 13, 255}, /* 356 */
    {13, 32, -23, 0, 0, 512, 0, 126, 13, 255}, /* 357 */
    {1, 32, -23, 0, 256, 512, 0, 126, 13, 255}, /* 358 */
    {1, 31, -13, 0, 256, 256, 0, 126, 13, 255}, /* 359 */
    {12, 31, -12, 0, 512, 992, 43, 111, -44, 255}, /* 360 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 361 */
    {12, 20, -13, 0, 512, 768, 58, 95, -61, 255}, /* 362 */
    {12, 31, -12, 0, 512, 288, 126, 5, 12, 255}, /* 363 */
    {11, 30, -2, 0, 512, 0, 126, 5, 12, 255}, /* 364 */
    {12, 20, -3, 0, 256, 0, 126, 5, 12, 255}, /* 365 */
    {12, 20, -13, 0, 384, 512, 58, 95, -61, 255}, /* 366 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 367 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 368 */
    {11, 30, -2, 0, 512, 1024, 126, 9, 11, 255}, /* 369 */
    {10, 30, 8, 0, 512, 768, 126, 9, 11, 255}, /* 370 */
    {11, 20, 7, 0, 256, 768, 126, 9, 11, 255}, /* 371 */
    {1, 30, -3, 0, 256, 1024, 5, 127, 7, 255}, /* 372 */
    {1, 30, 7, 0, 256, 736, 5, 127, 7, 255}, /* 373 */
    {10, 30, 8, 0, 0, 736, 5, 127, 7, 255}, /* 374 */
    {1, 31, -13, 0, 256, 256, 3, 127, 7, 255}, /* 375 */
    {1, 30, -3, 0, 256, 0, 3, 127, 7, 255}, /* 376 */
    {11, 30, -2, 0, 0, 0, 3, 127, 7, 255}, /* 377 */
    {10, 30, 8, 0, 512, 768, 124, 20, 18, 255}, /* 378 */
    {9, 29, 18, 0, 512, 544, 124, 20, 18, 255}, /* 379 */
    {11, 20, 17, 0, 256, 544, 124, 20, 18, 255}, /* 380 */
    {1, 30, 7, 0, 256, 736, 10, 126, 7, 255}, /* 381 */
    {1, 29, 17, 0, 256, 416, 10, 126, 7, 255}, /* 382 */
    {9, 29, 18, 0, 0, 416, 10, 126, 7, 255}, /* 383 */
    {12, 20, -3, 0, 384, 512, 64, 109, -15, 255}, /* 384 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 385 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 386 */
    {1, 29, 17, 0, 256, 512, 11, 126, 7, 255}, /* 387 */
    {1, 29, 27, 0, 256, 256, 11, 126, 7, 255}, /* 388 */
    {8, 28, 28, 0, 0, 256, 11, 126, 7, 255}, /* 389 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 390 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 391 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 392 */
    {11, 20, 7, 0, 384, 512, 59, 105, 39, 255}, /* 393 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 394 */
    {11, 20, 17, 0, 384, 512, 47, 89, 78, 255}, /* 395 */
    {1, 29, 27, 0, 256, 256, 12, 126, 7, 255}, /* 396 */
    {1, 28, 37, 0, 256, 0, 12, 126, 7, 255}, /* 397 */
    {8, 28, 38, 0, 0, 0, 12, 126, 7, 255}, /* 398 */
    {8, 28, 28, 0, 512, 992, 125, 24, 8, 255}, /* 399 */
    {8, 28, 38, 0, 512, 704, 125, 24, 8, 255}, /* 400 */
    {9, 20, 37, 0, 256, 704, 125, 24, 8, 255}, /* 401 */
    {9, 29, 18, 0, 512, 544, 125, 22, 8, 255}, /* 402 */
    {8, 28, 28, 0, 512, 384, 125, 22, 8, 255}, /* 403 */
    {10, 20, 27, 0, 256, 384, 125, 22, 8, 255}, /* 404 */
    {8, 28, 38, 0, 512, 704, 124, 25, 8, 255}, /* 405 */
    {7, 27, 48, 0, 512, 384, 124, 25, 8, 255}, /* 406 */
    {9, 20, 47, 0, 256, 384, 124, 25, 8, 255}, /* 407 */
    {10, 20, 27, 0, 384, 512, 36, 71, 99, 255}, /* 408 */
    {9, 20, 37, 0, 384, 512, 28, 58, 109, 255}, /* 409 */
    {9, 20, 37, 0, 384, 512, 28, 58, 109, 255}, /* 410 */
    {1, 28, 37, 0, 256, 512, 13, 126, 7, 255}, /* 411 */
    {1, 28, 47, 0, 256, 256, 13, 126, 7, 255}, /* 412 */
    {7, 27, 48, 0, 0, 256, 13, 126, 7, 255}, /* 413 */
    {-12, 20, -23, 0, 256, 224, -126, 0, 13, 255}, /* 414 */
    {-11, 20, -13, 0, 256, 0, -126, 0, 13, 255}, /* 415 */
    {-11, 31, -12, 0, 0, 0, -126, 0, 13, 255}, /* 416 */
    {-12, 32, -23, 0, 512, 512, 1, 126, 13, 255}, /* 417 */
    {-11, 31, -12, 0, 512, 256, 1, 126, 13, 255}, /* 418 */
    {1, 31, -13, 0, 256, 256, 1, 126, 13, 255}, /* 419 */
    {-11, 31, -12, 0, 2432, 544, -38, 113, -44, 255}, /* 420 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 421 */
    {-11, 20, -13, 0, 2432, 768, -52, 97, -63, 255}, /* 422 */
    {-11, 31, -12, 0, 0, 1024, -127, 0, 7, 255}, /* 423 */
    {-11, 20, -13, 0, 256, 1024, -127, 0, 7, 255}, /* 424 */
    {-10, 20, -3, 0, 256, 800, -127, 0, 7, 255}, /* 425 */
    {-11, 20, -13, 0, 384, 512, -52, 97, -63, 255}, /* 426 */
    {-11, 20, -13, 0, 384, 512, -52, 97, -63, 255}, /* 427 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 428 */
    {-10, 30, -2, 0, 0, 800, -127, 5, 7, 255}, /* 429 */
    {-10, 20, -3, 0, 256, 800, -127, 5, 7, 255}, /* 430 */
    {-10, 20, 7, 0, 256, 416, -127, 5, 7, 255}, /* 431 */
    {1, 30, -3, 0, 256, 1024, -3, 127, 9, 255}, /* 432 */
    {-10, 30, -2, 0, 512, 1024, -3, 127, 9, 255}, /* 433 */
    {-9, 30, 8, 0, 512, 736, -3, 127, 9, 255}, /* 434 */
    {1, 31, -13, 0, 256, 256, 0, 127, 10, 255}, /* 435 */
    {-11, 31, -12, 0, 512, 256, 0, 127, 10, 255}, /* 436 */
    {-10, 30, -2, 0, 512, 0, 0, 127, 10, 255}, /* 437 */
    {-9, 30, 8, 0, 0, 512, -127, 9, 7, 255}, /* 438 */
    {-10, 20, 7, 0, 256, 512, -127, 9, 7, 255}, /* 439 */
    {-9, 20, 17, 0, 256, 288, -127, 9, 7, 255}, /* 440 */
    {1, 30, 7, 0, 256, 736, -5, 126, 11, 255}, /* 441 */
    {-9, 30, 8, 0, 512, 736, -5, 126, 11, 255}, /* 442 */
    {-7, 29, 18, 0, 512, 416, -5, 126, 11, 255}, /* 443 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 444 */
    {-10, 20, -3, 0, 384, 512, -57, 112, -16, 255}, /* 445 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 446 */
    {1, 29, 17, 0, 256, 512, -10, 126, 7, 255}, /* 447 */
    {-7, 29, 18, 0, 512, 512, -10, 126, 7, 255}, /* 448 */
    {-7, 28, 28, 0, 512, 256, -10, 126, 7, 255}, /* 449 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 450 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 451 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 452 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 453 */
    {-10, 20, 7, 0, 384, 512, -53, 109, 40, 255}, /* 454 */
    {-9, 20, 17, 0, 384, 512, -41, 90, 79, 255}, /* 455 */
    {1, 29, 27, 0, 256, 256, -11, 126, 7, 255}, /* 456 */
    {-7, 28, 28, 0, 512, 256, -11, 126, 7, 255}, /* 457 */
    {-6, 28, 38, 0, 512, 0, -11, 126, 7, 255}, /* 458 */
    {-7, 28, 28, 0, 0, 480, -125, 22, 7, 255}, /* 459 */
    {-8, 20, 27, 0, 256, 480, -125, 22, 7, 255}, /* 460 */
    {-8, 20, 37, 0, 256, 256, -125, 22, 7, 255}, /* 461 */
    {-7, 29, 18, 0, 0, 288, -125, 21, 7, 255}, /* 462 */
    {-9, 20, 17, 0, 256, 288, -125, 21, 7, 255}, /* 463 */
    {-8, 20, 27, 0, 256, 32, -125, 21, 7, 255}, /* 464 */
    {-6, 28, 38, 0, 0, 256, -125, 24, 7, 255}, /* 465 */
    {-8, 20, 37, 0, 256, 256, -125, 24, 7, 255}, /* 466 */
    {-7, 20, 47, 0, 256, 0, -125, 24, 7, 255}, /* 467 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 468 */
    {-8, 20, 27, 0, 384, 512, -31, 72, 100, 255}, /* 469 */
    {-8, 20, 37, 0, 384, 512, -24, 58, 110, 255}, /* 470 */
    {1, 28, 37, 0, 256, 512, -12, 126, 7, 255}, /* 471 */
    {-6, 28, 38, 0, 512, 512, -12, 126, 7, 255}, /* 472 */
    {-6, 27, 48, 0, 512, 256, -12, 126, 7, 255}, /* 473 */
};

static Gfx gfx_Tower_None[] = {
    gsSPVertex(vtx_Tower_None+0, 63, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPLoadTextureBlock(environmentTexture, G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 7, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+63, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+126, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+189, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+252, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+315, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+378, 63, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSP1Triangle(33, 34, 35, 0),
    gsSP1Triangle(36, 37, 38, 0),
    gsSP1Triangle(39, 40, 41, 0),
    gsSP1Triangle(42, 43, 44, 0),
    gsSP1Triangle(45, 46, 47, 0),
    gsSP1Triangle(48, 49, 50, 0),
    gsSP1Triangle(51, 52, 53, 0),
    gsSP1Triangle(54, 55, 56, 0),
    gsSP1Triangle(57, 58, 59, 0),
    gsSP1Triangle(60, 61, 62, 0),

    gsSPVertex(vtx_Tower_None+441, 33, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSP1Triangle(24, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSP1Triangle(30, 31, 32, 0),
    gsSPEndDisplayList(),
};


/*********************************
          Animation Data
*********************************/
