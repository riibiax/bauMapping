#ifndef __bauMapping__VideoRecorder__
#define __bauMapping__VideoRecorder__

#include "ofMain.h"
#include "ofxVideoRecorder.h"
#include "ofxFastFboReader.h"
#include "ofxTimeMeasurements.h"

class VideoRecorder{
    
    public:
    
        VideoRecorder();
        virtual ~VideoRecorder();
    
        void setup();
        void update(ofFbo &fbo);
    
        void setStartRecord();
    
        void setStopRecord();
    
    private:
    
        ofxVideoRecorder    m_vidRecorder;
    
        bool m_bRecording;

        string m_fileName;
        string m_fileExt;
    
        unsigned int m_counter;
    
        ofxFastFboReader m_reader;
    
        ofPixels m_recordPixels;
};

#endif