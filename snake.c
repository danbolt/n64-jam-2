
#include "monsters.h"

Vtx snake_verts[] = {
{ 76, -127, 38, 0, 0, 0, 32, 139, 2, 255 },
{ 156, -112, 150, 0, 0, 0, 212, 167, 0, 255 },
{ 58, 231, 20, 0, 0, 0, 145, 93, 32, 255 },
{ 65, -48, 15, 0, 0, 0, 119, 90, 8, 255 },
{ 101, 11, 115, 0, 0, 0, 212, 167, 0, 255 },
{ 30, 106, 24, 0, 0, 0, 115, 82, 12, 255 },
{ 75, 52, 44, 0, 0, 0, 159, 110, 29, 255 },
{ 69, 50, 18, 0, 0, 0, 162, 113, 28, 255 },
{ 110, -88, 85, 0, 0, 0, 77, 53, 9, 255 },
{ 85, -43, 49, 0, 0, 0, 213, 168, 13, 255 },
{ 117, -109, 189, 0, 0, 0, 37, 59, 145, 255 },
{ 51, -107, 241, 0, 0, 0, 54, 86, 217, 255 },
{ 34, -166, 184, 0, 0, 0, 21, 33, 84, 255 },
{ 53, -136, 79, 0, 0, 0, 217, 6, 0, 255 },
{ 131, 11, 208, 0, 0, 0, 238, 225, 44, 255 },
{ 82, -136, 191, 0, 0, 0, 237, 229, 255, 255 },
{ 47, -135, 219, 0, 0, 0, 237, 229, 255, 255 },
{ 38, -167, 188, 0, 0, 0, 237, 229, 255, 255 },
{ -73, -127, 38, 0, 0, 0, 57, 109, 6, 255 },
{ -153, -112, 150, 0, 0, 0, 212, 167, 0, 255 },
{ -14, 218, 14, 0, 0, 0, 145, 93, 32, 255 },
{ 25, 268, 3, 0, 0, 0, 212, 167, 1, 255 },
{ 24, 263, 16, 0, 0, 0, 212, 167, 4, 255 },
{ 1, -130, 18, 0, 0, 0, 11, 145, 0, 255 },
{ 1, -91, 283, 0, 0, 0, 94, 91, 18, 255 },
{ -63, -48, 15, 0, 0, 0, 212, 167, 0, 255 },
{ -101, -39, 115, 0, 0, 0, 212, 167, 0, 255 },
{ 1, -8, 125, 0, 0, 0, 240, 230, 46, 255 },
{ 1, -49, 7, 0, 0, 0, 98, 94, 18, 255 },
{ -42, 139, 24, 0, 0, 0, 212, 167, 0, 255 },
{ -5, 123, 52, 0, 0, 0, 222, 211, 41, 255 },
{ -5, 123, 3, 0, 0, 0, 77, 53, 9, 255 },
{ -41, 5, 44, 0, 0, 0, 159, 110, 29, 255 },
{ 16, 29, 98, 0, 0, 0, 215, 174, 63, 255 },
{ 16, 29, 6, 0, 0, 0, 94, 91, 18, 255 },
{ -36, 7, 18, 0, 0, 0, 162, 113, 28, 255 },
{ 1, -56, 68, 0, 0, 0, 41, 32, 1, 255 },
{ 1, -185, 157, 0, 0, 0, 83, 103, 7, 255 },
{ -108, -88, 85, 0, 0, 0, 77, 53, 9, 255 },
{ -83, -43, 49, 0, 0, 0, 213, 168, 13, 255 },
{ -114, -109, 189, 0, 0, 0, 37, 59, 145, 255 },
{ -49, -107, 241, 0, 0, 0, 54, 86, 217, 255 },
{ -32, -166, 184, 0, 0, 0, 21, 33, 84, 255 },
{ -51, -136, 79, 0, 0, 0, 217, 6, 0, 255 },
{ 1, -110, 37, 0, 0, 0, 218, 52, 51, 255 },
{ 1, -180, 74, 0, 0, 0, 217, 6, 1, 255 },
{ 1, -119, 121, 0, 0, 0, 218, 29, 28, 255 },
{ -128, -52, 208, 0, 0, 0, 238, 225, 44, 255 },
{ 1, -59, 211, 0, 0, 0, 212, 167, 1, 255 },
{ -80, -136, 191, 0, 0, 0, 237, 229, 255, 255 },
{ -45, -135, 219, 0, 0, 0, 237, 229, 255, 255 },
{ -36, -167, 188, 0, 0, 0, 237, 229, 255, 255 },
};

