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

    TGAImage& getCanvas();  // Return reference to shared image

    //close canvas and draw
    void sceneFinalize(const std::string& filename);
};