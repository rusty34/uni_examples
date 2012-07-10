/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#include <base/Message.h>
#include <image/AbstractImage.h>

#define MESSAGE_IMAGE_SEND "LibSAR Image Send Message"

class MessageType
{
        public:

                struct SAR_API ImageMessage
                {
                        Message::Type type;
                        uint8_t flags;
                        uint32_t length;

                        uint32_t height;
                        uint32_t width;
                        uint8_t bpp;
                        image::AbstractImage::ImageFormat format;

                        unsigned char* data;
                };
};

#endif