Gfx snake_commands[] = {
  gsSPVertex(snake_verts, 52, 0),
  gsSP2Triangles(28, 0, 23, 0, 14, 24, 1, 0),
  gsSP2Triangles(1, 24, 37, 0, 6, 27, 4, 0),
  gsSP2Triangles(34, 3, 28, 0, 3, 8, 0, 0),
  gsSP2Triangles(7, 9, 3, 0, 21, 5, 31, 0),
  gsSP2Triangles(2, 30, 5, 0, 0, 36, 23, 0),
  gsSP2Triangles(31, 7, 34, 0, 5, 33, 6, 0),
  gsSP2Triangles(6, 4, 9, 0, 8, 37, 36, 0),
  gsSP2Triangles(9, 1, 8, 0, 5, 6, 7, 0),
  gsSP2Triangles(11, 12, 10, 0, 13, 46, 45, 0),
  gsSP2Triangles(13, 45, 44, 0, 13, 44, 46, 0),
  gsSP2Triangles(4, 48, 14, 0, 16, 17, 15, 0),
  gsSP2Triangles(21, 22, 2, 0, 28, 3, 0, 0),
  gsSP2Triangles(14, 48, 24, 0, 6, 33, 27, 0),
  gsSP2Triangles(34, 7, 3, 0, 3, 9, 8, 0),
  gsSP2Triangles(7, 6, 9, 0, 21, 2, 5, 0),
  gsSP2Triangles(2, 22, 30, 0, 0, 8, 36, 0),
  gsSP2Triangles(31, 5, 7, 0, 5, 30, 33, 0),
  gsSP2Triangles(8, 1, 37, 0, 9, 14, 1, 0),
  gsSP2Triangles(9, 4, 14, 0, 4, 27, 48, 0),
  gsSP2Triangles(28, 23, 18, 0, 47, 19, 24, 0),
  gsSP2Triangles(19, 37, 24, 0, 32, 26, 27, 0),
  gsSP2Triangles(34, 28, 25, 0, 25, 18, 38, 0),
  gsSP2Triangles(35, 25, 39, 0, 21, 31, 29, 0),
  gsSP2Triangles(20, 29, 30, 0, 18, 23, 36, 0),
  gsSP2Triangles(31, 34, 35, 0, 29, 32, 33, 0),
  gsSP2Triangles(32, 39, 26, 0, 38, 36, 37, 0),
  gsSP2Triangles(39, 38, 19, 0, 29, 35, 32, 0),
  gsSP2Triangles(41, 40, 42, 0, 43, 45, 46, 0),
  gsSP2Triangles(43, 44, 45, 0, 43, 46, 44, 0),
  gsSP2Triangles(26, 47, 48, 0, 50, 49, 51, 0),
  gsSP2Triangles(21, 20, 22, 0, 28, 18, 25, 0),
  gsSP2Triangles(47, 24, 48, 0, 32, 27, 33, 0),
  gsSP2Triangles(34, 25, 35, 0, 25, 38, 39, 0),
  gsSP2Triangles(35, 39, 32, 0, 21, 29, 20, 0),
  gsSP2Triangles(20, 30, 22, 0, 18, 36, 38, 0),
  gsSP2Triangles(31, 35, 29, 0, 29, 33, 30, 0),
  gsSP2Triangles(38, 37, 19, 0, 39, 19, 47, 0),
  gsSP2Triangles(39, 47, 26, 0, 26, 48, 27, 0),
  gsSPEndDisplayList()
};
