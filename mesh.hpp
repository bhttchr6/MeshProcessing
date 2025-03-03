#pragma once

#include "utils.hpp"
#include "tgaimage.h"
#include "scene.hpp"
#include <string>
#include <vector>
#include <memory>

typedef vec3<float> vec3f;

class meshAnalyzer: public scene
{
public:

    meshAnalyzer();
    meshAnalyzer(std::string filename, bool flag, std::shared_ptr<scene> scenePtr);
    virtual ~meshAnalyzer();

    
    // get number of elements
    unsigned int getNE();

    //get number of vertices
    unsigned int getNVertices();

    // get number of faces
    unsigned int getNFaces();

    //get the vertex coords for an individual vextex
    vec3f getIndividualVertexCoord(unsigned int vertexIdx);

    // get the indices associated with a faceId
    std::vector<int> getVertexIdsForFace(unsigned int faceIdx);

    // draw the mesh
    void drawMesh(std::string color);

    //draw a line between two points
    void drawLine(vec3f p1, vec3f p2, std::string color);

    //set scale knob
    void setScaleKnob( double scaleValue);

    void saveImage(const std::string& filename);  // New function to save image

    vec3f getCenterOfMass();

    void drawCOM();

    void drawBoundingBox(std::string color);


private:

    vec3f centerOfMass_;
    unsigned int numVertices_;
    unsigned int numFaces_;
    unsigned int numElems_;
    double scaleKnob_;
    // get the bounding box coordinates
    double xMax_, yMax_, zMax_;
    double xMin_, yMin_, zMin_;
    std::shared_ptr<scene> sharedScene_;  // Shared scene instance
    


    std::vector<vec3f> globalVertexCoords_;
    std::vector<std::vector<int> > vertexIdx_;


};