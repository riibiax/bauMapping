#include "Scene.hpp"
//--------------------------------------------------------------
Scene::Scene()
{
    
}

//--------------------------------------------------------------
Scene::~Scene()
{
    
}


//--------------------------------------------------------------
void Scene::setup(){
    
   // video.initGrabber(320, 240);
   // finder.setup("haarcascade_frontalface_default.xml");
    usePreview = false;
    
    previewCamera.setDistance(3.0f);
    previewCamera.setNearClip(0.01f);
    previewCamera.setFarClip(500.0f);
    previewCamera.setPosition(0.4f, 0.2f, 0.8f);
    previewCamera.lookAt(ofVec3f(0.0f, 0.0f, 0.0f));
    
    //headTrackedCamera.setNearClip(0.01f);
    //headTrackedCamera.setFarClip(1000.0f);
    
    //defining the real world coordinates of the window which is being headtracked is important for visual accuracy
    windowWidth = 0.3f;
    windowHeight = 0.2f;
    
    windowTopLeft = ofVec3f(-windowWidth / 2.0f,
                            +windowHeight / 2.0f,
                            0.0f);
    windowBottomLeft = ofVec3f(-windowWidth / 2.0f,
                               - windowHeight / 2.0f,
                               0.0f);
    windowBottomRight = ofVec3f(+windowWidth / 2.0f,
                                -windowHeight / 2.0f,
                                0.0f);
    
    //we use this constant since we're using a really hacky headtracking in this example
    //if you use something that can properly locate the head in 3d (like a kinect), you don't need this fudge factor
    viewerDistance = 0.4f;
}

//--------------------------------------------------------------
void Scene::update(){

}

//--------------------------------------------------------------
void Scene::draw(){
    
}