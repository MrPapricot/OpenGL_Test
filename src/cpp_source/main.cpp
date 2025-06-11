#include "config.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include "triangle.h"


uint32_t make_module(const std::string&, uint32_t);
uint32_t make_shader(const std::string&, const std::string&);

int main() {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    GLFWwindow* window;
    triangle trig;

    std::cout << "Started" << std::endl;
    if (!glfwInit()) {
        std::cout << "Error" << std::endl;
        return -1;
    }
     
    window = glfwCreateWindow(400, 400, "New Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
        glfwTerminate();
        return -1;
    }
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    uint32_t shader = make_shader("../src/shaders/vertex.shader", "../src/shaders/fragment.shader");

    init_triangle(&trig);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        draw_triangle(&trig);
        
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}

uint32_t make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    std::vector<uint32_t> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    uint32_t shader = glCreateProgram();
    for (uint32_t shared_module: modules) {
        glAttachShader(shader, shared_module);
    }
    glLinkProgram(shader);

    int32_t success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Link Error\n" << errorLog << std::endl;
    }
    for (uint32_t shared_module: modules) {
        glDeleteShader(shared_module);
    }

    return shader;
}


uint32_t make_module(const std::string& path, uint32_t module_type) {
    std::ifstream file;
    std::string line;
    std::stringstream bufferedReader;


    file.open(path);
    while (std::getline(file, line)) {
        bufferedReader << line << "\n";
    }
    std::string shaderSource = bufferedReader.str();
    const char* sharedSrc = shaderSource.c_str();
    bufferedReader.str("");
    file.close();

    uint32_t sharedModule = glCreateShader(module_type);
    glShaderSource(sharedModule, 1, &sharedSrc, NULL);
    glCompileShader(sharedModule);

    int32_t success;
    glGetShaderiv(sharedModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(sharedModule, 1024, NULL, errorLog);
        std::cout << "Compilation Error\n" << errorLog << std::endl;
    }

    return sharedModule;
}