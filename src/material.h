#include "c_config.h"

typedef struct material {
    uint32_t texture;
} material;

material init_material(const char const *);

void delete_material(material*);

void use_material(material*, int32_t);