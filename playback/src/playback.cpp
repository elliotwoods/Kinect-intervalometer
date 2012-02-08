//
//  playback.cpp
//  playback
//
#include "playback.h"

Playback::Playback() {
	pointSize = 1.0f;
}

void Playback::init() {
	vector<ofVec3f> vertices;
	vector<ofVec2f> texCoords;
	vector<ofFloatColor> colors;
	float x, y;
	int idx;
	for (int j=0; j<480; j++)
		for (int i=0; i<640; i++) {
			x = (float) i / 640;
			y = (float) j / 480;
			vertices.push_back(ofVec3f(x,y,0));
			texCoords.push_back(ofVec2f(x,y));
			colors.push_back(ofFloatColor(10,10,10));
		}
	mesh.addVertices(vertices);
	mesh.addTexCoords(texCoords);
	mesh.addColors(colors);
	
	shader.setUniformTexture("depth", depth, 0);
	shader.setUniformTexture("rgb", rgb, 1);	
}

void Playback::loadFrame(string path) {
	string rgbPath = path + string(RGB_EXT);
	string xyzPath = path + string(XYZ_EXT); 
	rgb.loadImage(rgbPath);
	depth.loadImage(xyzPath);
	
	const float fx_d = 1.0f / 5.9421434211923247e+02f;
	const float fy_d = 1.0f / 5.9104053696870778e+02f;
	const float cx_d = 3.3930780975300314e+02f;
	const float cy_d = 2.4273913761751615e+02f;
	ofVec3f* xyz = mesh.getVerticesPointer();
	unsigned short* depIn = depth.getPixels();
	for (int j=0; j<480; j++)
		for (int i=0; i<640; i++) {
			xyz->z = (float)(*depIn) / 1000.0f;
			xyz->x = ((float)i - cx_d) * fx_d * xyz->z;
			xyz->y = -((float)j - cy_d) * fy_d * xyz->z;
			xyz++;
			depIn++;
		}
	
	ofFloatColor *out = mesh.getColorsPointer();
	unsigned char *in = rgb.getPixels();
	for (int i=0; i<640*480; i++, out++, in+=3)
		*out = ofFloatColor((float)in[0] / 255.0f,
							(float)in[1] / 255.0f,
							(float)in[2] / 255.0f,
							1.0f);
}

void Playback::customDraw() {
	glPointSize(pointSize);
	mesh.drawVertices();
}