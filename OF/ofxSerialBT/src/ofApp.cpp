//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{

    ofSetWindowShape(600, 400);
    ofSetFrameRate(30);
	ofLogToConsole();

    // 1. Upload the `Echo.ino` sketch (in this example's `Arduino/` folder) to
    // an Arduino-compatible board.
    //
    // 2. Check the "listDevices" call in the `ofApp::setup()` function to make
    // sure the correct serial device is connected.
    //
    // 3. Run this app.

    //serial.setup("COM4", 115200);

    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";


    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }

    if (!devicesInfo.empty())
    {
        int port = 0; //使用可能なポートの何番目か

        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[port], 115200);

        if (success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[port];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[port];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }


}


void ofApp::update()
{
    // The serial device can throw exeptions.
    try
    {
        // Read all bytes from the device;
        uint8_t buffer[1024];
        static string str;

        while (device.available() > 0)
        {
            std::size_t sz = device.readBytes(buffer, 1024);

			string outputString = "";

            for (std::size_t i = 0; i < sz; ++i)
            {
                //コメントアウト std::cout << buffer[i];

				char c = buffer[i];
				//ASCII 0 〜9 
				if (c >= 48 && c <= 57)
				{
					outputString += c;
				}

				if (i != 0 && buffer[i - 1] == '\r') {

					if (outputString != "")
					{
						outputNum = stoi(outputString);
						//コメントアウト　std::cout << "data:";
						ofLog(OF_LOG_NOTICE, "data:" + outputString);
						outputString = "";  //初期化

					}
				}
            }
        }
 

        // Send some new bytes to the device to have them echo'd back.
        std::string text = "Frame Number: " + ofToString(ofGetFrameNum());
        ofx::IO::ByteBuffer textBuffer(text);
        device.writeBytes(textBuffer);
        device.writeByte('\n');
    }
    catch (const std::exception & exc)
    {
        ofLogError("ofApp::update") << exc.what();
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("Connected to " + device.port(), 200, 200);
    //ofDrawBitmapStringHighlight("Connected to " + device.
    ofDrawBitmapStringHighlight("See Console.", 20, 45);

}

