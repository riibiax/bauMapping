#ifndef __bauMapping__CvContourImage__
#define __bauMapping__CvContourImage__


#include "ofxCvContourFinder.h"

class CvContourImage: public ofxCvContourFinder{
    
    public:
        CvContourImage();
        virtual ~CvContourImage();
    
        virtual void setVertices();
    
        virtual void draw( float x, float y, float w, float h ) const;

    
    protected:

    
        vector<ofPath> m_paths;
    

    
};
#endif