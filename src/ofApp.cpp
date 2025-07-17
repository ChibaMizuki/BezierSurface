#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// 制御点の個数
	control_n = 5; 
	control_m = 5;
	grid.resize(control_n, vector<ofVec3f>(control_m));
	// メッシュの幅
	interval = 0.05;
	image.load("gk.jpg");

	ofVec3f offset(((control_n - 1) * 100) / 2, ((control_m - 1) * 100) / 2, 150);
	//制御点の設定
	for (int i = 0; i < control_n; i++) {
		for (int j = 0; j < control_m; j++) {
			grid[i][j] = ofVec3f(i * 100, j * 100, ofRandom(0, 300)) - offset;
		}
	}

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	ofEnableNormalizedTexCoords();
	ofSetBackgroundColor(ofColor::black);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
float ofApp::Bernstein(int n, int i, float u) {
	return binomialcoefficient(n, i) * std::pow(u, i) * std::pow((1 - u), (n - i));
}

//--------------------------------------------------------------
int ofApp::binomialcoefficient(int n, int i) {
	// 問題が起きた時用
	if (n < 0 || i < 0 || n < i) return 0;
	// = 1 になるから除外
	if (i == 0 || n == i) return 1;

	int comb = 1;
	for (int k = 1; k <= i; k++) {
		comb *= (n - k + 1);
		comb /= k;
	}
	return comb;
}

//--------------------------------------------------------------
ofVec3f ofApp::Bezier(float u, float v) {
	ofVec3f point(0, 0, 0);

	for (int i = 0; i < control_n; i++) {
		for (int j = 0; j < control_m; j++) {
			point += grid[i][j] * Bernstein(control_n - 1, i, u)* Bernstein(control_m - 1, j, v);
		}
	}

	return point;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	ofDrawAxis(50);

	for (int i = 0; i < control_n; i++) {
		for (int j = 0; j < control_m; j++) {
			if ((i == 0 && j == 0) || (i == control_n - 1 && j == 0) || (i == 0 && j == control_m - 1)
				|| (i == control_n - 1 && j == control_m - 1)) {
				ofSetColor(ofColor::blue);
			}
			else {
				ofSetColor(ofColor::white);
			}
			ofDrawSphere(grid[i][j], 2);
		}
	}

	//ofSetColor(ofColor::green);
	int i = 0;
	for (float u = 0.0; u < 1.0; u += interval) {
		float u0 = u;
		float u1 = u + interval;
		for (float v = 0.0; v < 1.0; v += interval) {
			float v0 = v;
			float v1 = v + interval;

			ofVec3f p00 = Bezier(u0, v0);
			ofVec3f p10 = Bezier(u1, v0);
			ofVec3f p01 = Bezier(u0, v1);
			ofVec3f p11 = Bezier(u1, v1);

			/*ofDrawLine(p00, p10);
			ofDrawLine(p00, p01);
			ofDrawLine(p11, p10);
			ofDrawLine(p11, p01);*/

			/*
			p01・-・p11
			    | |
			p00・-・p10
			*/

			mesh.addVertex(ofVec3f(p00));
			mesh.addVertex(ofVec3f(p10));
			mesh.addVertex(ofVec3f(p01));
			mesh.addVertex(ofVec3f(p11));

			mesh.addIndex(i + 0); mesh.addIndex(i + 1); mesh.addIndex(i + 2);
			mesh.addIndex(i + 2); mesh.addIndex(i + 1); mesh.addIndex(i + 3);

			// 上下反転するのを修正
			mesh.addTexCoord(ofVec2f(u0, 1.0 - v0));
			mesh.addTexCoord(ofVec2f(u1, 1.0 - v0));
			mesh.addTexCoord(ofVec2f(u0, 1.0 - v1));
			mesh.addTexCoord(ofVec2f(u1, 1.0 - v1));
			i += 4;
		}
	}

	ofSetColor(255);
	image.getTexture().bind();
	mesh.draw();
	image.getTexture().unbind();
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
