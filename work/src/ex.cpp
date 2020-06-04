#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "opengl.h"
#include "imgui.h"


#include "cgra/matrix.hpp"
#include "cgra/mesh.hpp"
#include "ex.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


void Application::init() {

    m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        CGRA_SRCDIR "/res/shaders/simple.fs.glsl");

    // Create a view matrix that positions the camera
    // 10 units behind the object
    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -8, 1);
    m_program.setViewMatrix(viewMatrix);

    meshes[0]=m_mesh;
    for(int i=0; i < 5; i++){
            meshes[i] = m_mesh;
    }


    srand(time(0));
    for(int i=0; i < 125; i++){
        boids.push_back(Boid(glm::vec3(getRandPos(),getRandPos(),getRandPos()), glm::vec3(getRandVel(),getRandVel(),getRandVel()), glm::vec3(0,0,0), 1));
        boids.push_back(Boid(glm::vec3(getRandPos(),getRandPos(),getRandPos()), glm::vec3(getRandVel(),getRandVel(),getRandVel()), glm::vec3(0,0,0), 2));
    }



    p.push_back(Predator(glm::vec3(getRandPos(),getRandPos(),getRandPos()), glm::vec3(getRandVel(),getRandVel(),getRandVel()), glm::vec3(0,0,0)));

    loadObj("cube.obj", 0);
    loadObj("sphere.obj", 1);
    loadObj("cube.obj", 2);
    loadObj("predator_boid.obj", 3);
    loadObj("sphere.obj", 4);


}

void Application::loadObj(const char *filename, int position) {
	// Load the .obj
    ifstream file;
    try {
        file.open(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << e.what() << "'" << std::endl;
        return;
    }

    string line, character;
    float x,y,z;

    unsigned int vCount=0;
    unsigned int fCount=0;

    while(!file.eof()){

        getline(file, line);
        istringstream iss(line);
        if(line.empty()){
            break;
        }
        iss >> character;
        if(character == "v"){
            vCount++;
        }
        if(character == "f"){
            fCount++;
        }
    }
    file.close();

    file.open(filename);

    while(!file.eof()){
        getline(file, line);
        istringstream iss(line);
        iss >> character;
        if(character == "v"){
            iss >> x;
            iss >> y;
            iss >> z;
            break;
        }
    }

    unsigned int numVertices  = vCount;
    unsigned int numTriangles = fCount;

    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);

    vertices.setRow(0, {  x,  y,  z });

    for (size_t i = 1; i < numVertices; i++) {
        // Add each position to the vertices matrix
        getline(file, line);
        istringstream iss(line);
        iss >> character;
        iss >> x;
        iss >> y;
        iss >> z;
        vertices.setRow(i, {  x,  y,  z});
    }

    unsigned int xT,yT,zT;
    while(!file.eof()){
        getline(file, line);
        istringstream iss(line);
        iss >> character;
        if(character == "f"){
            iss >> xT;
            iss >> yT;
            iss >> zT;
            break;
        }
    }

    triangles.setRow(0, {  xT-1,  yT-1,  zT-1 });

    for (size_t i = 1; i < numTriangles; i++) {

        getline(file, line);
        istringstream iss(line);
        iss >> character;
        iss >> xT;
        iss >> yT;
        iss >> zT;
        triangles.setRow(i, {  xT-1,  yT-1, zT-1});
    }
    meshes[position].setData(vertices, triangles);

}

