#pragma once

#include "ofMain.h"
#include "GUIParams.h"
#include "ImageProcessing.hpp"
#include "InputImage.hpp"
#include "ThreeDProcessing.hpp"
#include "ofxUI.h"

//--------------------------------------------------------------
class GUIPanel: public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    void dragEvent(ofDragInfo dragInfo);
    
    void deleteGUIs();
    
    void setupGUIs();
    void setupGUIParticles();
    void setupGUIBoids();
    void setupGUITabPhysics();
    void setupGUI();
    void setupGUI3D();
    void setupGUI2D();
    void setupGUIOriginal();
    void setupGUIAdaptiveThreshold();
    void setupGUIBasicThreshold();
    void setupGUICanny();
    void setupGUILaplace();
    void setupGUISobel();
    void setupGUICornerHarris();
    void setupGUIAlgorithms();
    void setupGUIZ();
    void setupGUIMorph();
    void setupGUITriangulation();
    void setupGUILinesConnection();
    void setupGUIEasyCam();
    void setupGUIShader();
    void setupGUILight();
    void setupGUIInputImage();
    void setupGUIRecordVideo();
    
    void updateImage();
    void updateImageFileName();
    void updateScaleFactor();
    void updateSaveImages();
    void updateImageProcessing();
    
    void createInputImage();
    void checkActivationTime();
    void updateInputImage();
    
    void update3DProcessing();
    void updateModelFileName();
    
    void updateAlgorithms();
    
    void singleGUIPressed(ofxUISuperCanvas *singleGUI, ofxUISuperCanvas *minifiedGUI);
    void updateGUIPosition(ofxUISuperCanvas *singleGUI, float x, float y);
    void toggleGUIPosition(ofxUISuperCanvas *parentGUI, ofxUISuperCanvas *childGUI, float offset);
    void setImageProcessingAsInput();
    
    void drawImage();
    void drawImageProcessing();
    void drawInputImage();
    
    void resetBool();
    void resetVars();
    void resetGUIs();
    void resetImageGUIs();
    void resetAlgorithmsGUIs();
    
    void guiEvent(ofxUIEventArgs &e);
    
    
    
public:
    
    //Class to process input images (openCV and basic mesh)
    ImageProcessing*        m_image;
    
    ThreeDProcessing*       m_model;
    
    //Input image
    InputImage*             m_inputImage=NULL;
    
    bool textureChecked;
    bool imageGUIChecked;
    bool modelGUIChecked;
    bool imageFileNameChecked;
    bool modelFileNameChecked;
    bool saveImage;
    bool saveImage32B;
    
    bool morphChecked;
    bool triangulationChecked;
    bool easyCamChecked;
    bool lightChecked;
    bool boidsChecked;
    
    int updateValue;
    int primitiveMesh;
    
    float m_elapsedTimeActivationCamera;
    
    ofDirectory     dir;
    
    //particles GUI
    ofxUISuperCanvas    *particlesGUI;
    ofxUIToggleMatrix   *tm;
    struct GUIParams::particlesGUI_p    particlesGUI_params;
    
    //starting GUI
    ofxUISuperCanvas    *GUI;
    struct GUIParams::GUI_p             GUI_params;
    
    //GUI 2D
    ofxUISuperCanvas    *GUI2D;
    struct GUIParams::GUI2D_p           GUI2D_params;
    
    //GUI 3D
    ofxUISuperCanvas    *GUI3D;
    struct GUIParams::GUI3D_p           GUI3D_params;
    
    //Original image GUI
    ofxUISuperCanvas *originalGUI;
    struct GUIParams::originalGUI_p     originalGUI_params;
    
    //Basic threshold GUI
    ofxUISuperCanvas *basicGUI;
    struct GUIParams::basicGUI_p        basicGUI_params;
    
    
    //Adaptive Threshold GUI
    ofxUISuperCanvas *adaptiveGUI;
    struct GUIParams::adaptiveGUI_p     adaptiveGUI_params;
    
    
    //Canny GUI
    ofxUISuperCanvas *cannyGUI;
    struct GUIParams::cannyGUI_p        cannyGUI_params;
    
    
    //Laplace GUI
    ofxUISuperCanvas *laplaceGUI;
    struct GUIParams::laplaceGUI_p      laplaceGUI_params;
    
    
    //Sobel GUI
    ofxUISuperCanvas *sobelGUI;
    struct GUIParams::sobelGUI_p        sobelGUI_params;
    
    
    //Corner Harris GUI
    ofxUISuperCanvas *cornerHarrisGUI;
    struct GUIParams::cornerHarrisGUI_p cornerHarrisGUI_params;
    
    
    //Algorithms GUI
    ofxUISuperCanvas *algorithmsGUI;
    struct GUIParams::algorithmsGUI_p   algorithmsGUI_params;
    
    //Morph GUI
    ofxUISuperCanvas *morphGUI;
    struct GUIParams::morphGUI_p        morphGUI_params;
    
    //Triangulation GUI
    ofxUISuperCanvas *triangulationGUI;
    struct GUIParams::triangulationGUI_p triangulationGUI_params;
    
    //Lines Connection GUI
    ofxUISuperCanvas *linesConnectionGUI;
    struct GUIParams::linesConnectionGUI_p linesConnectionGUI_params;
    
    //Z GUI
    ofxUISuperCanvas *ZGUI;
    struct GUIParams::ZGUI_p            ZGUI_params;
    
    //EasyCam GUI
    ofxUISuperCanvas *easycamGUI;
    struct GUIParams::easycamGUI_p      easycamGUI_params;
    
    //Shader GUI
    ofxUISuperCanvas *shaderGUI;
    struct GUIParams::shaderGUI_p      shaderGUI_params;
    
    //Light GUI
    ofxUISuperCanvas *lightGUI;
    struct GUIParams::lightGUI_p        lightGUI_params;
    
    ofxUITabBar *physicsGUITabBar;
    
    //Boids GUI
    ofxUISuperCanvas *boidsGUI;
    struct GUIParams::boidsGUI_p        boidsGUI_params;
    
    //OpenSteer GUI
    ofxUISuperCanvas *openSteerGUI;
    struct GUIParams::openSteerGUI_p   openSteerGUI_params;
    
    //InputImage GUI
    ofxUISuperCanvas *inputImageGUI;
    struct GUIParams::inputImageGUI_p   inputImageGUI_params;
    
    //RecordVideo GUI
    ofxUISuperCanvas *recordVideoGUI;
    struct GUIParams::recordVideoGUI_p   recordVideoGUI_params;
    
};
