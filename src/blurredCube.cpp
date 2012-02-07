#include "blurredCube.h"

void blurredCube::setup() {
    ofSetFrameRate(60);
    ofBackground(255, 255, 255);
    
    vertices.push_back(ofVec3f( 1,  1,  1));
    vertices.push_back(ofVec3f( 1,  1, -1));
    vertices.push_back(ofVec3f( 1, -1,  1));
    vertices.push_back(ofVec3f( 1, -1, -1));
    vertices.push_back(ofVec3f(-1,  1,  1));
    vertices.push_back(ofVec3f(-1,  1, -1));
    vertices.push_back(ofVec3f(-1, -1,  1));
    vertices.push_back(ofVec3f(-1, -1, -1));
    
    // TODO Any better way to initialize the array?
    int ls[12][2] = {
        { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 },
        { 1, 5 }, { 2, 3 }, { 2, 6 }, { 3, 7 },
        { 4, 5 }, { 4, 6 }, { 5, 7 }, { 6, 7 }        
    };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            lines[i][j] = ls[i][j];
        }
    }
    
    // This piece of code is from apps/examples/audioInputExample
    // Initialize sound stream
    soundStream.listDevices();
    
    //if you want to set a different device id 
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter = 0;
    drawCounter = 0;
    smoothedVol = 0.0;
    scaledVol = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

void blurredCube::update() {
    rotationX += 0.5;
    rotationY += 0.5;
}

void blurredCube::draw() {
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofScale(200, 200, 200);
    ofRotateX(rotationX);
    ofRotateY(rotationY);
    
    float amp = ofMap(smoothedVol, 0, 0.17, 0, 0.5);
    for (int i = 0; i < 12; i++) {
        randomLine(vertices[lines[i][0]], vertices[lines[i][1]], amp);
    }
}

#pragma mark - Private methods

void blurredCube::randomLine(const ofVec3f &start, const ofVec3f &end, float amp) {
    for (int i = 0; i < 15; i++) {
        ofSetColor(100, 100, 100);
        ofLine(
            start.x + ofRandom(-amp, amp),
            start.y + ofRandom(-amp, amp),
            start.z + ofRandom(-amp, amp),
            end.x + ofRandom(-amp, amp),
            end.y + ofRandom(-amp, amp),
            end.z + ofRandom(-amp, amp)
        );
    }
}


#pragma mark - Event handlers

// from apps/examples/audioInputExample
void blurredCube::audioIn(float *input, int bufferSize, int nChannels) {
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume    
    for (int i = 0; i < bufferSize; i++) {
        left[i] = input[i * 2] * 0.5;
        right[i] = input[i * 2 + 1] * 0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted += 2;
    }
    
    //this is how we get the mean of rms :) 
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :) 
    curVol = sqrt(curVol);
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
}

void blurredCube::keyPressed(int key) {

}

void blurredCube::keyReleased(int key) {

}

void blurredCube::mouseMoved(int x, int y ) {
    
}

void blurredCube::mouseDragged(int x, int y, int button) {

}

void blurredCube::mousePressed(int x, int y, int button) {

}

void blurredCube::mouseReleased(int x, int y, int button) {

}

void blurredCube::windowResized(int w, int h) {

}

void blurredCube::gotMessage(ofMessage msg) {

}

void blurredCube::dragEvent(ofDragInfo dragInfo) { 

}