void Application::drawScene() {
    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    // Set the projection matrix
    m_program.setProjectionMatrix(projectionMatrix);

    glm::mat4 modelTransform(1.0f);

    m_scale=2.0;
    modelTransform=m_rotationMatrix;
    modelTransform=glm::scale(modelTransform, glm::vec3(m_scale));
    m_program.setModelMatrix(modelTransform);
    meshes[0].setDrawWireframe(true);
    meshes[0].draw(); //Bounding box

    for(int i=0; i<boids.size(); i++){
        //Cohesion
        glm::vec3 coSum(0,0,0);
        int coCount=0;
        for(int j=0; j<boids.size(); j++){
            if ((i != j) && distance(boids.at(i).getPos(), boids.at(j).getPos()) < neighborhood && boids.at(i).id == boids.at(j).id) {
                coSum += boids.at(j).getPos();
                coCount++;
            }
        }

        if (coCount > 0) {
            glm::vec3 centroid = coSum/(float)coCount;
            coSum=cohesion*(centroid - boids.at(i).getPos());

        }

        //Alignment
        glm::vec3 alSum(0,0,0);
        int alCount=0;
        for(int j=0; j<boids.size(); j++){
            //cout<<distance(boids.at(i).getPos(), boids.at(j).getPos());
            if ((i != j) && distance(boids.at(i).getPos(), boids.at(j).getPos()) < neighborhood && boids.at(i).id == boids.at(j).id) {
                alSum += boids.at(j).getVelocity();
                alCount++;
            }
        }

        if (alCount > 0) {
            glm::vec3 centroid = alSum/(float)alCount;
            alSum=(alignment*(centroid - boids.at(i).getVelocity()));

        }

        //Avoidance
        glm::vec3 avSum(0,0,0);

        for(int j=0; j<boids.size(); j++){
            if ((i != j) && distance(boids.at(i).getPos(), boids.at(j).getPos()) < neighborhood) {
                float value = 1/this->length(boids.at(i).getPos()-boids.at(j).getPos());
                avSum+=(glm::normalize(boids.at(i).getPos()-boids.at(j).getPos())* value);
            }
        }
        avSum*=avoidance;

        //Predator Avoidance
        glm::vec3 pAvSum(0,0,0);
        if(showPredator) {
            if (distance(boids.at(i).getPos(), p.at(0).getPos()) < pNeighborhood) {
                float value = 1/this->length(boids.at(i).getPos()-p.at(0).getPos());
                pAvSum+= (glm::normalize(boids.at(i).getPos()-p.at(0).getPos())* value);
            }
        }
        pAvSum*=pAvoidance;

        //Sphere Avoidance
        glm::vec3 sAvSum(0,0,0);

        if(addOb) {
            for(int i=0; i<3; i++) {
                float value = 1 / this->length(boids.at(i).getPos()-glm::vec3(i-1,i-1,i-1));
                pAvSum += (glm::normalize(boids.at(i).getPos()-glm::vec3(i-1,i-1,i-1)) * value);
            }
        }
        sAvSum*=100;

        boids[i].setAcc(coSum+alSum+avSum+pAvSum+sAvSum);
    }

    for(int i=0; i<boids.size(); i++) {

        glm::vec3 velocity=boids[i].getVelocity()+(boids[i].getAcc()*0.01f);
        float len=this->length(velocity);
        if(len > maxSpeed){
            velocity=(maxSpeed/len)*velocity;
        }

        float lenMin=this->length(velocity);
        if(lenMin < minSpeed){
            velocity=(minSpeed/lenMin)*velocity;
        }
        boids[i].setVel(velocity);
        boids[i].setPos(boids[i].getPos()+(boids[i].getVelocity()*0.01f));
        checkBounds();

        if(boids.at(i).id==1) {
            m_scale=0.04;
            modelTransform=m_rotationMatrix;
            modelTransform=glm::translate(modelTransform,  boids[i].getPos());
            modelTransform=glm::scale(modelTransform, glm::vec3(m_scale));

            m_program.setModelMatrix(modelTransform);
            meshes[1].draw(); //Boid
        }

        if(secondFlock) {
            if (boids.at(i).id == 2) {
                m_scale = 0.03;
                modelTransform = m_rotationMatrix;
                modelTransform = glm::translate(modelTransform, boids[i].getPos());
                modelTransform = glm::scale(modelTransform, glm::vec3(m_scale));

                m_program.setModelMatrix(modelTransform);
                meshes[2].draw(); //Boid
            }
        }
    }

    if(showPredator) {
        Boid closestBoid=boids.at(0);
        for (int i = 0; i < boids.size(); i++) {
            if (distance(p.at(0).getPos(), boids.at(i).getPos()) < distance(p.at(0).getPos(), closestBoid.getPos()) && distance(p.at(0).getPos(), boids.at(i).getPos()) < pNeighborhood) {
                closestBoid = boids.at(i);
            }
        }

        glm::vec3 dir = glm::normalize(closestBoid.getPos() - p.at(0).getPos());
        p[0].setVel(dir);

        glm::vec3 velocity = p[0].getVelocity() + (p[0].getAcc() * 0.01f);
        float len = this->length(velocity);
        if (len > pMaxSpeed) {
            velocity = (pMaxSpeed / len) * velocity;
        }

        float lenMin = this->length(velocity);
        if (lenMin < pMinSpeed) {
            velocity = (pMinSpeed / lenMin) * velocity;
        }

        p[0].setVel(velocity);
        p[0].setPos(p[0].getPos() + (p[0].getVelocity() * 0.01f));
        checkPredatorBounds();

        m_scale = 0.12;
        modelTransform = m_rotationMatrix;
        modelTransform = glm::translate(modelTransform, p[0].getPos());
        modelTransform = glm::scale(modelTransform, glm::vec3(m_scale));

        m_program.setModelMatrix(modelTransform);
        meshes[3].draw(); //Predator
    }

    if(addOb) {
        for (int i = 0; i < 3; i++) {
            m_scale = 0.5;
            modelTransform = m_rotationMatrix;
            modelTransform = glm::translate(modelTransform, glm::vec3(i - 1, i - 1, i - 1));
            modelTransform = glm::scale(modelTransform, glm::vec3(m_scale));

            m_program.setModelMatrix(modelTransform);
            meshes[4].draw(); //Sphere
        }
    }
}

