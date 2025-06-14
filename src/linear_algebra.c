#include "linear_algebra.h"
#include <stdint.h>
#include <math.h>

#define PI 3.1415962

mat4 create_translation_matrix(vec3 translation) {
    mat4 matrix;

    matrix.entries[0] = 1.0f;
    matrix.entries[1] = 0.0f;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = 0.0f;
    matrix.entries[5] = 1.0f;
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.entries[0];
    matrix.entries[13] = translation.entries[1];
    matrix.entries[14] = translation.entries[2];
    matrix.entries[15] = 1.0f;

    return matrix;
}


mat4 create_rotation_overZ_matrix(float angle) {
    mat4 matrix;
    angle = angle * PI / 180.0f;

    float s = sinf(angle);
    float c = cosf(angle);   

    matrix.entries[0] = c;
    matrix.entries[1] = s;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = -s;
    matrix.entries[5] = c;
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = 0.0f;
    matrix.entries[13] = 0.0f;
    matrix.entries[14] = 0.0f;
    matrix.entries[15] = 1.0f;

    return matrix;
}



mat4 create_projectrion_matrix(float fovy, float aspect, float near, float far) {
    
    fovy = fovy * PI / 360.0f;
    float t = tanf(fovy);
    float n = -near;
    float f = -far;

    mat4 matrix;

    for (int i = 0; i < 16; i++) {
        matrix.entries[i] = 0.0f;
    }

    matrix.entries[0] = 1.0f / (aspect * t);
    matrix.entries[5] = 1.0f / t;
    matrix.entries[10] = -(n + f) / (n - f);
    matrix.entries[11] = -1.0f;
    matrix.entries[14] = 2 * n * f / (n - f);

    return matrix;
}



mat4 create_look_at(vec3 from, vec3 to) {
    vec3 global_up = {0.0f, 0.0f, 1.0f};

    vec3 f = {
        to.entries[0] - from.entries[0],
        to.entries[1] - from.entries[1],
        to.entries[2] - from.entries[2]
    };

    f = norm(f);

    vec3 r = norm(cross(f, global_up));
    vec3 u = norm(cross(r, f));

    mat4 matrix;

    matrix.entries[0] = r.entries[0];
    matrix.entries[1] = u.entries[0];
    matrix.entries[2] = -f.entries[0];
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = r.entries[1];
    matrix.entries[5] = u.entries[1];
    matrix.entries[6] = -f.entries[1];
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = r.entries[2];
    matrix.entries[9] = u.entries[2];
    matrix.entries[10] = -f.entries[2];
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = -dot(r, from);
    matrix.entries[13] = -dot(u, from);
    matrix.entries[14] = dot(f, from);
    matrix.entries[15] = 1.0f;

    return matrix;
}


float dot(vec3 u, vec3 v) {
    return (u.entries[0] * v.entries[0] +
            u.entries[1] * v.entries[1] +
            u.entries[2] * v.entries[2]);
}


vec3 norm(vec3 u) {
    vec3 v;
    float length = sqrtf(dot(u, u));

    v.entries[0] = u.entries[0] / length;
    v.entries[1] = u.entries[1] / length;
    v.entries[2] = u.entries[2] / length;

    return v;
}


vec3 cross(vec3 u, vec3 v) {
    vec3 w;

    w.entries[0] = u.entries[1] * v.entries[2] - u.entries[2] * v.entries[1];
    w.entries[1] = -(u.entries[0] * v.entries[2] - u.entries[2] * v.entries[0]);
    w.entries[2] = u.entries[0] * v.entries[1] - u.entries[1] * v.entries[0];

    return w;
}