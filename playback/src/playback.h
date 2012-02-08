//
//  playback.h
//  playback
//
#pragma once
#include "ofMain.h"

#define XYZ_EXT "-depth.png"
#define RGB_EXT "-rgb.jpg"

class Playback : public ofNode {
public:
	Playback();
	void init();
	void loadFrame(string path); ///< path is trunk filename, i.e. without -rgb.jpg or -depth.png
	
	void customDraw();
	ofMesh mesh;
	ofShader shader;
	
	ofImage rgb;
	ofShortImage depth;
	
	float pointSize;
};