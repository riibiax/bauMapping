#ifndef __bauMapping__Scene__
#define __bauMapping__Scene__

#include "ofMain.h"

class Scene{
    
    public:
        Scene();
        virtual ~Scene();
    
        void setup();
        void update();
        void draw();
    
    private:
    
        //the view window is defined by 3 corners
        ofVec3f windowTopLeft;
        ofVec3f windowBottomLeft;
        ofVec3f windowBottomRight;
        ofCamera headTrackedCamera;
        ofEasyCam previewCamera;
    
        bool usePreview;
        float windowWidth;
        float windowHeight;
        float viewerDistance;
    
        deque<ofPoint> headPositionHistory;
    
        ofVboMesh window;
    
};

#endif
    
 