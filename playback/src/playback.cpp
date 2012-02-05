//
//  playback.cpp
//  playback
//
#include "playback.h"

void Playback::init() {
	vector<ofVec3f> vertices;
	vector<ofVec2f> texCoords;
	float x, y;
	int idx;
	for (int j=0; j<480; j++)
		for (int i=0; i<640; i++) {
			x = (float) i / 640;
			y = (float) j / 480;
			vertices.push_back(ofVec3f(x,y,0));
			texCoords.push_back(ofVec2f(x,y));
		}
	mesh.addVertices(vertices);
	mesh.addTexCoords(texCoords);
	
	shader.setUniformTexture("depth", depth, 0);
	shader.setUniformTexture("rgb", rgb, 1);
	
}

void Playback::loadFrame(string path) {
	rgb.loadImage(path + string("-rgb.jpg"));
	depth.loadImage(path + string("-depth.png"));
}

void Playback::customDraw() {
	mesh.draw();
}