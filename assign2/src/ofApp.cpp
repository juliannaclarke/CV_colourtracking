#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	if (USE_WEB_CAM) {
		//set up webcam
		m_webcam.setup(640, 360);
	}
	else { //set up video
		m_video.load("assign2_video.mp4");		//NOTE: this file is not included in the directory because it included video of a person. However, another video file could be loaded here.
		m_video.setLoopState(OF_LOOP_NORMAL);
		m_video.play();
	}

	ofSetFrameRate(23);

	//set up gui
	m_gui.setup();

	//set up trackers
	tracker1.setup();
	tracker2.setup();

	distance = 0;

	m_collision.load("COLLISION.png");
}

//--------------------------------------------------------------
void ofApp::update(){

	tracker1.update();
	tracker2.update();

	if (USE_WEB_CAM) {
		m_webcam.update();

		if (m_webcam.isFrameNew()) {
			tracker1.findContour(m_webcam);
			tracker2.findContour(m_webcam);
		}						 
	}
	else {
		m_video.update();

		if (m_video.isFrameNew()) {
			tracker1.findContour(m_video);
			tracker2.findContour(m_video);
		}
	}

	distance = sqrt(pow((tracker2.m_trackerPos.x - tracker1.m_trackerPos.x), 2) + pow((tracker2.m_trackerPos.y - tracker1.m_trackerPos.y), 2));
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetBackgroundColor(30, 30, 30);
	ofSetColor(255);

	
	if (USE_WEB_CAM) {
		m_webcam.draw(0, 0);
	}
	else {
		m_video.draw(0, 0);
	}

	tracker1.draw();
	tracker2.draw();

	m_gui.begin(); //gui controls
		ImGui::Text("First colour controls");
		ImGui::Text("To select colour one, right mouse click");
		ImGui::SliderInt("Threshold 1", &tracker1.m_threshold, 0, 255);
		ImGui::SliderFloat("Min Radius 1", &tracker1.m_minRad, 0.0f, 500.0f);
		ImGui::SliderFloat("Max Radius 1", &tracker1.m_maxRad, 0.0f, 500.0f);

		ImGui::Text("Second colour controls");
		ImGui::Text("To select colour two, middle mouse click");
		ImGui::SliderInt("Threshold 2", &tracker2.m_threshold, 0, 255);
		ImGui::SliderFloat("Min Radius 2", &tracker2.m_minRad, 0.0f, 500.0f);
		ImGui::SliderFloat("Max Radius 2", &tracker2.m_maxRad, 0.0f, 500.0f);
	m_gui.end();

	ofFill();
	ofSetColor(tracker1.m_colour);
	ofDrawRectangle(20, 500, 40, 40);

	ofSetColor(tracker2.m_colour);
	ofDrawRectangle(80, 500, 40, 40);

	if (distance < 100) { // checks if the centres of the two tracked objects are within 100px of each other
		ofPushMatrix();		//notify a collision if the distance is small enough
		m_collision.setAnchorPoint(ofGetWidth() / 2, ofGetHeight() / 2);
		ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		ofScale(0.4);
		m_collision.draw(0, 0);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		m_video.setPaused(!m_video.isPaused());
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (USE_WEB_CAM) {
		if (button == OF_MOUSE_BUTTON_RIGHT) {
			int index = (x + y * m_webcam.getWidth()) * m_webcam.getPixels().getBytesPerPixel();
			tracker1.setColour(m_webcam.getPixels()[index], m_webcam.getPixels()[index + 1], m_webcam.getPixels()[index + 2]);
		}
		else if (button == OF_MOUSE_BUTTON_MIDDLE) {
			int index = (x + y * m_webcam.getWidth()) * m_webcam.getPixels().getBytesPerPixel();
			tracker2.setColour(m_webcam.getPixels()[index], m_webcam.getPixels()[index + 1], m_webcam.getPixels()[index + 2]);
		}
	}

	else {
		if (button == OF_MOUSE_BUTTON_RIGHT) {
			int index = (x + y * m_video.getWidth()) * m_video.getPixels().getBytesPerPixel();
			tracker1.setColour(m_video.getPixels()[index], m_video.getPixels()[index + 1], m_video.getPixels()[index + 2]);
		}
		else if (button == OF_MOUSE_BUTTON_MIDDLE) {
			int index = (x + y * m_video.getWidth()) * m_video.getPixels().getBytesPerPixel();
			tracker2.setColour(m_video.getPixels()[index], m_video.getPixels()[index + 1], m_video.getPixels()[index + 2]);
		}
	}

	

}