#include "ofApp.h"


//----


int MSB_0 = -1;
int LSB_0 = -1;
int WAIT_LSB_0 = 0;
int MSB_1 = -1;
int LSB_1 = -1;
int line = -1;
int WAIT_LSB_1 = 0;

//bool available_a = false;
//bool available_b = false;

vector<int> opts ={0,0,0,0};
vector<int> pos = {-1, -1, -1, -1};
vector<int> last_pos = {0, 0, 0, 0};
vector<bool> new11 = {false, false, false, false};
vector<bool> line_complete = {false, false, false, false};
vector<bool> reset_once = {false, false, false, false};

vector<vector<int>> a2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

int MAXLEN = 11;
vector<vector<string>> line_char_array = {
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "", "", "", ""},
};


vector<string> line_static_str_VISUAL = {"", "", "", ""};
vector<string> line_static_str = {"", "", "", ""};
vector<string> line_static_str_SHADOW = {"", "", "", ""};

bool bDeckAIsPlaying = false;
bool bDeckBIsPlaying = false;
bool bDeckAIsPlaying_tmp = false;
bool bDeckBIsPlaying_tmp = false;
bool countA = 0;
bool countB = 0;


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
    //ofLog() << message.toString() ;
    string str;

    int a = message.bytes[0];
    int b = message.bytes[1];
    int c = message.bytes[2];
    
    int deck = a & 0x01;
    int ch = 0;
    line = -1;
    int tmp_pos = -1;
    
    switch ( b ) {
        case 0x1: line = 0; tmp_pos = 0; MSB_0 = c; break;
        case 0x2: line = 0; tmp_pos = 1; MSB_0 = c; break;
        case 0x3: line = 0; tmp_pos = 2; MSB_0 = c; break;
        case 0x4: line = 0; tmp_pos = 3; MSB_0 = c; break;
        case 0x5: line = 0; tmp_pos = 4; MSB_0 = c; break;
        case 0x7: line = 0; tmp_pos = 5; MSB_0 = c; break;
        case 0x8: line = 0; tmp_pos = 6; MSB_0 = c; break;
        case 0x9: line = 0; tmp_pos = 7; MSB_0 = c; break;
        case 0xA: line = 0; tmp_pos = 8; MSB_0 = c; break;
        case 0xB: line = 0; tmp_pos = 9; MSB_0 = c; break;
        case 0xC: line = 0; tmp_pos = 10;MSB_0 = c; break;
        case 0xD: line = 0; tmp_pos = 11;MSB_0 = c; break;

        case 0x21: line = 0; tmp_pos = 0; LSB_0 = c; break;
        case 0x22: line = 0; tmp_pos = 1; LSB_0 = c; break;
        case 0x23: line = 0; tmp_pos = 2; LSB_0 = c; break;
        case 0x24: line = 0; tmp_pos = 3; LSB_0 = c; break;
        case 0x25: line = 0; tmp_pos = 4; LSB_0 = c; break;
        case 0x27: line = 0; tmp_pos = 5; LSB_0 = c; break;
        case 0x28: line = 0; tmp_pos = 6; LSB_0 = c; break;
        case 0x29: line = 0; tmp_pos = 7; LSB_0 = c; break;
        case 0x2A: line = 0; tmp_pos = 8; LSB_0 = c; break;
        case 0x2B: line = 0; tmp_pos = 9; LSB_0 = c; break;
        case 0x2C: line = 0; tmp_pos = 10;LSB_0 = c; break;
        case 0x2D: line = 0; tmp_pos = 11;LSB_0 = c; break;

        case 0xE: line = 1; tmp_pos = 0; MSB_1 = c; break;
        case 0xF: line = 1; tmp_pos = 1; MSB_1 = c; break;
        case 0x10: line = 1; tmp_pos = 2; MSB_1 = c; break;
        case 0x11: line = 1; tmp_pos = 3; MSB_1 = c; break;
        case 0x12: line = 1; tmp_pos = 4; MSB_1 = c; break;
        case 0x13: line = 1; tmp_pos = 5; MSB_1 = c; break;
        case 0x14: line = 1; tmp_pos = 6; MSB_1 = c; break;
        case 0x15: line = 1; tmp_pos = 7; MSB_1 = c; break;
        case 0x16: line = 1; tmp_pos = 8; MSB_1 = c; break;
        case 0x17: line = 1; tmp_pos = 9; MSB_1 = c; break;
        case 0x18: line = 1; tmp_pos = 10;MSB_1 = c; break;
        case 0x19: line = 1; tmp_pos = 11;MSB_1 = c; break;

        case 0x2E: line = 1; tmp_pos = 0; LSB_1 = c;break;
        case 0x2F: line = 1; tmp_pos = 1; LSB_1 = c;break;
        case 0x30: line = 1; tmp_pos = 2; LSB_1 = c;break;
        case 0x31: line = 1; tmp_pos = 3; LSB_1 = c;break;
        case 0x32: line = 1; tmp_pos = 4; LSB_1 = c;break;
        case 0x33: line = 1; tmp_pos = 5; LSB_1 = c;break;
        case 0x34: line = 1; tmp_pos = 6; LSB_1 = c;break;
        case 0x35: line = 1; tmp_pos = 7; LSB_1 = c;break;
        case 0x36: line = 1; tmp_pos = 8; LSB_1 = c;break;
        case 0x37: line = 1; tmp_pos = 9; LSB_1 = c;break;
        case 0x38: line = 1; tmp_pos = 10;LSB_1 = c;break;
        case 0x39: line = 1; tmp_pos = 11;LSB_1 = c; break;
        //default:
    }
    
    bool bCharComplete = false;
    
    // Check if LSB_0 received
    if ( MSB_0 != -1 && LSB_0 == -1 ) {
        if ( WAIT_LSB_0 == 1 ) {
            ofLogNotice ( "ERROR: LSB_0 missing!");
            MSB_0 = -1;
            WAIT_LSB_0 = 0;
        }
        else
            WAIT_LSB_0 = 1;
    }

    // Check if MSB_0 received
    if ( MSB_0 == -1 && LSB_0 != -1 ) {
        ofLogNotice ( "ERROR: MSB_0 missing!");
        LSB_0 = -1;
    }

    if ( MSB_0 != -1 && LSB_0 != -1 ) {
        ch = (MSB_0 << 4) | LSB_0;
        str = char( ch );
        MSB_0 = -1;
        LSB_0 = -1;
        WAIT_LSB_0 = 0;
        bCharComplete = true;
    }

    // Check if LSB_1 received
    if ( MSB_1 != -1 && LSB_1 == -1 ) {
        if ( WAIT_LSB_1 == 1 ) {
            ofLogNotice ( "ERROR: LSB_1 missing!");
            MSB_1 = -1;
            WAIT_LSB_1 = 0;
        }
        else
            WAIT_LSB_1 = 1;
    }

    // Check if MSB_1 received
    if ( MSB_1 == -1 && LSB_1 != -1 ) {
        ofLogNotice ( "ERROR: MSB_1 missing!");
        LSB_1 = -1;
    }

    if ( MSB_1 != -1 && LSB_1 != -1 ) {
        ch = (MSB_1 << 4) | LSB_1;
        str = char( ch );
        MSB_1 = -1;
        LSB_1 = -1;
        WAIT_LSB_1 = 0;
        bCharComplete = true;
    }

    if ( !bCharComplete )
        return;

    if ( deck == 0 ) { // Deck A
        if ( line == 0 ) {// Line 1
            pos[0] = tmp_pos;
            buildString(str, 0);
            FindStart(0);
        } else { // Line 2
            pos[1] = tmp_pos;
            buildString(str, 1);
            FindStart(1);
        }
    } else { // Deck B
        if ( line == 0 ) { // Line 1
            pos[2] = tmp_pos;
            buildString(str, 2);
            FindStart(2);
        } else { // Line 2
            pos[3] = tmp_pos;
            buildString(str, 3);
            FindStart(3);
        }
    }

}

