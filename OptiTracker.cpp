/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include "OptiTracker.h"
#include <iostream>


OptiTracker::OptiTracker(const OptionList& options) :
        tracker(""), debug(false), oldTime(0)
{
        for(OptionList::const_iterator option = options.begin(); option != options.end(); ++option)
        {
                if(option->first == "Tracker")
                {
                        tracker = option->second;
                        std::cout << "Listening to tracker - " << tracker << std::endl;
                }

                if(option->first == "Debug")
                {
                        if(option->second == "TRUE" || option->second == "true" || option->second == "True")
                                debug = true;

                        std::cout << (debug?"R":"Not r") << "eporting tracker data." << std::endl;
                }
        }
}


OptiTracker::~OptiTracker()
{

}


void OptiTracker::update(unsigned int timestamp)
{
        //Print tracker position every half a second
        if(timestamp - oldTime > 500)
        {
                oldTime = timestamp;
                std::cout << "-------------" << std::endl;
                std::cout << tracker << " Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
                std::cout << tracker << " Rotation: (" << rotation.w << ", " << rotation.x << ", " << rotation.y << ", " << rotation.z << ")" << std::endl; 
        }
}


void OptiTracker::handleMessage(const Message* msg)
{
        if(msg->type == Message::hashType(MESSAGE_TRACKER_UPDATE))
        {
                const TrackerMessage* tm = reinterpret_cast<const TrackerMessage*>(msg);

                if(std::string(tm->id) == tracker)
                {
                        position.x = tm->translation.x;
                        position.y = tm->translation.y;
                        position.z = tm->translation.z;

                        rotation.w = tm->orientation.w;
                        rotation.x = tm->orientation.x;
                        rotation.y = tm->orientation.y;
                        rotation.z = tm->orientation.z;
                }
        }
}


