#pragma once

#include "ofMain.h"

class blurredCube : public ofBaseApp {
  public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
  
  private:
    vector<ofVec3f> vertices;
    int lines[12][2];
    float rotationX, rotationY;
    
    void randomLine(const ofVec3f &start, const ofVec3f &end, float amp);    
    
    //  For audio
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;

    ofSoundStream soundStream;
};