void ofApp::buildString(string c, int pLine){

    line_char_array[pLine][pos[pLine]] = c;
    
    if ( pos[pLine] - last_pos[pLine] > 1 && line_char_array[pLine][last_pos[pLine]] != "_" ) {
        while ( last_pos[pLine] < pos[pLine] - 1 ) {
            line_char_array[pLine][last_pos[pLine] + 1] = line_char_array[pLine][last_pos[pLine]];
            last_pos[pLine]++;
        }
    }
    else if ( pos[pLine] < last_pos[pLine] && last_pos[pLine] < MAXLEN && line_char_array[pLine][last_pos[pLine]] != "_") {
        while ( last_pos[pLine] < MAXLEN ) {
            line_char_array[pLine][last_pos[pLine] + 1] = line_char_array[pLine][last_pos[pLine]];
            last_pos[pLine]++;

            if ( last_pos[pLine] == MAXLEN )
                new11[pLine] = true;
        }

        if ( pos[pLine] > 0 ) {
            last_pos[pLine] = 0;

            while ( last_pos[pLine] < pos[pLine] - 1 ) {
                line_char_array[pLine][last_pos[pLine] + 1] = line_char_array[pLine][last_pos[pLine]];
                last_pos[pLine]++;
            }
        }
    }

    if ( pos[pLine] == MAXLEN ){
        new11[pLine] = true;
    }

    last_pos[pLine] = pos[pLine];
}


