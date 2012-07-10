/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef GEOMETRY_COMPONENT_H
#define GEOMETRY_COMPONENT_H

#include <Component.h>
#include <geometry2/Geometry.h>
#include <base/ResourceManager.h>

#include <string>


class GeometryComponent : public Component
{
        public:
                GeometryComponent(ResourceManager& resmgr, std::string& filename, std::string& texFilename);
                ~GeometryComponent();
                void init();
                void update(unsigned int timestamp);
                void draw();

        private:
                geometry::Geometry* mGeometry;
};

#endif
