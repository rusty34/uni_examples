/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef DESIGNER_H
#define DESIGNER_H

#include <sar/base/Module.h>
#include <sar/base/Message.h>
#include <sar/base/SystemManager.h>
#include <graphics/Shader.h>
#include <vector>

#include "Component.h"
#include "Button.h"
#include "GeometryComponent.h"
#include "TextureLoader.h"
#include "ModeSelector.h"
#include "OptiTracker.h"
#include "Board.h"

class Designer : public Module
{

        public:
                Designer(const std::string &name, SystemManager &sysMgr);
                ~Designer();
                void handleInput(const SDL_Event &event);
                void init(const OptionList &options);
                void update(unsigned int timestamp);
                void draw(const Projector *p);
                void handleMessage(const Message* msg);

                void unload();
                bool canUnload(){ return true; }

        private:

                SystemManager* mSysMgr;

                //Component List
                std::vector<Component*> cList;
                Component* selected;

                //Modes
                Mode mode;
                int currentMode;

                //Tracker/s
                bool mUseOpti;
                OptiTracker* opti;

                //Texture stuff
                TextureLoader* tLoader;
                Board* mBoard;
                std::vector<graphics::Texture*> textureList;

                void loadTextures(const std::string &cName);
                void loadFiles();

};

#endif
