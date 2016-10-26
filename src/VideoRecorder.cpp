#include "VideoRecorder.hpp"

//--------------------------------------------------------------
VideoRecorder::VideoRecorder()
{
    setup();
}

//--------------------------------------------------------------
VideoRecorder::~VideoRecorder()
{
    m_vidRecorder.close();
}

//--------------------------------------------------------------
void VideoRecorder::setup(){
        
    m_fileName = "movie";
    m_fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    m_vidRecorder.setVideoCodec("mpeg4");
    m_vidRecorder.setVideoBitrate("200000k");
    m_bRecording = false;
    
    m_counter=0;
    m_recordPixels.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR_ALPHA); //OF_IMAGE_COLOR
    m_reader.setAsync(true);
}


//--------------------------------------------------------------
void VideoRecorder::update(ofFbo &fbo){
    if(m_bRecording){
        TIME_SAMPLE_START("PBO");
        
        m_reader.readToPixels(fbo, m_recordPixels);

        TIME_SAMPLE_STOP("PBO");

        m_vidRecorder.addFrame(m_recordPixels);
    }
}

//--------------------------------------------------------------
void VideoRecorder::setStartRecord(){
    if(!m_bRecording){
        m_bRecording = true;
        if(m_bRecording && !m_vidRecorder.isInitialized()) {
            m_vidRecorder.setup(m_fileName+ofToString(m_counter)+ofGetTimestampString()+m_fileExt, ofGetWidth(), ofGetHeight(), 30,0,0,false,true);
            m_vidRecorder.start();
            m_counter++;
        }
        else if(!m_bRecording && m_vidRecorder.isInitialized()) {
            m_vidRecorder.setPaused(true);
        }
        else if(m_bRecording && m_vidRecorder.isInitialized()) {
            m_vidRecorder.setPaused(false);
        }
    }
}


//--------------------------------------------------------------
void VideoRecorder::setStopRecord(){
    if(m_bRecording){
        m_bRecording = false;
        m_vidRecorder.close();
    }
}
