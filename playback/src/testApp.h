#pragma once

#include "ofMain.h"

#include "ofxCVgui.h"

#include "playback.h"

class testApp : public ofBaseApp {

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
	//playback
	////
	//
	Playback playback;
	//
	wdgButton wdgSelectPath;
	void	selectFiles();
	string	stripExtension(string &path);
	void	crop(vector<string>& filenames, string firstFile, string lastFile="");
	vector<string>	findRgbDepthPairs(vector<string>& filenames);
	string	firstFile;
	string	lastFile;
	vector<string> filenames;
	unsigned int count;
	unsigned int position;
	//
	////
};
