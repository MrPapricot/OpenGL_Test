#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"




#include <stdint.h>

typedef struct triangle {
    uint32_t vertex_count;
    uint32_t VAO;
    uint32_t VBO;
} triangle;
