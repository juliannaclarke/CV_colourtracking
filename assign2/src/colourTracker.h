#pragma once
#include "ofMain.h"
#include "ofxCv.h"

class colourTracker {

public:

	colourTracker();
	~colourTracker();

	ofVec2f m_trackerPos;
	ofColor m_colour;
	ofxCv::ContourFinder m_contour;

	int m_threshold;
	float m_minRad;
	float m_maxRad;

	int prevNumContours;

	void setup();
	void update();
	void draw();

	void findContour(ofVideoPlayer video);
	void findContour(ofVideoGrabber video);

	void setColour(float r, float g, float b);
	void setPos(int x, int y);
};