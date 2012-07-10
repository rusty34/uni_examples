/*
    Spatial AR Framework - CBL

    Copyright (c) 2012 Shane Porter

    If you use/extend/modify this code, add your name and email address
    to the AUTHORS file in the root directory.

    This code can be used by members of the Wearable Computer Lab, University
    of South Australia for research purposes. Commercial use is not allowed
    without written permission. This copyright notice is subject to change.
*/
    
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <boost/foreach.hpp>

#include <image/AbstractImage.h>
#include <image/BufferedImage.h>

#include "TextureLoader.h"
#include "MessageType.h"

#define MESSAGE_IMAGE_SEND "LibSAR Image Send Message"

#ifndef foreach
#define foreach BOOST_FOREACH
#endif

TextureLoader::TextureLoader()
{

}


TextureLoader::~TextureLoader()
{

        foreach(graphics::Texture* t, textureList)
        {
                delete t;
        }

}


bool TextureLoader::handleMessage(const Message* msg)
{
        if(msg->type == Message::hashType(MESSAGE_IMAGE_SEND))
        {
               const MessageType::ImageMessage* im = reinterpret_cast<const MessageType::ImageMessage*>(msg); 

               unsigned int height = im->height;
               unsigned int width = im->width;
               image::AbstractImage::ImageFormat format = im->format;

               //std::cout << "Height " << height << ", Width " << width << std::endl;
               std::cout << "Making BufferedImage\n";
               //std::cout << (int)im->data[40] << " " << (int)im->data[41] << " " << (int)im->data[42] << " " << (int)im->data[43] << std::endl;

               /*int numBytes = height * width * im->bpp;
               for(int i = 0; i<numBytes; i+=4)
               {
                       std::cout << (int)im->data[i] << " " << (int)im->data[i+1] << " " << (int)im->data[i+2] << " " << (int)im->data[i+3] << std::endl;
               }*/

               image::BufferedImage* image = new image::BufferedImage(width, height, format, im->data);
               graphics::Texture* texture = new graphics::Texture(image);

               textureList.push_back(texture);

               return true;
        }

        return false;
}


graphics::Texture* TextureLoader::getTextureAt(unsigned int i)
{
        if(i >= textureList.size())
                throw SARException("Array index out of bounds - TextureLoader");

        return textureList[i];
}


graphics::Texture* TextureLoader::getNewTexture()
{
        return textureList.back();
}


int TextureLoader::getFullDir(std::string dir, std::vector<std::string> &files)
{
        std::vector<std::string> contents;
        getDirContents(dir, contents);

        for(unsigned int i = 0; i < contents.size(); i++)
        {
                std::string new_name = contents.at(i);
                std::cout << new_name << std::endl;
        }

        return 0;
}


int TextureLoader::getDirContents(std::string dir, std::vector<std::string> &files)
{

        DIR *directory;
        struct dirent *dirp;

        if((directory = opendir(dir.c_str())) == NULL)
        {
                std::cout << "Error opening " << dir << std::endl;
                return 1;
        }


        while((dirp = readdir(directory)) != NULL)
        {

                if(dirp->d_name[0]!='.')
                {

                        std::stringstream fullFilename;
                        fullFilename << dir;
                        fullFilename << dirp->d_name;

                        if(dirp->d_type == DT_DIR)
                        {
                                fullFilename << "/";
                                std::cout << "directory: " << fullFilename.str() << std::endl;
                                getDirContents(fullFilename.str(), files);
                        }
                        else if(dirp->d_type == DT_REG)
                        {
                                std::cout << "file: " << fullFilename.str() << std::endl;
                                files.push_back(fullFilename.str());
                        }

                }
        }
        
        closedir(directory);

        return 0;
}


/*void TextureLoader::listPath(const char* dir)
{
        listPath(path(dir));
}*/


/*void TextureLoader::listPath(path p)
{
        try
        {
                if(exists(p))
                {
                        if(is_regular_file(p))
                        {
                                //Add to list
                        }
                        else if (is_directory(p))
                        {
                                cout << p << " contains:\n";

                                //Show folder
                                typedef vector<path> vec;
                                vec v;

                                copy(directory_iterator(p), directory_iterator(), back_inserter(v));
                                sort(v.begin(), v.end());

                                for(vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
                                {
                                        cout << "   " << *it << '\n';
                                }
                        }
                        else
                        {
                                cout << p << " exists, but is not a file or a directory.\n";
                        }
                }
                else
                {
                        cout << p << " does not exist.\n";
                }
        }
        catch (const filesystem_error& e)
        {
                cout << e.what() << '\n';
        }

}*/


