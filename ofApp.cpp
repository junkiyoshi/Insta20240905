#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(255);
	ofFill();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 175, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);
	ofSetColor(0);

	auto word = "NOISE";
	this->font.drawString(word, -5, 90 + 360);

	fbo.end();
	auto span = 10;
	fbo.readToPixels(this->pixels);
}

//--------------------------------------------------------------
void ofApp::update() {
		
}

//--------------------------------------------------------------
void ofApp::draw() {

	int len = 10;
	for (int x = 0; x <= ofGetWindowWidth(); x += len) {

		for (int y = 0; y <= ofGetWindowHeight(); y += len) {

			auto noise_value = ofNoise(x * 0.002, y * 0.002, ofGetFrameNum() * 0.015);

			ofColor color = pixels.getColor(x, y);
			if (color != ofColor(0, 0)) {

				auto color_value = noise_value < 0.4 ? 0 : noise_value > 0.85 ? 239 : ofMap(noise_value, 0.4, 0.85, 0, 239);

				ofFill();
				ofSetColor(color_value);

				ofDrawRectangle(x, y, len, len);

				ofNoFill();
				ofSetColor(color_value == 239 ? 39 : 128);

				ofDrawRectangle(x, y, len, len);
			}
			else {

				auto color_value = noise_value < 0.4 ? 239 : noise_value > 0.85 ? 0 : ofMap(noise_value, 0.4, 0.85, 239, 0);

				ofFill();
				ofSetColor(color_value);

				ofDrawRectangle(x, y, len, len);

				ofNoFill();
				ofSetColor(color_value == 239 ? 128 : 39);

				ofDrawRectangle(x, y, len, len);
			}
		}
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}