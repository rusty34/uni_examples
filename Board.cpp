/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include "Board.h"

#include <iostream>
#include <algorithm>

#include <boost/foreach.hpp>
#ifndef foreach
    #define foreach BOOST_FOREACH
#endif


Board::Board(ResourceManager& resMgr)
{
}


Board::Board(wcl::SMatrix offset, ResourceManager& resMgr)
{
}


Board::~Board()
{
        /*delete displayImage;
        delete nextImage;
        delete prevImage;
        delete selectImage;*/

        foreach(Button* b, buttonList)
        {
                delete b;
        }

        foreach(Sample* s, sampleList)
        {
                delete s;
        }

        delete mTransform;
}


void Board::init()
{
        totalArea = 100.0f;
        sampleCount = 0;
        mTransform = new geometry::TrackerTransform();

        /*displayImage = new geometry::Texture("data/displayImage.bmp");
        nextImage = new geometry::Texture("data/nextImage.bmp");
        prevImage = new geometry::Texture("data/prevImage.bmp");
        selectImage = new geometry::Texture("data/selectImage.bmp");*/

        currentMode = DEFAULT;

        //Set up buttons
        Button* nextButton = new Button;
        nextButton->height = 20;
        nextButton->width = 20;
        nextButton->xOffset = 10;
        nextButton->yOffset = BOARD_HEIGHT/2 - nextButton->height/2;
        nextButton->anchor = TOP_LEFT;

        buttonList.push_back(nextButton);
        
        Button* prevButton = new Button;
        prevButton->height = 20;
        prevButton->width = 20;
        prevButton->xOffset = BOARD_WIDTH-30;
        prevButton->yOffset = BOARD_HEIGHT/2 - prevButton->height/2;
        prevButton->anchor = TOP_RIGHT;

        buttonList.push_back(prevButton);

        Button* selectButton = new Button;
        selectButton->height = 20;
        selectButton->width = 50;
        selectButton->xOffset = BOARD_WIDTH/2 - 25;
        selectButton->yOffset = BOARD_HEIGHT - 30;
        selectButton->anchor = TOP_LEFT;

        buttonList.push_back(selectButton);

        remainingArea = new Sample;
        remainingArea->area = totalArea;
        remainingArea->texture = NULL;

        sampleList.push_back(remainingArea);
        sampleCount++;
}


void Board::update(unsigned int timestamp)
{
        //Get position from vrpn
        //Update transform
}


void Board::addTexture(float faceArea, graphics::Texture* image)
{
        Sample* temp = new Sample;
        temp->area = faceArea;
        temp->texture = image;

        remainingArea->area -= faceArea;
        if(remainingArea->area < 0.0f)
                remainingArea->area = 0.0f;

        sampleList.push_back(temp);
        sampleCount++;

        std::sort(sampleList.begin(), sampleList.end());
}


void Board::drawSamples()
{
        float startX, startY, endX, endY, remArea;

        startX = 0.0f;
        startY = 0.0f;
        endX = 1.0f;
        endY = 1.0f;
        remArea = 1.0f;

        for(int x = 0; x<sampleCount; x++)
        {

                float overallPercent = sampleList[x]->area / totalArea;
                if(overallPercent > 1.0f)
                        overallPercent = 1.0f;

                remArea -= overallPercent;
                if(remArea < 0.0f)
                        remArea = 0.0f;

                //float remPercent = 1.0f - remArea;
                float remX = 1.0f - startX;
                float remY = 1.0f - startY;

                int remainder = x % 2;
                //remainder = 0 = Even x
                //remainder = 1 = Odd x
                if(remainder == 0)
                {
                        endX = startY + overallPercent / remY;
                        endY = 1.0f;
                }
                else if(remainder == 1)
                {
                        endX = 1.0f;
                        endY = startY + overallPercent / remX;
                }

                glColor3f(1.0f, 1.0f, 1.0f);

                if(sampleList[x]->texture!=NULL)
                {
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        sampleList[x]->texture->bind();
                }

                //Clap values
                if(startX < 0.0f)
                        startX = 0.0f;
                if(startY < 0.0f)
                        startY = 0.0f;
                if(endX > 1.0f)
                        endX = 1.0f;
                if(endY > 1.0f)
                        endY = 1.0f;

                //std::cout << "Drawing sample\n";
                
                //draw sample
                glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(BOARD_WIDTH*startX, 0, -BOARD_HEIGHT*startY);
                glTexCoord2f(1, 0);
                glVertex3f(BOARD_WIDTH*endX, 0, -BOARD_HEIGHT*startY);
                glTexCoord2f(1,1);
                glVertex3f(BOARD_WIDTH*endX, 0, -BOARD_HEIGHT*endY);
                glTexCoord2f(0,1);
                glVertex3f(BOARD_WIDTH*startX, 0, -BOARD_HEIGHT*endY);
                glEnd();

                if(sampleList[x]->texture!=NULL)
                        sampleList[x]->texture->disable();

                if(remainder == 0)
                {
                        startX = endX;
                }
                else if(remainder == 1)
                {
                        startY = endY;
                }
        }
}


void Board::draw()
{
        glPushMatrix();
        {
                glMultMatrixd(transpose(mTransform->getTransform())[0]);
                glDisable(GL_DEPTH_TEST);

                if(mTexture!=NULL)
                {
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        mTexture->bind();
                }
                else
                {
                        glColor3f(0.3f, 0.3f, 0.3f);
                }

                glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex3f(0, 0, 0);
                glTexCoord2f(1,0);
                glVertex3f(BOARD_WIDTH, 0, 0);
                glTexCoord2f(1,1);
                glVertex3f(BOARD_WIDTH, 0, -BOARD_HEIGHT);
                glTexCoord2f(0,1);
                glVertex3f(0, 0, -BOARD_HEIGHT);
                glEnd();

                if(mTexture!=NULL)
                    mTexture->disable();

                drawSamples();

                //Draw Buttons
                glColor3f(0.5f, 0.5f, 0.5f);
                float anchorXOffset = 0.0f;
                float anchorYOffset = 0.0f;
                foreach (Button* b, buttonList)
                {
                        switch(b->anchor)
                        {
                                case TOP_LEFT:
                                        anchorXOffset = 0.0f;
                                        anchorYOffset = 0.0f;
                                        break;
                                case TOP_RIGHT:
                                        anchorXOffset = -b->width;
                                        anchorYOffset = 0.0f;
                                        break;
                                case BOTTOM_LEFT:
                                        anchorXOffset = 0.0f;
                                        anchorYOffset = b->height;
                                        break;
                                case BOTTOM_RIGHT:
                                        anchorXOffset = -b->width;
                                        anchorYOffset = b->height;
                                        break;
                                case CENTER:
                                        anchorXOffset = b->width/2;
                                        anchorYOffset = -(b->height/2);
                                        break;
                                default:
                                        anchorXOffset = 0.0f;
                                        anchorYOffset = 0.0f;
                                        break;
                        }

                        float originX = b->xOffset + anchorXOffset;
                        float originY = b->yOffset + anchorYOffset;
                        
                        glBegin(GL_QUADS);
                        glTexCoord2f(0,0);
                        glVertex3f(originX, 0.0f, -originY);
                        glTexCoord2f(1,0);
                        glVertex3f(originX+b->width, 0.0f, -originY);
                        glTexCoord2f(1,1);
                        glVertex3f(originX+b->width, 0.0f, -originY-b->height);
                        glTexCoord2f(0,1);
                        glVertex3f(originX, 0.0f, -originY-b->height);
                        glEnd();

                }

                glEnable(GL_DEPTH_TEST);
        }
        glPopMatrix();

}


