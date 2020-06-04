//
// Created by Cameron Rose on 15/05/18.
//

#include "Boid.h"

    Boid::Boid(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc, int id) : position(pos), velocity(vel), acceleration(acc), id(id) {

    }

    glm::vec3 Boid::getPos() {
        return position;
    }

    void Boid::setPos(glm::vec3 p) {
        position = p;
    }

    glm::vec3 Boid::getVelocity() {
        return velocity;
    }

    void Boid::setVel(glm::vec3 v) {
        velocity = v;
    }

    glm::vec3 Boid::getAcc() {
        return acceleration;
    }

    void Boid::setAcc(glm::vec3 a) {
        acceleration = a;
    }





