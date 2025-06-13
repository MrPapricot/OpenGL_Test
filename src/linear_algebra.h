typedef struct mat4 {
    float entries[16];
} mat4;

typedef struct vec3 {
    float entries[3];
} vec3;


mat4 create_translation_matrix(vec3 translation); 


mat4 create_rotation_overZ_matrix(float angle);


mat4 create_look_at(vec3 from, vec3 to);


float dot(vec3 u, vec3 v);


vec3 norm(vec3 u);


vec3 cross(vec3 u, vec3 v);


mat4 create_projectrion_matrix(float fovy, float aspect, float near, float far);