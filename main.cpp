#include <iostream>
#include <string>
#include <memory>
#include "utils.hpp"
#include "mesh.hpp"
#include "scene.hpp"

#define width  1920
#define height  1080

int main(int argc, char* argv[])
{
    
    TGAImage image(width, height, TGAImage::RGB);
    std::shared_ptr<scene> sharedScene = std::make_shared<scene>(image);
    //scene canvas(image);
    
    
    std::string filename1 = "head.obj";
    std::string filename2 = "shuttle.obj";
    bool cleanOBJ1 = false;
    bool cleanOBJ2 = true;
    if(argc > 1)
    {
        filename1 = argv[1];
    }
    
    // create memory location
    
    std::unique_ptr<meshAnalyzer> mesh1  = std::make_unique<meshAnalyzer>(filename1, cleanOBJ1, sharedScene);
    std::unique_ptr<meshAnalyzer> mesh2  = std::make_unique<meshAnalyzer>(filename2, cleanOBJ2, sharedScene);
    
    std::cout << "Number of faces = " << mesh1->getNFaces() << std::endl;
    std::cout << "Number of vertices = " << mesh1->getNVertices() << std::endl;

    std::cout << "Number of faces = " << mesh2->getNFaces() << std::endl;
    std::cout << "Number of vertices = " << mesh2->getNVertices() << std::endl;

    
    mesh1->setScaleKnob(600); // 600 for head
    mesh1->drawMesh("red");
    vec3f COM_1 = mesh1->getCenterOfMass();
    std::cout << "center of mass for mesh 1" << COM_1.x <<" " << COM_1.y<<" " << COM_1.z << std::endl;

    vec3f COM_2 = mesh2->getCenterOfMass();
    std::cout << "center of mass for mesh 2" << COM_2.x <<" " << COM_2.y<<" " << COM_2.z << std::endl;

    mesh2->setScaleKnob(100); // 600 for head
    mesh2->drawMesh("white");
    mesh2->drawBoundingBox("white");

    mesh1->saveImage("output.tga");
    
    return 1;
}