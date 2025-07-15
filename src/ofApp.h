#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	private:
		//����_�i4 x 4�j
		ofVec3f grid[4][4];
		//u, v�̊Ԋu
		float interval;
		int control_n, control_m;

		ofMesh mesh;

		ofEasyCam camera;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Bernstein������
		float Bernstein(int, int, float);
		int binomialcoefficient(int, int);
		ofVec3f Bezier(ofVec3f p[4][4], float, float);
		
};
