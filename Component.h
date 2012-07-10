/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef COMPONENT_H
#define COMPONENT_H

#include <graphics/Texture.h>
#include <geometry2/Geometry.h>

class Component
{
        public:
                Component();
                ~Component();

                virtual void init();
                virtual void update(unsigned int timestamp); 
                virtual void draw();

                void setTexture(graphics::Texture *t);

                int getType() { return componentType; }

        protected:

                graphics::Texture* mTexture;

                int id;
                int componentType;
                int numberOfVertices;

};


#endif
