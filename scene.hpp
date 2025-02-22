#pragma once
#include"tgaimage.h"

class scene
{
public: 

    //constructor
    scene();
    scene(TGAImage &image);

    // variable image
    TGAImage image_;

    //close canvas and draw
    void sceneFinalize(const std::string& filename);
};