    #include "c_config.h"
    #include <glad/glad.h>
    #include "material.h"
    #include "linear_algebra.h"

    int64_t make_module(const char*, uint32_t);
    int64_t make_shader(const char*, const char*);

    int main() {
        GLFWwindow* window;


        struct triangle trig;
        material mat;
        material mask;


        printf("Started\n");
        if (!glfwInit()) {
            printf("Error with glfw init\n");
            return -1;
        }
        
        window = glfwCreateWindow(800, 400, "Sosal Application", NULL, NULL);
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
            printf("Hello\n");
            glfwTerminate();
            return -1;
        }
        glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

        uint32_t shader = make_shader("../src/shaders/vertex.txt", "../src/shaders/fragment.txt");

        init_triangle(&trig);
        mat = init_material("../images/Sosal.jpg");
        mask = init_material("../images/mask.jpg");

        glUseProgram(shader);
        glUniform1i(glGetUniformLocation(shader, "material"), 0);
        glUniform1i(glGetUniformLocation(shader, "mask"), 1);


        vec3 position = { -0.2f, +0.4f, 0.0f };
        mat4 model;

        vec3 camera_pos = {-1.3f, 0.0f, 0.7f};
        vec3 camera_target = {0.0f, 0.0f, 0.0f};

        uint32_t model_location = glGetUniformLocation(shader, "model");
        uint32_t view_location = glGetUniformLocation(shader, "view");
        uint32_t projection_location = glGetUniformLocation(shader, "projection");
        
        mat4 projection = create_projectrion_matrix(
            70.0f, 800.0f / 400.0f, 0.1f, 20.0f 
        );
        mat4 view = create_look_at(camera_pos, camera_target);

        glUniformMatrix4fv(view_location, 1, GL_FALSE, view.entries);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.entries);   

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            model = create_rotation_overZ_matrix(20 * glfwGetTime());
            glUniformMatrix4fv(model_location, 1, GL_FALSE, model.entries);

            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader);

            draw_triangle(&trig);
            use_material(&mat, 0);
            use_material(&mask, 1);
            
            glfwSwapBuffers(window);
        }

        delete_triangle(&trig);
        delete_material(&mat);
        delete_material(&mask);

        glDeleteProgram(shader);
        glfwTerminate();
        return 0;
    }

    int64_t make_shader(const char const* vertex_filepath, const char const* fragment_filepath) {
        uint32_t modules[2] = {make_module(vertex_filepath, GL_VERTEX_SHADER), make_module(fragment_filepath, GL_FRAGMENT_SHADER)};

        uint32_t shader = glCreateProgram();
        for (size_t i = 0; i < 2; i++) {
            if (modules[i] == -1) {
                return -1;
            }
            glAttachShader(shader, modules[i]);
        }
        glLinkProgram(shader);

        int32_t success;
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            char errorLog[1024];
            glGetProgramInfoLog(shader, 1024, NULL, errorLog);
            printf("Link Error\n%s", errorLog);
        }
        for (size_t i = 0; i < 2; i++) {
            glDeleteShader(modules[i]);
        }

        return shader;
    }


    int64_t make_module(const char const* path, uint32_t module_type) {
        FILE* file = fopen(path, "rb");
        if (file == NULL) {
            printf("Error opening the file [%s]\n", path);
            return -1;
        }
        char* buffer;
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        rewind(file);
        buffer = (char*)malloc(size + 1);
        if (buffer == NULL) {
            printf("Unable to allocate enougth memory\n");
            fclose(file);
            return -1;
        }
        size_t bytes_read = fread(buffer, 1, size, file);
        fclose(file);
        if (bytes_read != size) {
            printf("Can't read file [%s]\n", path);
            return -1;
        }
        buffer[size] = '\0';
        uint32_t sharedModule = glCreateShader(module_type);
        glShaderSource(sharedModule, 1, (const char* const*)&buffer, NULL);
        glCompileShader(sharedModule);

        int32_t success;
        glGetShaderiv(sharedModule, GL_COMPILE_STATUS, &success);
        if (!success) {
            char errorLog[1024];
            glGetShaderInfoLog(sharedModule, 1024, NULL, errorLog);
            printf("Compilation Error\n, %s", errorLog);
        }

        return sharedModule;
    }