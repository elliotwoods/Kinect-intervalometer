#include "testApp.h"

testApp::testApp() :
scrPreviewDepth("Depth", playback.depth),
scrPreviewRGB("RGB", playback.rgb),
scr3D("3D", playback),

wdgSelectPath("Select path")

{
	scrMain.push(scrPreviewDepth);
	scrMain.push(scrPreviewRGB);
	scrMain.push(scrControl);
	scrMain.push(scr3D);
	
	scr3D.enableGrid(3.0f);
	scrControl.push(new wdgCounter("images in sequence", count));
	scrControl.push(&wdgSelectPath);
}

//--------------------------------------------------------------
void testApp::setup(){	
	screens.init(scrMain);	
	ofBackground(117/2,130/2,160/2);
	count = 0;
	
	selectFiles();
}

//--------------------------------------------------------------
void testApp::update(){
	if (wdgSelectPath.getBang())
		selectFiles();
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
void testApp::selectFiles() {
	firstFile = ofSystemLoadDialog("Select first rgb file in sequence").getPath();
	lastFile = ofSystemLoadDialog("Select first depth file in sequence").getPath();
	
	cout << firstFile << endl << lastFile << endl;
}