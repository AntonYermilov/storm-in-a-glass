#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "environment.h"

class graphics {
  public:
    static bool initialize(int width, int height, const environment_t& environment);
    static void render();
    static bool should_finish();
    static void destroy();

  private:
    static void draw_circle(float position_x, float position_y, float radius, float brightness, int sides);
    static void draw_liquid(float width, float height);
    static void draw_glass(float width, float height);
    static void draw_polygon(GLfloat * polygon_vertices, GLfloat * colors, int count);
};

#endif
