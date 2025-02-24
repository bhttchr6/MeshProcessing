#include "mesh.hpp"
#include "tgaimage.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

#define width  1920
#define height  1080

// default constructor

meshAnalyzer::meshAnalyzer():sharedScene_(nullptr)
{
    throw std::invalid_argument(" Mesh not defined");
}

// constructor
meshAnalyzer::meshAnalyzer(std::string filename, bool flag, std::shared_ptr<scene> scenePtr):sharedScene_(scenePtr), scene(*scenePtr)
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
                if(flag)
                {
                    //std::cout << "clean obj file provided" << std::endl;
                    int vertexId1, vertexId2, vertexId3;

                    iss >> c >> vertexId1 >> vertexId2 >> vertexId3;
                    std::vector<int> vertexIds;
                    vertexIds.push_back(vertexId3--);
                    vertexIds.push_back(vertexId2--);
                    vertexIds.push_back(vertexId1--);

                    vertexIdx_.push_back(vertexIds);
                }
                
                
                
                if(!flag)
                {
                    std::vector<int> f;
                    int itrash, idx;
                    iss >> c;
                    while (iss >> idx >> c >> itrash >> c >> itrash) {
                        idx--; // in wavefront obj all indices start at 1, not zero
                        f.push_back(idx);
                    }
                    vertexIdx_.push_back(f);
                }
                
                


            }
        }
        
    }

    numElems_ = vertexIdx_.size();
    numVertices_ = globalVertexCoords_.size();
    numFaces_ = vertexIdx_.size();
    //TGAImage image(width, height, TGAImage::RGB);
    //image_ = image;
    scaleKnob_ = 100;

    // evaluate the center of mass
    float xCOM = 0, yCOM = 0, zCOM = 0; 
    for(unsigned int i = 0; i < globalVertexCoords_.size(); i++)
    {
        vec3f vertexCoordinates = globalVertexCoords_[i];
        float xCoords = vertexCoordinates.x;
        float yCoords = vertexCoordinates.y;
        float zCoords = vertexCoordinates.z;

        xCOM = xCOM + xCoords;
        yCOM = yCOM + yCoords;
        zCOM = zCOM + zCoords;

    }

    vec3f centerOfMass_;
    centerOfMass_.x = xCOM / globalVertexCoords_.size();
    centerOfMass_.y = yCOM / globalVertexCoords_.size();
    centerOfMass_.z = zCOM / globalVertexCoords_.size();
    
    



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

 vec3f meshAnalyzer::getCenterOfMass()
 {
    return centerOfMass_;
 }

 void meshAnalyzer::drawLine(vec3f point1, vec3f point2, std::string color)
 {
    TGAColor lineColor = color == "red" ? TGAColor(255, 0,   0,   255): TGAColor(255, 255, 255,  255);

    
    // evaluate the slope of the line
    double slope = 0;
    int numSteps = 100;
    // the scale knob is an important parameter
    //double scaleKnob = 400.0;
    double scalex = width/scaleKnob_;
   double scaley  = height/scaleKnob_;
   point1.x = point1.x/scalex;
   point1.y = point1.y / scaley;

   point2.x = point2.x /scalex;
   point2.y = point2.y /scaley;
    if((point2.x > point1.x) && (point2.y > point1.y)) //quad 2
    {
        //std::cout << "here in quad 1" <<std::endl;
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = (point2.x - point1.x)/ numSteps;
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x + i*deltaX;
            //std::cout << x_i <<std::endl;
            double y_i = point1.y + slope * i*deltaX;
            //std::cout << y_i <<std::endl;
            x_i = (x_i + 1)* width/2;
            y_i = (y_i + 1)* height/2;
            
            sharedScene_->getCanvas().set(x_i, y_i, lineColor); 
        }
    }
    else if ((point2.x > point1.x) && (point2.y < point1.y)) // quad 1
    {
        
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = (point2.x - point1.x)/ numSteps;

        //std::cout << "here in quad 1" <<std::endl;
        //std::cout << "slope " << slope <<std::endl;
        //std::cout << "deltaX" <<  deltaX <<std::endl;
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x + i * deltaX;
            double y_i = point1.y + slope * i * deltaX;
            //x_i = x_i < 0 ? x_i*width/2.0 + width: x_i*width/2.0;
            //y_i = y_i < 0 ? y_i*height/2.0 + height: y_i*height/2.0;
            x_i = (x_i + 1)* width/2;
            y_i = (y_i + 1)* height/2;

            //std::cout << x_i <<std::endl;
            //std::cout << y_i <<std::endl;
            sharedScene_->getCanvas().set(x_i, y_i, lineColor); 
        } 
    }
    else if ((point2.x < point1.x) && (point2.y > point1.y)) // quad 3
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = std::abs((point2.x - point1.x)/ numSteps);
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x - i * deltaX;
            double y_i = point1.y - slope * i * deltaX;

            //x_i = x_i < 0 ? x_i*width/2.0 + width: x_i*width/2.0;
            //y_i = y_i < 0 ? y_i*height/2.0 + height: y_i*height/2.0;
            x_i = (x_i + 1)* width/2;
            y_i = (y_i + 1)* height/2;
            sharedScene_->getCanvas().set(x_i, y_i, lineColor); 
        } 

    }

    else if ((point2.x < point1.x) && (point2.y < point1.y)) // quad 4
    {
        slope = (point2.y - point1.y) / (point2.x - point1.x);
        double deltaX = std::abs((point2.x - point1.x)/ numSteps);
        for(int i = 0; i < numSteps; i++)
        {
            double x_i = point1.x - i * deltaX;
            double y_i = point1.y - slope * i * deltaX;
            //x_i = x_i < 0 ? x_i*width/2.0 + width: x_i*width/2.0;
            //y_i = y_i < 0 ? y_i*height/2.0 + height: y_i*height/2.0;
            x_i = (x_i + 1)* width/2;
            y_i = (y_i + 1)* height/2;
            sharedScene_->getCanvas().set(x_i, y_i, lineColor); 
        } 

    }
    
    
 }

 void meshAnalyzer::setScaleKnob(double scaleValue)
 {
    scaleKnob_ = scaleValue;
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
    

    //image_.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    //image_.write_tga_file("output.tga");
    
 }

 void meshAnalyzer::saveImage(const std::string& filename) {
    sharedScene_->sceneFinalize(filename);
}

 


