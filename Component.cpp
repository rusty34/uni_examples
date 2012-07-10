/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include <Component.h>
#include <iostream>

Component::Component()
        : mTexture(0), id(0)
{
}


Component::~Component()
{

}


void Component::init()
{
}


void Component::update(unsigned int timestamp)
{

}


void Component::draw()
{

}


void Component::setTexture(graphics::Texture* t)
{
        delete mTexture;
        mTexture = t;
}


