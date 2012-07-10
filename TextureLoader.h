/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <base/Message.h>
#include <graphics/Texture.h>

#include <string>
#include <vector>

class TextureLoader
{

        public:
                TextureLoader();
                ~TextureLoader();

                int getFullDir(std::string dir, std::vector<std::string> &files);
                int getDirContents(std::string dir, std::vector<std::string> &files);

                bool handleMessage(const Message* msg);
                graphics::Texture* getNewTexture();
                graphics::Texture* getTextureAt(unsigned int i);

                //void listPath(const char* dir);
                //void listPath(path p);
                
        private:

                std::vector<graphics::Texture*> textureList;

};
#endif
