/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include <GeometryComponent.h>
#include <sar/base/OpenGL.h>

GeometryComponent::GeometryComponent(ResourceManager& resmgr, std::string& filename, std::string& texFilename)
        : mGeometry(0)
{

        mGeometry = resmgr.getGeometry(filename);
        mTexture = new graphics::Texture(resmgr.getImage(texFilename));

}


GeometryComponent::~GeometryComponent()
{
        delete mTexture;
}


void GeometryComponent::init()
{
        //glDisable(GL_CULL_FACE);
}


void GeometryComponent::update(unsigned int timestamp)
{
}


void GeometryComponent::draw()
{
        
        glPushMatrix();

                //glScalef(200.0f, 200.0f, 200.0f);

                if(mTexture!=NULL)
                {
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        mTexture->bind();
                }
                else
                {
                        glColor3f(0.0f, 1.0f, 0.0f);
                }
 
                mGeometry->draw();

                /*mTexture->bind();
                glMatrixMode(GL_TEXTURE);
                glLoadIdentity();
                glTranslatef(x, 0.0f, 0.0f);
                glMatrixMode(GL_MODELVIEW);*/

        glPopMatrix();
}
