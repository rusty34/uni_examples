/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef BOARD_H
#define BOARD_H

#include "Component.h"

#include <base/OpenGL.h>
#include <graphics/Texture.h>
#include <base/ResourceManager.h>
#include <geometry2/TrackerTransform.h>

#include <wcl/maths/Vector.h>
#include <wcl/maths/SMatrix.h>

#include <vector>

#define BOARD_WIDTH 700
#define BOARD_HEIGHT 200

#define BUTTON_SPACING 9


class Board : public Component
{

        public:
                enum Mode
                {
                        ADD,
                        SELECT,
                        BROWSE,
                        DEFAULT
                };

                enum Anchor
                {
                        TOP_LEFT,
                        TOP_RIGHT,
                        BOTTOM_LEFT,
                        BOTTOM_RIGHT,
                        CENTER
                };

                struct Button
                {
                        float height;
                        float width;
                        float xOffset;
                        float yOffset;
                        Anchor anchor;
                };

                struct Sample
                {
                        float area;
                        graphics::Texture* texture;
                        bool operator<(Sample* rhs) { return area < rhs->area; }
                };

                Board(ResourceManager& resMgr);
                Board(wcl::SMatrix offset, ResourceManager& resMgr);
                ~Board();

                void init();
                void update(unsigned int timestamp);
                void draw();

                void setMode(Mode m){ currentMode = m; }

                void addTexture(float faceArea, graphics::Texture* image);

        private:

                float totalArea;
                int sampleCount;

                geometry::TrackerTransform* mTransform;

                Mode currentMode;

                std::vector<Button*> buttonList;

                Sample* remainingArea;
                std::vector<Sample*> sampleList;

                graphics::Texture* displayImage;
                graphics::Texture* nextImage;
                graphics::Texture* prevImage;
                graphics::Texture* selectImage;

                void drawSamples();

};

#endif


