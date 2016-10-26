#include "InputImage.hpp"

//--------------------------------------------------------------
InputImage::InputImage()
{
    
}

//--------------------------------------------------------------
InputImage::~InputImage()
{
    
}

//--------------------------------------------------------------
void InputImage::setupSize(int w, int h){
    m_width=w;
    m_height=h;
}

//--------------------------------------------------------------
void InputImage::setup(){
    
    //vidGrabber.setDeviceID(0);
   // m_vidGrabber.setVerbose(true);
    m_vidGrabber.setup(m_width,m_height);

    m_colorImg.allocate(m_width,m_height);
    m_grayImage.allocate(m_width,m_height);
    m_grayBg.allocate(m_width,m_height);
    m_grayDiff.allocate(m_width,m_height);
    
    m_backgroundImage.allocate(m_width, m_height, OF_IMAGE_COLOR);
    m_backgroundImage.setColor(ofColor(155,155,155));
    m_backgroundImage.update();
    m_grayBg.setFromPixels(m_backgroundImage.getPixels());
    
    m_bClose=false;
    m_bShotPicture=false;
    m_bMaskExists=false;
}

//--------------------------------------------------------------
void InputImage::update(){
    if(m_vidGrabber.isInitialized()){
        m_vidGrabber.update();
    }
    else{
        m_vidGrabber.initGrabber(m_width,m_height);
    }
}


//--------------------------------------------------------------
void InputImage::shootPicture(int threshold){

    if(m_vidGrabber.isInitialized()){
        m_bClose=false;
        m_colorImg.setFromPixels(m_vidGrabber.getPixels());
        m_grayImage = m_colorImg;
            
        // take the abs value of the difference between background and incoming and then threshold:
        m_grayDiff.absDiff(m_grayBg, m_grayImage);
        m_grayDiff.threshold(threshold);

        m_contourFinder.findContours(m_grayDiff, (m_width*m_height)*0.01, (m_width*m_height)*0.8, 10, false, true);
        if(m_contourFinder.nBlobs>0){
            m_bMaskExists=true;
            m_contourFinder.setVertices();
        }
        else{
            m_bMaskExists=false;
        }
        m_bShotPicture=true;
    }
}

//--------------------------------------------------------------
void InputImage::close(){
    if(!m_bClose){
        m_vidGrabber.close();
        m_bClose=true;
    }
}

//--------------------------------------------------------------
bool InputImage::isClose(){
    return m_bClose;
}

//--------------------------------------------------------------
bool InputImage::isMaskExist(){
    return m_bMaskExists;
}

//--------------------------------------------------------------
void InputImage::draw(float x, float y, int w, int h){
    //back layer
    m_vidGrabber.draw(x,y,w,h);
    if(m_bShotPicture){
        if(m_bMaskExists){
            //front layer
            m_contourFinder.draw(x,y,w,h);
        }
    }
}

//--------------------------------------------------------------
void InputImage::draw(float x, float y){
    m_vidGrabber.draw(x,y,m_width,m_height);
    if(m_bShotPicture){
        if(m_bMaskExists){
            m_contourFinder.draw(x,y,m_width,m_height);
        }
    }
}

//--------------------------------------------------------------
ofVec2f InputImage::getSize(){
    return ofVec2f(m_width,m_height);
}


