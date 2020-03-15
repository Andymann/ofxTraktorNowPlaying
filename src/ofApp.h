#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font;
    ofxMidiIn midiIn;
    ofxDatGui* gui;
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    void setMidiPort(string pPortName);
    
};

class myCustomTheme : public ofxDatGuiTheme{
public:
    myCustomTheme(){
        font.size = 13;
        //font.file = "path/to/font.ttf";
        init();
    }
};
