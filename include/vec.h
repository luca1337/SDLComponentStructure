#ifndef VEC_H
#define VEC_H

typedef struct vec2{
    float x;
    float y;
}vec2_t;

vec2_t vec2_init(float, float);
vec2_t vec2_sum(vec2_t, vec2_t);
vec2_t vec2_sub(vec2_t, vec2_t);
vec2_t vec2_scale(vec2_t, vec2_t);
float vec2_slow_len(vec2_t);
float vec2_fast_len(vec2_t);
float vec2_dist(vec2_t, vec2_t);
int vec2_normalize(vec2_t*);
vec2_t vec2_scaled(vec2_t, float);
float vec2_dot(vec2_t, vec2_t);
vec2_t vec2_reflected(vec2_t, vec2_t);

#endif