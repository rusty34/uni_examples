/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <sar/base/ResourceManager.h>
#include <boost/foreach.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <string>
#include <iostream>

#include <Designer.h>

#ifndef foreach
#define foreach BOOST_FOREACH
#endif

MODULE(Designer);

Designer::Designer(const std::string &name, SystemManager &sysMgr)
        : Module(name, sysMgr)
{

        mSysMgr = &sysMgr;

}


Designer::~Designer()
{
}


void Designer::unload()
{
        foreach(Component* c, cList)
        {
                delete c;
        }

        if(opti!=NULL)
            delete opti;

        if(tLoader!=NULL)
            delete tLoader;
}


void Designer::handleInput(const SDL_Event &event)
{
        switch(event.type)
        {
                case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_SPACE)
                        {
                                std::cout << "I pressed space from designer.cpp\n";
                                //loadFiles();
                                return;
                        }
                        break;
                default:
                        break;
        }
}


void Designer::init(const OptionList &options)
{

        std::string geometry;
        std::string texture;

        geometry = options.find("Geometry")->second;
        texture = options.find("MainTexture")->second;

        //Init Texture Loader/handler
        tLoader = new TextureLoader();

        //Init tracker
        std::string optiStatus = options.find("UseTracker")->second;
        if(optiStatus.compare("true")==0)
                mUseOpti = true;
        else if(optiStatus.compare("false")==0)
                mUseOpti = false;
        else
                mUseOpti = false;

        if(mUseOpti)
            opti = new OptiTracker(options);

        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        //init children
        Component* temp;

        //temp = new Button();
        temp = new Board(mSysMgr->getResMgr());
        //std::cout << "Making Geometry Component.....\n";
        //temp = new GeometryComponent(mSysMgr->getResMgr(), geometry, texture);
        //std::cout << "Geometry Component made successfully.....\n";
        cList.push_back(temp);

        mBoard = (Board*)temp;

        foreach(Component *c, cList)
        {
                c->init();
        }

        //mode.setCurrentMode(Mode::ROTATING);
}


void Designer::update(unsigned int timestamp)
{
        //update tracker position
        //check every X milliseconds
        if(mUseOpti) {
                opti->update(timestamp);
                glm::vec3 trackerPosition = opti->getPosition();
                glm::fquat trackerRotation = opti->getRotation();
        }

        //Check if tracked object is interacting with anything
        //Do something if it is
        //Do something else if it isn't
        
        currentMode = mode.getCurrentMode();

        //update children
        foreach(Component* c, cList)
        {
                switch(currentMode)
                {
                        case Mode::STANDARD:
                                //What to do when no mode is selected?
                                break;
                        case Mode::MOVING:
                                //Get update from tracker
                                //update transform
                                break;
                        case Mode::SCALING:
                                //Get update from tracker
                                //scale transform
                                break;
                        case Mode::ROTATING:
                                //Get update from tracker
                                //rotate transform
                                //c->setRotation(trackerRotation);
                                break;
                        case Mode::SELECTING:
                                //Check if component is being selected
                                //Set selected button
                                selected = c;
                                //highlight button
                                break;
                        default:
                                break;
                }

                c->update(timestamp);
        }
}


void Designer::draw(const Projector *p)
{
        //draw children
        foreach(Component* c, cList)
        {
                c->draw();
        }
}


void Designer::handleMessage(const Message* msg)
{
        if(mUseOpti)
            opti->handleMessage(msg);

        if(tLoader->handleMessage(msg))
        {
                textureList.push_back(tLoader->getNewTexture());
                mBoard->addTexture(30.0f, textureList.back());
        }
}


void Designer::loadTextures(const std::string &cName)
{

}


void Designer::loadFiles()
{
        std::vector<std::string> files;

        tLoader->getDirContents("modules/wcl/designTest/data/", files);

        for(unsigned int i = 0; i < files.size(); i++)
        {
                std::cout << files.at(i) << std::endl;
        }

        //cout << "-----------\n";
        //tLoader->listPath("modules/wcl/designtest/data/");
}


