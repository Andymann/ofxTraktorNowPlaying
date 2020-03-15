#include "ofApp.h"


//----
int MSB_0 = -1;
int LSB_0 = -1;
int WAIT_LSB_0 = 0;
int MSB_1 = -1;
int LSB_1 = -1;
int line = -1;
int WAIT_LSB_1 = 0;

int available_a = 0;
int available_b = 0;

vector<int> opts ={0,0,0,0};
vector<int> pos = {-1, -1, -1, -1};
vector<int> last_pos = {0, 0, 0, 0};
vector<int> new11 = {0, 0, 0, 0};
vector<int> line_complete = {0, 0, 0, 0};
vector<bool> reset_once = {false, false, false, false};

vector<vector<int>> a2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

vector<vector<string>> line_char_array = {
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
};

/*
vector<string> line_char_array = {
    vector<string>{"", "", "", "", "", "", "", "", "", "", "", ""},
    vector<string>{"", "", "", "", "", "", "", "", "", "", "", ""},
    vector<string>{"", "", "", "", "", "", "", "", "", "", "", ""},
    vector<string>{"", "", "", "", "", "", "", "", "", "", "", ""}
};
*/
vector<string> line_static_str_VISUAL = {"", "", "", ""};
vector<string> line_static_str = {"", "", "", ""};
vector<string> line_static_str_SHADOW = {"", "", "", ""};

bool bDeckAIsPlaying = false;
bool bDeckBIsPlaying = false;
bool bDeckAIsPlaying_tmp = false;
bool bDeckBIsPlaying_tmp = false;
bool countA = 0;
bool countB = 0;


//----


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxTraktorNowPlaying");
    ofSetBackgroundColor(60, 60, 60);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetEscapeQuitsApp(false);
    
    font.load(OF_TTF_MONO, 23);
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    
    // add a dropdown menu //
    vector<string> opts = {midiIn.getInPortList()/*"option - 1", "option - 2", "option - 3", "option - 4"*/};
    
    gui->addDropdown("Select MidiPort", opts);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->setTheme(new myCustomTheme() );
    gui->setWidth(1024);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e){
    cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
    setMidiPort( e.target->getLabel() );
}

void ofApp::setMidiPort(string pPortName){
    midiIn.closePort();
//    midiIn.removeListener(this);
    
    midiIn.openPort( pPortName ); // open a virtual port
    midiIn.ignoreTypes(false, // sysex  <-- don't ignore timecode messages!
                       false, // timing <-- don't ignore clock messages!
                       true); // sensing
    
    // add ofApp as a listener
    midiIn.addListener(this);
    cout << "setMidiPort: " << pPortName << " Selected" << endl;
}

void ofApp::newMidiMessage(ofxMidiMessage& message) {
    
    ofLog() << message.toString() ;
    
}
