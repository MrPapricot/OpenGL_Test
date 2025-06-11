#include <stdlib.h>
#include <stdint.h>

typedef struct triangle{
    uint32_t vertex_count;
    uint32_t VAO;
    uint32_t* VBOs;
    uint32_t EBO;
} triangle;


void init_triangle(triangle*);

void draw_triangle(triangle*);

void delete_triangle(triangle*);