void Application::doGUI() {
    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Boids");

    static glm::vec3 rotation(0, 0, 0);
    if (ImGui::InputFloat3("Rotation", &rotation[0])) {
        m_rotationMatrix=glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);

    }

    static float co = 12.5;
    if(ImGui::SliderFloat("Cohesion", &co, 0,25)){
        cohesion=co;
    }
    static float av = 12.5;
    if(ImGui::SliderFloat("Avoidance", &av, 0,25)){
        avoidance=av;
    }
    static float al = 12.5;
    if(ImGui::SliderFloat("Alignment", &al, 0,25)){
        alignment=al;
    }
    static float ne = 0.5;
    if(ImGui::SliderFloat("Neighborhood", &ne, 0,2)){
        neighborhood=ne;
    }
    static float min = 1.25;
    if(ImGui::SliderFloat("Min Speed", &min, 0,5)){
        minSpeed=min;
    }
    static float max = 3.75;
    if(ImGui::SliderFloat("Max Speed", &max, 0,5)){
        maxSpeed=max;
    }
    static float pAv = 12.5;
    if(ImGui::SliderFloat("Predator Avoidance", &pAv, 0,25)){
        pAvoidance=pAv;
    }

    static bool b = false;
    if(ImGui::Checkbox("Second Flock", &b)){
        secondFlock=true;
    }
    else{
        if(!b) {
            secondFlock = false;
        }
    }

    static bool a = false;
    if(ImGui::Checkbox("Predator", &a)){
        showPredator=true;
    }
    else{
        if(!a) {
            showPredator = false;
        }

    }

    if(a){
        static float pFo = 1;
        if(ImGui::SliderFloat("Predator Force", &pFo, 0.1,2)){
            pForce=pFo;
        }
        static float pNe = 0.5;
        if(ImGui::SliderFloat("Predator Neighborhood", &pNe, 0,2)){
            pNeighborhood=pNe;
        }

        static float pMin = 1.5;
        if(ImGui::SliderFloat("Predator Min Speed", &pMin, 0,5)){
            pMinSpeed=pMin;
        }

        static float pMax = 4;
        if(ImGui::SliderFloat("Predator Max Speed", &pMax, 0,5)){
            pMaxSpeed=pMax;
        }
    }

    static bool c = false;
    if(ImGui::Checkbox("Obstacles", &c)){
        addOb=true;
    }
    else{
        if(!c) {
            addOb = false;
        }
    }

    ImGui::End();
}

