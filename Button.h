/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <Component.h>
#include <graphics/Texture.h>

class Button : public Component
{

        public:
                Button();
                ~Button();
                void init();
                void update(unsigned int timestamp);
                void draw();

};

#endif
