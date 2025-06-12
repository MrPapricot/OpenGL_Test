typedef struct mat4 {
    float entries[16];
} mat4;

typedef struct vec3 {
    float entries[3];
} vec3;


mat4 cretae_translation_matrix(vec3 translation); 