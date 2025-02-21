#pragma once

#include "utils.hpp"
#include "tgaimage.h"
#include <string>
#include <vector>

typedef vec3<float> vec3f;

class meshAnalyzer
{
public:

    meshAnalyzer();
    meshAnalyzer(std::string filename);
    ~meshAnalyzer();

    
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

private:

    unsigned int numVertices_;
    unsigned int numFaces_;
    unsigned int numElems_;
    TGAImage image_;
    double scaleKnob_;


    std::vector<vec3f> globalVertexCoords_;
    std::vector<std::vector<int> > vertexIdx_;


};