#include "colourTracker.h"

//constructor and destructor
colourTracker::colourTracker(){
}


colourTracker::~colourTracker(){
}

void colourTracker::setup() { //initialise variables with default values
	setColour(255, 255, 255);
	setPos(0,0);

	m_threshold = 0;
	m_minRad = 10.0f;
	m_maxRad = 100.0f;

	prevNumContours = 0;
}

void colourTracker::update(){
	//sets the values for the computer vision to track the contours based on colour & other values
	m_contour.setThreshold(m_threshold);
	m_contour.setMinAreaRadius(m_minRad);
	m_contour.setMaxAreaRadius(m_maxRad);
	m_contour.setTargetColor(m_colour, ofxCv::TRACK_COLOR_RGB);
}

void colourTracker::draw() {
	int numContours = m_contour.getContours().size(); // the number of contours found

	for (int i = 0; i < numContours; ++i){ //only runs if contours are found
		ofNoFill();
		ofSetColor(ofFloatColor(1.0f, 0.0f, 0.0f));

		cv::Point2f center = m_contour.getCenter(i);
		cv::Rect rect = m_contour.getBoundingRect(i);

		setPos(center.x, center.y); //drawing something at the position of the tracked contour
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);

		ofDrawBitmapString(ofToString(center.x) + ", " + ofToString(center.y), center.x, center.y);
	}

	ofFill();

	if (prevNumContours == 0 && numContours > 0) { //flash a little circle when tracking is gained and lost at the position 
													//of the tracked object
		ofSetColor(ofColor::red);
		ofDrawCircle(m_trackerPos.x, m_trackerPos.y, 30.0);
	}
	else if (prevNumContours > 0 && numContours == 0) {
		ofSetColor(ofColor::black);
		ofDrawCircle(m_trackerPos.x, m_trackerPos.y, 30.0);
	}

	prevNumContours = numContours;
}

void colourTracker::findContour(ofVideoPlayer video){ //finds the contours based on the set tracked colour in update()
	m_contour.findContours(video);
}

void colourTracker::findContour(ofVideoGrabber video) { 
	m_contour.findContours(video);
}
void colourTracker::setColour(float r, float g, float b){ //sets the colour to be tracked
	m_colour.r = r;
	m_colour.g = g;
	m_colour.b = b;
}

void colourTracker::setPos(int x, int y) { // sets the position of the tracker
	m_trackerPos.x = x;
	m_trackerPos.y = y;
}