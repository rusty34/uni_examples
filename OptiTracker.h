/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef OPTI_TRACKER_H
#define OPTI_TRACKER_H

#include <string>
#include <sar/base/Message.h>
#include <sar/base/SystemManager.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class OptiTracker
{

        public:
                OptiTracker(const OptionList& options);
                ~OptiTracker();
                void update(unsigned int timestamp);
                void handleMessage(const Message* msg);
                glm::vec3 getPosition() { return position; }
                glm::fquat getRotation() { return rotation; }

        private:
                std::string tracker;
                glm::vec3 position;
                glm::fquat rotation;

                bool debug;

                unsigned int oldTime;
};

#endif