void Application::onMouseButton(int button, int action, int) {
    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}

void Application::onCursorPos(double xpos, double ypos) {

    // Make a vec2 with the current mouse position
    glm::vec2 currentMousePosition(xpos, ypos);

    // Get the difference from the previous mouse position
    glm::vec2 mousePositionDelta = currentMousePosition - m_mousePosition;

    if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]) {

    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]) {
        m_translation=glm::vec3(mousePositionDelta[0],-mousePositionDelta[1], 0);

    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]) {
        m_scale=sqrt((mousePositionDelta[0]*mousePositionDelta[0])+(mousePositionDelta[1]*mousePositionDelta[1]));
    }

    // Update the mouse position to the current one
    m_mousePosition = currentMousePosition;
}

void Application::onKey(int key, int scancode, int action, int mods) {
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void Application::onScroll(double xoffset, double yoffset) {
    (void)xoffset;
    (void)yoffset;
}



float Application::getRandPos(){

    float random_number = (rand() % 400) -200;
    random_number = random_number/100;
    return random_number;
}

float Application::getRandVel(){

    float random_number = (rand() % 30)-15;
    random_number = random_number/1000;
    return random_number;
}

void Application::checkBounds(){
    for(int i=0; i<boids.size(); i++){
        if (boids[i].getPos()[0] < -2) {
            boids[i].setPos(glm::vec3(2, boids[i].getPos()[1], boids[i].getPos()[2]));
        }
        if (boids[i].getPos()[0] > 2) {
            boids[i].setPos(glm::vec3(-2, boids[i].getPos()[1], boids[i].getPos()[2]));
        }
        if (boids[i].getPos()[1] < -2) {
            boids[i].setPos(glm::vec3(boids[i].getPos()[0], 2, boids[i].getPos()[2]));
        }
        if (boids[i].getPos()[1] > 2) {
            boids[i].setPos(glm::vec3(boids[i].getPos()[0], -2, boids[i].getPos()[2]));
        }
        if (boids[i].getPos()[2] < -2) {
            boids[i].setPos(glm::vec3(boids[i].getPos()[0], boids[i].getPos()[1], 2));
        }
        if (boids[i].getPos()[2] > 2) {
            boids[i].setPos(glm::vec3(boids[i].getPos()[0], boids[i].getPos()[1], -2));
        }
    }

}

void Application::checkPredatorBounds(){
        if (p[0].getPos()[0] < -2) {
            p[0].setPos(glm::vec3(2, p[0].getPos()[1], p[0].getPos()[2]));
        }
        if (p[0].getPos()[0] > 2) {
            p[0].setPos(glm::vec3(-2, p[0].getPos()[1], p[0].getPos()[2]));
        }
        if (p[0].getPos()[1] < -2) {
            p[0].setPos(glm::vec3(p[0].getPos()[0], 2, p[0].getPos()[2]));
        }
        if (p[0].getPos()[1] > 2) {
            p[0].setPos(glm::vec3(p[0].getPos()[0], -2, p[0].getPos()[2]));
        }
        if (p[0].getPos()[2] < -2) {
            p[0].setPos(glm::vec3(p[0].getPos()[0], p[0].getPos()[1], 2));
        }
        if (p[0].getPos()[2] > 2) {
            p[0].setPos(glm::vec3(p[0].getPos()[0], p[0].getPos()[1], -2));
        }
}

float Application::distance(glm::vec3 a, glm::vec3 b){
    glm::vec3 d(b-a);
    return length(d);
}

double Application::length(glm::vec3 l){
    return sqrt(pow(l.x,2)+pow(l.y,2)+pow(l.z,2));
}
