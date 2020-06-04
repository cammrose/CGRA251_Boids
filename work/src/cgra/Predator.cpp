//
// Created by Cameron Rose on 26/05/18.
//

#include "Predator.h"

Predator::Predator(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc) : position(pos), velocity(vel), acceleration(acc) {

}

glm::vec3 Predator::getPos() {
    return position;
}

void Predator::setPos(glm::vec3 p) {
    position = p;
}

glm::vec3 Predator::getVelocity() {
    return velocity;
}

void Predator::setVel(glm::vec3 v) {
    velocity = v;
}

glm::vec3 Predator::getAcc() {
    return acceleration;
}

void Predator::setAcc(glm::vec3 a) {
    acceleration = a;
}