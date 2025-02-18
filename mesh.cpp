#include "mesh.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// default constructor
meshAnalyzer::meshAnalyzer() 
{
    throw std::invalid_argument(" Mesh not defined");
}

// constructor
meshAnalyzer::meshAnalyzer(std::string filename)
{
    

    
    //read file
    std::ifstream file;
    file.open(filename);

    if(file.is_open())
    {
        
        std::string line;
        while(!file.eof())
        {
            std::getline(file, line);
            std::istringstream iss(line);
            char c;

            if (!line.compare(0, 2, "v "))
            {
                vec3f coords;
                float coordsX, coordsY, coordsZ;
                
                iss >> c >> coordsX  >> coordsY >> coordsZ;
                coords.x = coordsX;
                coords.y = coordsY;
                coords.z = coordsZ;
                globalVertexCoords_.push_back(coords);
                
            }

            if(!line.compare(0, 2, "f "))
            {
                int vertexId1, vertexId2, vertexId3;

                iss >> c >> vertexId1 >> vertexId2 >> vertexId3;
                std::vector<int> vertexIds;
                vertexIds.push_back(vertexId3);
                vertexIds.push_back(vertexId2);
                vertexIds.push_back(vertexId1);

                vertexIdx_.push_back(vertexIds);


            }
        }
        
    }

    numElems_ = vertexIdx_.size();
    numVertices_ = globalVertexCoords_.size();
    numFaces_ = vertexIdx_.size();
    



}

meshAnalyzer::~meshAnalyzer(){}

unsigned int meshAnalyzer::getNE()
{
    return numElems_;
}

unsigned int meshAnalyzer::getNVertices()
{
    return numVertices_;
}

unsigned int meshAnalyzer::getNFaces()
{
    return numFaces_;
}

vec3f meshAnalyzer::getIndividualVertexCoord(unsigned int vertexIdx)
{
    vec3f vcoords = globalVertexCoords_[vertexIdx];

    return vcoords;
}

 std::vector<int> meshAnalyzer::getVertexIdsForFace(unsigned int faceIdx)
 {
    std::vector<int> vids = vertexIdx_[faceIdx];
    return vids;

 }


