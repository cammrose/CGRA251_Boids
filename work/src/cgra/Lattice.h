//
// Created by Cameron Rose on 3/05/18.
//

#ifndef CGRA_PROJECT_CGRA_LATTICE_H
#define CGRA_PROJECT_CGRA_LATTICE_H

#endif //CGRA_PROJECT_CGRA_LATTICE_H
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

class Lattice{
public:
    glm::vec3 m_min;
    glm::vec3 m_max;
    glm::vec3 m_resolution;
    Lattice(glm::vec3 min, glm::vec3 max, glm::vec3 res);


};
class LatticeNode{
public:
    glm::vec3 m_position;
    LatticeNode(glm::vec3 pos)
        :m_position(pos){}


};