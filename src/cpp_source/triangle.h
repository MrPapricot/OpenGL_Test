#include "config.h"

void init_triangle(triangle* trig) {
    float data[18] = {
        // Positions         // Colors
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom-left (red)
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right (green)
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f   // Top-right (blue)
    };
    
    trig->vertex_count = 3;
    glGenVertexArrays(1, &(trig->VAO));
    glBindVertexArray(trig->VAO);
    
    glGenBuffers(1, &(trig->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, trig->VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

void draw_triangle(triangle* trig) {
    glBindVertexArray(trig->VAO);
    glDrawArrays(GL_TRIANGLES, 0, trig->vertex_count);
    glBindVertexArray(0);
}