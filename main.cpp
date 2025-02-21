#include <iostream>
#include <string>
#include <memory>
#include "utils.hpp"
#include "mesh.hpp"


int main(int argc, char* argv[])
{
    std::string filename = "mesh.obj";
    if(argc > 1)
    {
        filename = argv[1];
    }
    
    // create memory location
    std::unique_ptr<meshAnalyzer> mesh  = std::make_unique<meshAnalyzer>(filename);
    
    std::cout << "Number of faces = " << mesh->getNFaces() << std::endl;
    std::cout << "Number of vertices = " << mesh->getNVertices() << std::endl;

    mesh->drawMesh("red");

    return 1;
}