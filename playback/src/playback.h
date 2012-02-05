//
//  playback.h
//  playback
//
#pragma once
#include "ofMain.h"

class Playback : public ofNode {
public:
	void init();
	void loadFrame(string path); ///< path is trunk filename, i.e. without -rgb.jpg or -depth.png
	
	void customDraw();
	ofMesh mesh;
	ofShader shader;
	
	ofImage rgb;
	ofShortImage depth;
};