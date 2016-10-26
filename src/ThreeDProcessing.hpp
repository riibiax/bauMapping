#ifndef __bauMapping__ThreeDProcessing__
#define __bauMapping__ThreeDProcessing__

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ThreeDProcessing{
    
    public:
        ThreeDProcessing();
        virtual ~ThreeDProcessing();
    
        void setup();
        void load(string fileName);
        void update();
        void draw();
    
    private:
    
        ofxAssimpModelLoader m_model;
    
};

#endif