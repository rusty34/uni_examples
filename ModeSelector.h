/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef MODESELECTOR_H
#define MODESELECTOR_H


class Mode
{

        public:
                Mode() { currentMode = STANDARD; }
                Mode(int mode) { currentMode = mode; }
                ~Mode() {};
                int getCurrentMode() { return currentMode; }
                void setCurrentMode(int mode) { currentMode = mode; }

                enum Modes
                {
                        STANDARD,
                        MOVING,
                        SCALING,
                        ROTATING,
                        SELECTING
                };

        private:
                int currentMode;
};

#endif
