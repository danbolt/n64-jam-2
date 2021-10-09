
#ifndef GAMEMATH_H
#define GAMEMATH_H

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	int x;
	int y;
} Pos2;


float clamp(float x, float min, float max);

#endif