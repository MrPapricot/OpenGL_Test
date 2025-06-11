#include <stdlib.h>
#include <stdint.h>

typedef struct triangle{
    uint32_t vertex_count;
    uint32_t VAO;
    uint32_t* VBOs;
    uint32_t EBO;
} triangle;


void init_triangle(triangle* trig) {

    float positions[] = {
        -0.8f, -0.8f, 0.0f,
        -0.8f, +0.8f, 0.0f,
        +0.8f, -0.8f, 0.0f,
        +0.8f, +0.8f, 0.0f
    };

    uint32_t colors[] = {0, 1, 2, 3};
    uint32_t indices[] = {0, 1, 2, 2, 1, 3};

    trig->VBOs = malloc(2 * sizeof(uint32_t));
    trig->vertex_count = 6;

    glGenVertexArrays(1, &(trig->VAO));
    glBindVertexArray(trig->VAO);
    
    glGenBuffers(2, trig->VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, trig->VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    glBindBuffer(GL_ARRAY_BUFFER, trig->VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(uint32_t), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &trig->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trig->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void draw_triangle(triangle* trig) {
    glBindVertexArray(trig->VAO);
    glDrawElements(GL_TRIANGLES, trig->vertex_count, GL_UNSIGNED_INT, 0);
}

void delete_triangle(triangle* trig) {
    glDeleteVertexArrays(1, &trig->VAO);
    glDeleteBuffers(2, trig->VBOs);
    glDeleteBuffers(1, &trig->EBO);
}