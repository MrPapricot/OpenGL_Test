#include "material.h"
#include "stb_image.h"

material init_material(const char const * filename) {
    material self;
    int32_t width, height, channels;
    uint8_t* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    if (!data) {
        printf("Can't load correctly");
        return self;
    }


    glGenTextures(1, &self.texture);
    glBindTexture(GL_TEXTURE_2D, self.texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return self;
}

void delete_material(material* self) {
    glDeleteTextures(1, &self->texture);
}

void use_material(material* self, int32_t unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, self->texture);
}