#include "testApp.h"

testApp::testApp() :
kinectView(kinect),

scrPreviewDepth("Depth", kinect.getDepthTextureReference()),
scrPreviewRGB("RGB", kinect.getTextureReference()),
scr3D("3D", kinectView),

wdgSelectPath("Select path")

{
	scrMain.push(scrPreviewDepth);
	scrMain.push(scrPreviewRGB);
	scrMain.push(scrControl);
	scrMain.push(scr3D);
	
	scr3D.enableGrid(3.0f);
	//scr3D.setCursorEnabled(true);
	scrControl.push(new wdgButton("recording", recording));
	scrControl.push(new wdgSlider("interval", interval, 0, 20, 0.1, "s"));
	scrControl.push(new wdgCounter("snaps taken", count));
	scrControl.push(&wdgSelectPath);
	
	wdgButton* open = new wdgButton("Connected", this->open);
	scrControl.push(open);
	open->enabled = false;
}

//--------------------------------------------------------------
void testApp::setup(){	
	screens.init(scrMain);	
	ofBackground(117/2,130/2,160/2);
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	kinect.init();
	kinect.open();
	kinect.setRegistration(true);

	lastCapture = 0;
	count = 0;
	interval = 5.0f;
	recording = true;
	path = "";
	
	depth.allocate(640, 480, OF_IMAGE_GRAYSCALE);
	rgb.allocate(640, 480, OF_IMAGE_COLOR);
	startThread(true, false);
}

//--------------------------------------------------------------
void testApp::update(){
	this->open = kinect.isConnected();
	if (wdgSelectPath.getBang())
		path = ofSystemSaveDialog("timelapse", "Timelapse save path").getPath();
	
	lock();
	kinect.update();
	unlock();
}

void testApp::threadedFunction() {
	while (isThreadRunning()) {
		if (recording && ofGetElapsedTimef() - lastCapture >= interval)
			capture();
		ofSleepMillis(10);
	}
}
//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::capture(){
	
	if (!kinect.isConnected() || !kinect.getPixelsRef().isAllocated())
		return;
	
	stringstream dateString;
	dateString << ofGetYear() << "-" << ofGetMonth() << "-" << ofGetDay() << "," << ofGetHours() << "." << ofGetMinutes() << "." << ofGetSeconds() << "-" << ofGetElapsedTimeMillis();
	
	lock();
	memcpy(rgb.getPixels(),	kinect.getPixels(), sizeof(unsigned char) * 640 * 480 * 3);
	memcpy(depth.getPixels(),	kinect.getRawDepthPixels(), sizeof(unsigned short) * 640 * 480);
	unlock();
	
	string savePath;
	if (path != "")
		savePath = path + "/" + dateString.str();
	else
		savePath = dateString.str();
	
	rgb.saveImage(savePath + string(RGB_EXT));
	depth.saveImage(savePath + string(XYZ_EXT));
	
	lastCapture = ofGetElapsedTimef();
	count++;
}