void ofApp::FindStart ( int  line_idx ){
    if ( line_static_str_SHADOW[line_idx].find("   ") != /*-1*/ std::string::npos ) {
        // Remove trailing blanks
        while ( line_static_str_SHADOW[line_idx].substr ( line_static_str_SHADOW[line_idx].length()-1, 1 ) == " " ){
        line_static_str_SHADOW[line_idx] = line_static_str_SHADOW[line_idx].substr ( 0, line_static_str_SHADOW[line_idx].length()-1 );
        }
        
        // If there are multiple underscores due to german "Umlaute" reduce every multiple to one underscore
        line_static_str_SHADOW[line_idx] = RemoveMultipleUnderscores ( line_static_str_SHADOW[line_idx] );

        // String not final yet, due to marker confusion?
        if ( line_static_str[line_idx] != line_static_str_SHADOW[line_idx] ) {
            line_static_str[line_idx] = line_static_str_SHADOW[line_idx];
            line_complete[line_idx] = false;

        } else {
            line_complete[line_idx] = true;

            // If line 0 has been completed reset line 1 once to ensure that track and artist match. Otherwise a track could get the wrong artist!
            if ( line_idx == 0 ) {
                if ( reset_once[1] == false ) {
                    line_complete[1] = false;
                    reset_once[1] = true;
                }
                else
                    reset_once[1] = false;
            }

            // If line 1 has been completed reset line 0 once to ensure that track and artist match. Otherwise a track could get the wrong artist!
            if ( line_idx == 1 ) {
                if ( reset_once[0] == false ) {
                    line_complete[0] = false;
                    reset_once[0] = true;
                }
                else
                    reset_once[0] = false;
            }

            // If line 2 has been completed reset line 3 once to ensure that track and artist match. Otherwise a track could get the wrong artist!
            if ( line_idx == 2 ) {
                if ( reset_once[3] == false ) {
                    line_complete[3] = false;
                    reset_once[3] = true;
                }
                else
                    reset_once[3] = false;
            }

            // If line 3 has been completed reset line 2 once to ensure that track and artist match. Otherwise a track could get the wrong artist!
            if ( line_idx == 3 ) {
                if ( reset_once[2] == false ) {
                    line_complete[2] = false;
                    reset_once[2] = true;
                }
                else
                    reset_once[2] = false;
            }

            if ( line_complete[0] == true &&
                line_complete[1] == true &&
                ( line_static_str_VISUAL[0] != line_static_str[0] ||
                line_static_str_VISUAL[1] != line_static_str[1] )   ) {
                line_static_str_VISUAL[0] = line_static_str[0];
                line_static_str_VISUAL[1] = line_static_str[1];

                ofLogNotice("Deck A");
                ofLogNotice("Track: " + line_static_str[0]);
                ofLogNotice("Artist: " + line_static_str[1]);
                //available_a = true;
                line_complete[0] = false;
                line_complete[1] = false;
            }
            else if (     line_complete[2] == true &&
                line_complete[3] == true &&
                ( line_static_str_VISUAL[2] != line_static_str[2] ||
                line_static_str_VISUAL[3] != line_static_str[3] )  ) {
                line_static_str_VISUAL[2] = line_static_str[2];
                line_static_str_VISUAL[3] = line_static_str[3];

                ofLogNotice("Deck B");
                ofLogNotice("Track: " + line_static_str[2]);
                ofLogNotice("Artist: " + line_static_str[3]);
                //available_b = true;
                line_complete[2] = false;
                line_complete[3] = false;
            }
        }
        line_static_str_SHADOW[line_idx] = "";
        
    } else {
        if ( new11[line_idx] == true ) {
            line_static_str_SHADOW[line_idx] += line_char_array[line_idx][MAXLEN];
            new11[line_idx] = false;
        }
    }
}
string ofApp::RemoveMultipleUnderscores ( string str ){
    int k;
    string str1;
    string str2;
    for ( k = 0 ; k < str.length() - 1 ; k++ ) {
        while ( k < str.length() - 1 && str.substr ( k, 1 ) == "_" && str.substr ( k + 1, 1 ) == "_" ) {
            str1 = str.substr( 0, k + 1 );

            if ( k < str.length() - 2 )
                str2 = str.substr ( k + 2 );
            else
                str2 = "";

            str  = str1 + str2;
        }
    }

    return str;
}
