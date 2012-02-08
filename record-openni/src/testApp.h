#pragma once

#include "ofMain.h"

#include "ofxCVgui.h"
#include "ofxOpenNI.h"

#include "OpenNI2ViewNode.h"

#define XYZ_EXT "-depth.png"
#define RGB_EXT "-rgb.jpg"

class testApp : public ofBaseApp, public ofThread {

public:
	testApp();
	
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

protected:
	
	//////////////////
	// Device
	//////////////////
	//
	ofxOpenNI			kinect;
	bool				open;
	//
	//////////////////
	
	OpenNI2ViewNode		kinectView;
	
	
	//////////////////
	// GUI
	//////////////////
	//
	ofxCVgui		screens;
	scrGroupGrid	scrMain;
	
	scrDraw2D		scrPreviewDepth;
	scrDraw2D		scrPreviewRGB;	
	scrWidgets		scrControl;
	scrDraw3D		scr3D;
	//
	//////////////////
	
	////
	//recording
	////
	//
	void	threadedFunction();
	void	capture();
	float	interval;
	float	lastCapture;
	bool	recording;
	unsigned int count;
	ofImage rgb;
	ofShortImage depth;
	string	path;
	wdgButton wdgSelectPath;
	//
	////
};
