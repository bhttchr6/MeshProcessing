#include "scene.hpp"
#include "tgaimage.h"
#include <iostream>

scene::scene()
{ 
    throw std::invalid_argument(" No canvas created");
}

scene::scene(TGAImage &imageInput): image_(imageInput){}

void scene::sceneFinalize(const std::string& filename)
{
    image_.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image_.write_tga_file(filename.c_str());

    
}