//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    ofx::IO::SerialDevice device;
    ofSerial serial;
    float logText;

};
