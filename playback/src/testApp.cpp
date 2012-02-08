#include "testApp.h"

testApp::testApp() :
scrPreviewDepth("Depth", playback.depth),
scrPreviewRGB("RGB", playback.rgb),
scr3D("3D", playback),

wdgSelectPath("Select path"),
wdgRewind("Rewind")
{
	scrMain.push(scrPreviewDepth);
	scrMain.push(scrPreviewRGB);
	scrMain.push(scrControl);
	scrMain.push(scr3D);
	
	scr3D.enableGrid(1.0f);
	scrControl.push(new wdgCounter("images in sequence", count));
	scrControl.push(new wdgSlider("position in sequence", position, 0, count));
	scrControl.push(new wdgButton("Play", playing));
	scrControl.push(&wdgRewind);
	scrControl.push(new wdgButton("Loop", loop));
	scrControl.push(&wdgSelectPath);
	scrControl.push(new wdgSlider("Point size", playback.pointSize, 1.0f, 10.0f));
}

//--------------------------------------------------------------
void testApp::setup(){	
	screens.init(scrMain);	
	playback.init();
	ofBackground(117/4,130/4,160/4);
	count = 0;
	position = 0;
}
	
//--------------------------------------------------------------
void testApp::update(){
	if (playing) {
		moveFrame(1);
	}
	if (wdgRewind.getBang())
		moveFrame(-(int)position);
	
	if (wdgSelectPath.getBang())
		selectFiles();
}
//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key==OF_KEY_LEFT && position > 0)
		moveFrame(-1);
	if (key==OF_KEY_RIGHT && position < count-1 && count != 0)
		moveFrame(1);
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
void testApp::moveFrame(int distance) {
	int newPosition = distance + (int)position;
	if (newPosition < 0)
		newPosition = 0;
	if (newPosition >= filenames.size()) {
		if (loop)
			newPosition = 0;
		else {
			playing = false;
			newPosition = filenames.size() - 1;
		}
	}
	position = newPosition;
	
	if (position < filenames.size())
		playback.loadFrame(filenames[position]);
}
//--------------------------------------------------------------
void testApp::selectFiles() {
	string file1In = ofSystemLoadDialog("Select first rgb file in sequence").getPath();
	string file2In = ofSystemLoadDialog("Select first depth file in sequence").getPath();
	
	cout << firstFile << endl << lastFile << endl;
	
	if (!ofFile::doesFileExist(file1In)) {
		ofLogError() << "File selection failed";
		return;
	}
	
	firstFile = file1In;
	firstFile = stripExtension(firstFile);
	
	if (ofFile::doesFileExist(file2In)) {
		lastFile = file2In;
		lastFile = stripExtension(lastFile);
	} else
		lastFile = "";
	
	ofDirectory dir;
	dir.listDir(ofFilePath::getEnclosingDirectory(file1In));
	dir.sort();
	vector<string> files;
	for (unsigned int i=0; i<dir.size(); i++) {
		files.push_back(dir.getPath(i));
	}
	
	filenames = findRgbDepthPairs(files);
	
	cout << "Found " << filenames.size() << " pairs before crop to selection" << endl;
	crop(filenames, firstFile, lastFile);
	cout << "Found " << filenames.size() << " pairs after crop to selection" << endl;
	count = filenames.size();
	
	if (count > 0) {
		playback.loadFrame(filenames[0]);
		position = 0;
	}
}


//--------------------------------------------------------------
string testApp::stripExtension(string &path) {
	string extension = ofFilePath::getFileExt(path);
	if (extension=="png") {
		// depth
		return path.substr(0, path.length() - string(XYZ_EXT).length());
	} else if (extension=="jpg") {
		// rgb
		return path.substr(0, path.length() - string(RGB_EXT).length());
	}
	else
		return "";
}

//--------------------------------------------------------------
vector<string> testApp::findRgbDepthPairs(vector<string>& filenames) {
	//takes in list of files, and returns trunks names where pair exists
	//(trunk = without -xyz.hdr, etc).
	
	vector<string> results;
	vector<string>::iterator it;
	string rgbFile, depthFile;
	string trunk;
	for (it = filenames.begin(); it != filenames.end(); it++) {
		trunk = stripExtension(*it);
		if (trunk == "")
			continue;
		
		//check if already have this
		if (find(results.begin(), results.end(), trunk) != results.end())
			continue;
		
		rgbFile = trunk + XYZ_EXT;
		depthFile = trunk + RGB_EXT;
		if (ofFile::doesFileExist(rgbFile) &&
			ofFile::doesFileExist(depthFile))
			results.push_back(trunk);
	}
	
	return results;
}

//--------------------------------------------------------------
void testApp::crop(vector<string>& filenames, string firstFile, string lastFile) {
	vector<string>::iterator first, last = filenames.end();
	
	first = find(filenames.begin(), filenames.end(), firstFile);
	if (lastFile != "")
		last = find(first, filenames.end(), lastFile);
	if (last != filenames.end())
		last++;

	filenames = vector<string>(first, last);
}
