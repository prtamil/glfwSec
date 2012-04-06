#ifndef GLUTIL_H
#define GLUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/half_float.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Error Utilities
bool checkError(const char* Title);
bool checkExtension(char const * String);

//Initialization Routines
bool initGLEW();

//Shader Utils
bool validateProgram(GLuint ProgramName);
bool checkProgram(GLuint ProgramName);
bool checkShader(GLuint ShaderName, char const* Source);
std::string loadFile(std::string const & Filename);
GLuint createShader(GLenum Type,std::string const & Source);

#endif // GLUTIL_H
