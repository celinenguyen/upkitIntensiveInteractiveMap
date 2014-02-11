#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxUI.h"

using namespace wng;



class testApp : public ofBaseApp{
    
    

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxUICanvas *gui;
        void exit();
        void guiEvent(ofxUIEventArgs &e);
    
        ofxCsv csv;
        ofxCsv csvRecorder;
    
        ofMesh mesh;
        ofMesh hotelTypeMesh;
        ofMesh adjacencyMesh;
    
        ofEasyCam easyCam;
    
    
    
        int appWidth = 1200;
        int appHeight = 800;
		
};
