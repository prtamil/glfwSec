#ifndef RENDERER_H
#define RENDERER_H
#include "glUtil.h"

bool init_Program();
bool init_Buffers();
bool InitGL(void);
void Delete_GL();
void PaintGL(double time);
void draw(double time);

#endif // RENDERER_H
