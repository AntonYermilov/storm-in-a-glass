#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include "graphics.h"
#include "environment.h"

static GLFWwindow * window = nullptr;
static float scale = 1.0f;
static const environment_t * env = nullptr;
static const float eps = 10;

void draw_polygon(GLfloat *, GLfloat *, int);

bool graphics::initialize(int width, int height, const environment_t& environment) {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Storm in a Glass", nullptr, nullptr);
    env = &environment;

    if (window == nullptr) {
        std::cerr << "Window creation failed" << std::endl;
        destroy();
        return false;
    }
    glfwMakeContextCurrent(window);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-width / 2.0f, width / 2.0f, -eps, height - eps, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    scale = 0.9f * std::min(width / env->get_config().width, height / env->get_config().height);
    //scale /= std::max(width, height);

    return true;
}

void graphics::render() {
    glClearColor(0.894f, 0.867f, 0.812f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_glass(env->get_config().width, env->get_config().height);
    draw_liquid(env->get_config().width, env->get_liquid().liquid_level);

    for (auto& element: env->get_elements()) {
        float element_brightness = 4.0f / (1.0f + expf(element.get_density() / env->get_liquid().liquid_density)) / 3.0f;
        draw_circle(element.get_position_x(), element.get_position_y(), element.get_radius(), element_brightness, 30);
    }

    glfwSwapBuffers(window);

    glfwPollEvents();
}

void graphics::draw_polygon(GLfloat * polygon_vertices, GLfloat * colors, int count) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygon_vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_POLYGON, 0, count);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void graphics::draw_circle(float position_x, float position_y, float radius, float brightness, int sides) {
    float w = env->get_config().width;
    float r = radius * scale;
    float x = (position_x - w / 2) * scale;
    float y = position_y * scale;

    float d = 2 * M_PI / sides;

    GLfloat circle_vertices[3 * sides];
    GLfloat colors[4 * sides];

    for (int i = 0; i < sides; i++) {
        float vx = x + r * cosf(i * d);
        float vy = y + r * sinf(i * d);
        circle_vertices[3 * i] = vx;
        circle_vertices[3 * i + 1] = vy;
        circle_vertices[3 * i + 2] = 0;

        colors[4 * i] = brightness;
        colors[4 * i + 1] = brightness;
        colors[4 * i + 2] = brightness;
        colors[4 * i + 3] = 1.0;
    }

    draw_polygon(circle_vertices, colors, sides);
}


void graphics::draw_liquid(float width, float height) {
    float w = width * scale;
    float h = height * scale;
    float w2 = w / 2.0f;

    GLfloat polygon_vertices[] = {
        -w2, 0, 0,
         w2, 0, 0,
         w2, h, 0,
        -w2, h, 0,
    };

    GLfloat colors[] = {
        0.25, 0.64, 0.87, 1.0,
        0.25, 0.64, 0.87, 1.0,
        0.25, 0.64, 0.87, 1.0,
        0.25, 0.64, 0.87, 1.0,
    };

    draw_polygon(polygon_vertices, colors, 4);
}

void graphics::draw_glass(float width, float height) {
    static const float e = 10;
    float w = width * scale;
    float h = height * scale;
    float w2 = w / 2.0f;

    GLfloat glass_1[] = {
         w2      ,  0  , 0,
         w2      ,  h  , 0,
         w2 + eps,  h  , 0,
         w2 + eps, -eps, 0,
        -w2 - eps, -eps, 0,
    };

    GLfloat glass_2[] = {
        -w2 - eps, -eps, 0,
        -w2 - eps,  h  , 0,
        -w2      ,  h  , 0,
        -w2      ,  0  , 0,
         w2      ,  0  , 0,
    };

    GLfloat colors[] = {
        0.15, 0.15, 0.15, 1.0,
        0.15, 0.15, 0.15, 1.0,
        0.15, 0.15, 0.15, 1.0,
        0.15, 0.15, 0.15, 1.0,
        0.15, 0.15, 0.15, 1.0,
    };

    draw_polygon(glass_1, colors, 5);
    draw_polygon(glass_2, colors, 5);
}

bool graphics::should_finish() {
    return glfwWindowShouldClose(window);
}

void graphics::destroy() {
    glfwTerminate();
}

