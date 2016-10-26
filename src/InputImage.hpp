#ifndef __bauMapping__InputImage__
#define __bauMapping__InputImage__

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "CvContourImage.hpp"

class InputImage{
    
    public:
        InputImage();
        virtual ~InputImage();
    
        void setup();
        void setupSize(int w,int h);
        void update();
        //void updateParams(GUIPanel::inputImageGUI_p params);
        void draw(float x, float y, int w, int h);
        void draw(float x, float y);
        //void keyPressed(int key);
    
        void shootPicture(int threshold);
    
        void close();
    
        bool isClose();
    
        bool isMaskExist();
    
        ofVec2f getSize();
    
        CvContourImage      m_contourFinder;
    
    private:
    
    
        ofVideoGrabber          m_vidGrabber;

        ofxCvColorImage			m_colorImg;
        ofxCvGrayscaleImage 	m_grayImage;
        ofxCvGrayscaleImage 	m_grayBg;
        ofxCvGrayscaleImage 	m_grayDiff;
    
    
    
        ofImage                 m_backgroundImage;
    
        int                     m_width, m_height;
        bool                    m_bShotPicture;
        bool                    m_bClose;
        bool                    m_bMaskExists;
};
#endif