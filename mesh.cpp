#include "mesh.hpp"
#include "tgaimage.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define width  800
#define height  800

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
    TGAImage image(width, height, TGAImage::RGB);
    image_ = image;
    



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

 void meshAnalyzer::drawLine(vec3f point1, vec3f point2, std::string color)
 {
    TGAColor lineColor = color == "red" ? TGAColor(255, 0,   0,   255): TGAColor(255, 255, 255,  255);

    // evaluate the slope of the line
    double slope = 0;
    int numSteps = 10;
    if((point2.x > point1.x) && (point2.y > point1.y)) //quad 2
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = (point2.x - point1.x)/ numSteps;
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x + deltaX;
            double y_i = point1.y + slope * deltaX;
            image_.set(x_i, y_i, lineColor); 
        }
    }
    else if ((point2.x > point1.x) && (point2.y < point1.y)) // quad 1
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = (point2.x - point1.x)/ numSteps;
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x + deltaX;
            double y_i = point1.y + slope * deltaX;
            image_.set(x_i, y_i, lineColor); 
        } 
    }
    else if ((point2.x < point1.x) && (point2.y > point1.y)) // quad 3
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = std::abs((point2.x - point1.x)/ numSteps);
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x - deltaX;
            double y_i = point1.y - slope * deltaX;
            image_.set(x_i, y_i, lineColor); 
        } 

    }

    else if ((point2.x < point1.x) && (point2.y < point1.y)) // quad 4
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = std::abs((point2.x - point1.x)/ numSteps);
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x - deltaX;
            double y_i = point1.y + slope * deltaX;
            image_.set(x_i, y_i, lineColor); 
        } 

    }
    

    
 }

 void meshAnalyzer::drawMesh( std::string color)
 {
    // go to each face
    for(unsigned int i = 0; i<numFaces_; i++)
    {
        std::vector<int> vertIds = vertexIdx_[i];
        for(unsigned int j = 0; j< vertIds.size(); j++)
        {
            
            vec3f coordIds1 = globalVertexCoords_[vertIds[j]];
            vec3f coordIds2 = globalVertexCoords_[vertIds[(j+1)%vertIds.size()]];
            drawLine(coordIds1, coordIds2, color);
        }
    }

    image_.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image_.write_tga_file("output.tga");
 }

 


