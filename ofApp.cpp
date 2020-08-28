#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int i = 0; i < 6; i++) {

		this->noise_seed_list.push_back(ofRandom(1000));
		this->noise_param_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int radius = 300;
	int span = 28;

	for (int i = 0; i < this->noise_seed_list.size(); i++) {

		for (int deg = 0; deg < 360; deg += 3) {

			auto noise_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_param = ofMap(ofNoise(this->noise_seed_list[i], noise_location.x * 0.005, noise_location.y * 0.005, this->noise_param_list[i]), 0, 1, 0.5, 1);

			this->mesh.addVertex(glm::vec3(radius * noise_param * cos(deg * DEG_TO_RAD), radius * noise_param * sin(deg * DEG_TO_RAD), 0));
		}

		this->noise_param_list[i] += 0.005;
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		this->mesh.addColor(ofColor(39, 0));
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < span) {

				auto alpha = distance < span * 0.25 ? 255 : ofMap(distance, span * 0.25, span, 255, 0);

				if (this->mesh.getColor(i).a < alpha) {

					this->mesh.setColor(i, ofColor(this->mesh.getColor(i), alpha));
				}

				if (this->mesh.getColor(k).a < alpha) {

					this->mesh.setColor(k, ofColor(this->mesh.getColor(k), alpha));
				}

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);
			}
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->mesh.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}