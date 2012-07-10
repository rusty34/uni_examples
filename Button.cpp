/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include <Button.h>
#include <iostream>
#include <sar/base/OpenGL.h>

Button::Button()
{
        //Also calls Component constructor class
}


Button::~Button()
{

}


void Button::init()
{

        //glDisable(GL_CULL_FACE);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CW);
        //std::cout << "BUTTON INIT" << std::endl;
                
}


void Button::update(unsigned int timestamp)
{
        


}


void Button::draw()
{
        //std::cout << "button DRAW" << std::endl;

        glPushMatrix();

                if(mTexture!=NULL)
                {
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

                        mTexture->bind();
                }
                else
                {
                        glColor3f(0.0f, 1.0f, 0.0f);
                }

                glBegin(GL_QUADS);

                glNormal3f(0.0f, 1.0f, 0.0f);

                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-100.5f, 0.0f, -100.5f);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(100.5f, 0.0f, -100.5f);

                glTexCoord2f(1.0f,1.0f);
                glVertex3f(100.5f, 0.0f, 100.5f);

                glTexCoord2f(0.0f,1.0f);
                glVertex3f(-100.5f, 0.0f, 100.5f);

                glEnd();

        glPopMatrix();

}


