#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <gl/glew.h>

GLuint load_shader_program(const char *vertex_file,const char *fragment_file);

#endif // SHADER_LOADER_H