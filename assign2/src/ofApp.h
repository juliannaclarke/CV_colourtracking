#pragma once

#include "ofMain.h"
#include "colourTracker.h"

#include "ofxImGui.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

#define USE_WEB_CAM true

	public:
		void setup();
		void update();
		void draw();

		ofVideoPlayer m_video;
		ofVideoGrabber m_webcam;

		ofxImGui::Gui m_gui;

		float distance;

		ofImage m_collision;

		//generate instances of colour tracker objects
		colourTracker tracker1;
		colourTracker tracker2;

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
};
