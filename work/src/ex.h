#pragma once

#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"
#include "cgra/Boid.h"
#include "cgra/Predator.h"
#include <vector>
#include "glm/glm.hpp"
#include "ex.h"

class Boid;
class Predator;
class Application {
public:
    // The window object managed by GLFW
    GLFWwindow *m_window;

    // The shader program used for drawing
    cgra::Program m_program;
    // The mesh data
    cgra::Mesh m_mesh;

    // The current size of the viewport
    glm::vec2 m_viewportSize;
    // The current mouse position
    glm::vec2 m_mousePosition;

    // The translation of the mesh as a vec3
    glm::vec3 m_translation;
    // The scale of the mesh
    float m_scale;

    cgra::Mesh meshes[1000];

    //Boid boids[5];
    std::vector<Boid> boids;
    //std::vector<Boid> boids2;
    std::vector<Predator> p;

    float avoidance = 12.5;
    float alignment = 12.5;
    float cohesion = 12.5;
    float neighborhood= 0.5;
    glm::vec3 totalForce;

    // A 4x4 matrix representing the rotation of the
    // mesh
    glm::mat4 m_rotationMatrix;

    // Whether or not the left, middle or right buttons are down.
    bool m_mouseButtonDown[3];

    Application(GLFWwindow *win)
        : m_window(win),
          m_viewportSize(1, 1), m_mousePosition(0, 0),
          m_translation(0), m_scale(1), m_rotationMatrix(1) {
        m_mouseButtonDown[0] = false;
        m_mouseButtonDown[1] = false;
        m_mouseButtonDown[2] = false;
    }

    void setWindowSize(int width, int height) {
        m_viewportSize.x = float(width);
        m_viewportSize.y = float(height);
    }

    void init();

    void loadObj(const char *filename, int position);

    void drawScene();
    void doGUI();

    void onKey(int key, int scancode, int action, int mods);

    void onMouseButton(int button, int action, int mods);

    void onCursorPos(double xpos, double ypos);

    void onScroll(double xoffset, double yoffset);

    float getRandPos();

    float getRandVel();

    void checkBounds();

    void checkPredatorBounds();

    float distance(glm::vec3 a, glm::vec3 b);

    double length(glm::vec3 l);

    float maxSpeed=3.75;

    float minSpeed=1.25;

    float pMaxSpeed=4;
    float pMinSpeed=1.5;
    float pNeighborhood= 0.5;
    float pForce=1;
    float pAvoidance=25;



    bool secondFlock =false;

    bool showPredator =false;

    bool addOb =false;

};
