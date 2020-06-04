//
// Created by Cameron Rose on 26/05/18.
//

#ifndef CGRA_PROJECT_CGRA_PREDATOR_H
#define CGRA_PROJECT_CGRA_PREDATOR_H


#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "opengl.h"
#include "imgui.h"

#include "cgra/matrix.hpp"

#include "ex.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


class Predator {
public:
    Predator(){}

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Predator(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc);

    glm::vec3 getPos();

    void setPos(glm::vec3 p);

    glm::vec3 getVelocity();

    void setVel(glm::vec3 v);

    glm::vec3 getAcc();

    void setAcc(glm::vec3 a);

};


#endif //CGRA_PROJECT_CGRA_PREDATOR_H
