#include "GUIPanel.hpp"

//--------------------------------------------------------------
void GUIPanel::setup(){
    resetBool();
    resetVars();
    setupGUIs();
}

//--------------------------------------------------------------
void GUIPanel::exit(){
    
    /*  if(m_model){
     delete m_model;
     }
     if(m_image){
     
     delete m_image;
     }*/
    if(m_inputImage){
        m_inputImage->close();
        // delete m_inputImage;
    }
}

//--------------------------------------------------------------
void GUIPanel::deleteGUIs(){
    if(GUI)
        delete GUI;
    if(particlesGUI)
        delete particlesGUI;
    if(boidsGUI)
        delete boidsGUI;
    if(physicsGUITabBar)
        delete physicsGUITabBar;
    if(GUI3D)
        delete GUI3D;
    if(GUI2D)
        delete GUI2D;
    if(originalGUI)
        delete originalGUI;
    if(basicGUI)
        delete basicGUI;
    if(adaptiveGUI)
        delete adaptiveGUI;
    if(cannyGUI)
        delete cannyGUI;
    if(laplaceGUI)
        delete laplaceGUI;
    if(sobelGUI)
        delete sobelGUI;
    if(cornerHarrisGUI)
        delete cornerHarrisGUI;
    if(algorithmsGUI)
        delete algorithmsGUI;
    if(ZGUI)
        delete ZGUI;
    if(morphGUI)
        delete morphGUI;
    if(triangulationGUI)
        delete triangulationGUI;
    if(linesConnectionGUI)
        delete linesConnectionGUI;
    if(easycamGUI)
        delete easycamGUI;
    if(shaderGUI)
        delete shaderGUI;
    if(lightGUI)
        delete lightGUI;
    if(inputImageGUI)
        delete inputImageGUI;
    if(recordVideoGUI)
        delete recordVideoGUI;
}


//--------------------------------------------------------------
void GUIPanel::setupGUIs(){
    setupGUI();
    setupGUIParticles();
    setupGUIBoids();
    setupGUITabPhysics();
    setupGUIInputImage();
    setupGUI2D();
    setupGUI3D();
    setupGUIOriginal();
    setupGUIBasicThreshold();
    setupGUIAdaptiveThreshold();
    setupGUICanny();
    setupGUILaplace();
    setupGUISobel();
    setupGUICornerHarris();
    setupGUIAlgorithms();
    setupGUIZ();
    setupGUIMorph();
    setupGUITriangulation();
    setupGUIEasyCam();
    setupGUIShader();
    setupGUILight();
    setupGUILinesConnection();
    setupGUIRecordVideo();
    resetGUIs();
}

//--------------------------------------------------------------
void GUIPanel::setupGUIParticles(){
    //INITIALIZE VALUES
    particlesGUI_params.Total= 500;
    //if size==1, get flickering effect
    particlesGUI_params.Size=2;
    particlesGUI_params.Red=255;
    particlesGUI_params.Green=255;
    particlesGUI_params.Blue=255;
    particlesGUI_params.Alpha=255;
    particlesGUI_params.FreqFlickering=0.0f;
    //51 is the value to switch off the fbo trails==>ofclear(0,0,0,255);
    particlesGUI_params.AlphaFboTrails=51;
    particlesGUI_params.Texture=true;
    particlesGUI_params.MatrixTexture=1;
    //ADDING ELEMENTS
    particlesGUI = new ofxUISuperCanvas("Particles", OFX_UI_FONT_SMALL);
    particlesGUI->addSpacer();
    particlesGUI->addIntSlider("Total Number", 1000, 1000000, &particlesGUI_params.Total);
    particlesGUI->addSpacer();
    particlesGUI->addIntSlider("Size", 1, 100, &particlesGUI_params.Size);
    particlesGUI->addIntSlider("Alpha Fbo Trails", 0, 51, &particlesGUI_params.AlphaFboTrails);
    particlesGUI->addSpacer();
    particlesGUI->addIntSlider("Red", 0, 255, &particlesGUI_params.Red);
    particlesGUI->addIntSlider("Green", 0, 255, &particlesGUI_params.Green);
    particlesGUI->addIntSlider("Blue", 0, 255, &particlesGUI_params.Blue);
    particlesGUI->addIntSlider("Alpha", 0, 255, &particlesGUI_params.Alpha);
    particlesGUI->addSlider("Frequence Flickering", 0.0f, 255.0f, &particlesGUI_params.FreqFlickering);
    particlesGUI->addSpacer();
    particlesGUI->addLabelToggle("Load Texture", particlesGUI_params.Texture);
    tm =particlesGUI->addToggleMatrix("MATRIX", 1, 11);
    tm->setAllowMultiple(false);
    particlesGUI->addSpacer();
    vector<string> vnames; vnames.push_back("Boids");
    ofxUIRadio *radio = GUI->addRadio("PG", vnames, OFX_UI_ORIENTATION_VERTICAL);
    //SETTINGS
    particlesGUI->setName("Particles");
    particlesGUI->setPosition(ofGetWidth()-particlesGUI->getRect()->getWidth(), 0);
    particlesGUI->setVisible(true);
    particlesGUI->autoSizeToFitWidgets();
    particlesGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(particlesGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIBoids(){
    //INITIALIZE VALUES
    boidsGUI_params.LifeTime=10000.0f;
    boidsGUI_params.Speed=10.0f;
    boidsGUI_params.Align=12.0f;
    boidsGUI_params.DistSeparation=50.0f;
    boidsGUI_params.GravityForce=10000.0f;
    boidsGUI_params.BoundMode=2;
    //ADDING ELEMENTS
    boidsGUI = new ofxUISuperCanvas("Boids", OFX_UI_FONT_SMALL);
    boidsGUI->addSpacer();
    boidsGUI->addSlider("LifeTime", 0, 30000.0f, &boidsGUI_params.LifeTime);
    boidsGUI->addSlider("Speed", 1.0f, 100.0f, &boidsGUI_params.Speed);
    boidsGUI->addSlider("Align", 1.0f, 100.0f, &boidsGUI_params.Align);
    boidsGUI->addSlider("Distance Separation", 1.0f, 1000.0f, &boidsGUI_params.DistSeparation);
    boidsGUI->addSlider("Gravity Force", 0.0f, 10000.0f, &boidsGUI_params.GravityForce);
    boidsGUI->addIntSlider("Bound Mode", 0, 2, &boidsGUI_params.BoundMode);
    //SETTINGS
    boidsGUI->setName("Boids");
    boidsGUI->setVisible(true);
    boidsGUI->autoSizeToFitWidgets();
    boidsGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(boidsGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUITabPhysics(){
    physicsGUITabBar = new ofxUITabBar();
    physicsGUITabBar->setName("Particles Physics");
    physicsGUITabBar->addCanvas(boidsGUI);
    physicsGUITabBar->setColorBack(ofColor(25,25,25,200));
    physicsGUITabBar->setVisible(true);
    physicsGUITabBar->setPosition(ofGetWidth()-particlesGUI->getRect()->getWidth(),particlesGUI->getRect()->getHeight()+1);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIInputImage(){
    //INITIALIZE VALUES
    inputImageGUI_params.ActivateCamera=false;
    inputImageGUI_params.Threshold=80;
    inputImageGUI_params.Shoot=false;
    vector<string> names;
    names.push_back("OFF");
    names.push_back("Inside");
    names.push_back("Outside");
    inputImageGUI_params.Mask=GUIParams::MASKOFF;
    //ADDING ELEMENTS
    inputImageGUI = new ofxUISuperCanvas("Input Image", OFX_UI_FONT_SMALL);
    inputImageGUI->addToggle("Activate Camera", inputImageGUI_params.ActivateCamera);
    inputImageGUI->addIntSlider("Threshold", 0, 255, &inputImageGUI_params.Threshold);
    inputImageGUI->addLabelButton("Shoot", &inputImageGUI_params.Shoot);
    inputImageGUI->addLabel("MASK", OFX_UI_FONT_SMALL);
    inputImageGUI->addRadio("MASK", names, OFX_UI_ORIENTATION_HORIZONTAL);
    //SETTINGS
    inputImageGUI->setName("Input Image");
    inputImageGUI->setVisible(true);
    inputImageGUI->setPosition(ofGetWidth()-particlesGUI->getRect()->getWidth() -inputImageGUI->getRect()->getWidth() -1, 0);
    inputImageGUI->autoSizeToFitWidgets();
    inputImageGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(inputImageGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUI(){
    //INITIALIZE VALUES
    GUI_params.Image=false;
    GUI_params.Model=false;
    //ADDING ELEMENTS
    GUI = new ofxUISuperCanvas("GUI", OFX_UI_FONT_SMALL);
    GUI->addSpacer();
    GUI->addLabelToggle("Fullscreen", false);
    vector<string> vnames; vnames.push_back("2D"); vnames.push_back("3D");
    ofxUIRadio *radio = GUI->addRadio("GR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    //SETTINGS
    GUI->setName("GUI");
    GUI->setPosition(0,0);
    GUI->setVisible(true);
    GUI->autoSizeToFitWidgets();
    GUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(GUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUI3D(){
    //INITIALIZE VALUES
    GUI3D_params.DrawingStyle=1; //Texture
    //ADDING ELEMENTS
    GUI3D = new ofxUISuperCanvas("Model processing", OFX_UI_FONT_SMALL);
    GUI3D->addSpacer();
    vector<string> vnames; vnames.push_back("Texture"); vnames.push_back("Point Cloud"); vnames.push_back("Wireframe");
    ofxUIRadio *radio = GUI3D->addRadio("3DR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    GUI3D->addSpacer();
    dir.listDir("models/");
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    vector<string> names;
    for(int i = 0; i < (int)dir.size(); i++){
        names.push_back(dir.getName(i));
    }
    ofxUIDropDownList *ddl = GUI3D->addDropDownList("Files Models", names);
    GUI3D_params.ModelFileName=names[0];
    //SETTINGS
    GUI3D->setName("Model processing");
    GUI3D->autoSizeToFitWidgets();
    GUI3D->setColorBack(ofColor(25,25,25,200));
    ofAddListener(GUI3D->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUI2D(){
    //INITIALIZE VALUES
    GUI2D_params.ScaleFactor=10;
    //ADDING ELEMENTS
    GUI2D = new ofxUISuperCanvas("Image processing", OFX_UI_FONT_SMALL);
    GUI2D->addSpacer();
    GUI2D->addIntSlider("Scale Factor", 1, 100, &GUI2D_params.ScaleFactor);
    GUI2D->addSpacer();
    vector<string> vnames; vnames.push_back("Original"); vnames.push_back("Basic Threshold"); vnames.push_back("Adaptive Threshold"); vnames.push_back("Canny"); vnames.push_back("Laplace"); vnames.push_back("Sobel"); vnames.push_back("Corner Harris");
    ofxUIRadio *radio = GUI2D->addRadio("2DR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    GUI2D->addSpacer();
    dir.listDir("images/");
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    vector<string> names;
    for(int i = 0; i < (int)dir.size(); i++){
        names.push_back(dir.getName(i));
    }
    ofxUIDropDownList *ddl = GUI2D->addDropDownList("Files Images", names);
    GUI2D_params.ImageFileName=names[0];
    //SETTINGS
    GUI2D->setName("Image processing");
    GUI2D->autoSizeToFitWidgets();
    GUI2D->setColorBack(ofColor(25,25,25,200));
    ofAddListener(GUI2D->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIOriginal(){
    //INITIALIZE VALUES
    
    //ADDING ELEMENTS
    originalGUI = new ofxUISuperCanvas("Original", OFX_UI_FONT_SMALL);
    //SETTINGS
    originalGUI->setName("Original");
    originalGUI->autoSizeToFitWidgets();
    originalGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(originalGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIBasicThreshold(){
    //INITIALIZE VALUES
    basicGUI_params.ThreshHold=100;
    basicGUI_params.Invert=0;
    basicGUI_params.Background=false;
    basicGUI_params.GrayValue=255;
    basicGUI_params.Brightness=false;
    basicGUI_params.BrightnessValue=0;
    basicGUI_params.ContrastValue=0;
    basicGUI_params.Range=false;
    basicGUI_params.RangeMin=15;
    basicGUI_params.RangeMax=300;
    basicGUI_params.Erode=false;
    basicGUI_params.Dilate=false;
    //ADDING ELEMENTS
    basicGUI = new ofxUISuperCanvas("Basic Threshold", OFX_UI_FONT_SMALL);
    basicGUI->addSpacer();
    basicGUI->addIntSlider("Threshold", 0, 255, &basicGUI_params.ThreshHold);
    basicGUI->addIntSlider("Invert", 0, 1, &basicGUI_params.Invert);
    basicGUI->addSpacer();
    basicGUI->addToggle("Background", basicGUI_params.Background);
    basicGUI->addIntSlider("Background Gray Value", 0, 255, &basicGUI_params.GrayValue);
    basicGUI->addSpacer();
    basicGUI->addToggle("Brightness/Contrast", basicGUI_params.Brightness);
    basicGUI->addRangeSlider("Range", -1, 10, &basicGUI_params.BrightnessValue, &basicGUI_params.ContrastValue);
    basicGUI->addToggle("Range", basicGUI_params.Range);
    basicGUI->addRangeSlider("Range", 0, 1000, &basicGUI_params.RangeMin, &basicGUI_params.RangeMax);
    basicGUI->addSpacer();
    basicGUI->addToggle("Erode", basicGUI_params.Erode);
    basicGUI->addToggle("Dilate", basicGUI_params.Dilate);
    basicGUI->addLabelButton("Save", false);
    //SETTINGS
    basicGUI->setName("Basic");
    basicGUI->autoSizeToFitWidgets();
    basicGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(basicGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIAdaptiveThreshold(){
    //INITIALIZE VALUES
    adaptiveGUI_params.BlockSize=200;
    adaptiveGUI_params.Offset=15;
    adaptiveGUI_params.Invert=false;
    adaptiveGUI_params.Gauss=false;
    adaptiveGUI_params.Brightness=false;
    adaptiveGUI_params.BrightnessValue=0;
    adaptiveGUI_params.ContrastValue=0;
    adaptiveGUI_params.Range=false;
    adaptiveGUI_params.RangeMin=15;
    adaptiveGUI_params.RangeMax=300;
    adaptiveGUI_params.Erode=false;
    adaptiveGUI_params.Dilate=false;
    //ADDING ELEMENTS
    adaptiveGUI = new ofxUISuperCanvas("Adaptive Threshold", OFX_UI_FONT_SMALL);
    adaptiveGUI->addSpacer();
    adaptiveGUI->addIntSlider("Block size", 3, 1001, &adaptiveGUI_params.BlockSize);
    adaptiveGUI->addIntSlider("Offset", 0, 200, &adaptiveGUI_params.Offset);
    adaptiveGUI->addToggle("Invert", adaptiveGUI_params.Invert);
    adaptiveGUI->addToggle("Gauss", adaptiveGUI_params.Gauss);
    adaptiveGUI->addSpacer();
    adaptiveGUI->addToggle("Brightness/Contrast", adaptiveGUI_params.Brightness);
    adaptiveGUI->addRangeSlider("Range", -1, 10, &adaptiveGUI_params.BrightnessValue, &adaptiveGUI_params.ContrastValue);
    adaptiveGUI->addToggle("Range", adaptiveGUI_params.Range);
    adaptiveGUI->addRangeSlider("Range", 0, 1000, &adaptiveGUI_params.RangeMin, &adaptiveGUI_params.RangeMax);
    adaptiveGUI->addSpacer();
    adaptiveGUI->addToggle("Erode", adaptiveGUI_params.Erode);
    adaptiveGUI->addToggle("Dilate", adaptiveGUI_params.Dilate);
    adaptiveGUI->addLabelButton("Save", false);
    //SETTINGS
    adaptiveGUI->setName("Adaptive");
    adaptiveGUI->autoSizeToFitWidgets();
    adaptiveGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(adaptiveGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUICanny(){
    //INITIALIZE VALUES
    cannyGUI_params.Threshold1=50;
    cannyGUI_params.Threshold2=80;
    cannyGUI_params.Aperture=3;
    cannyGUI_params.Invert=false;
    cannyGUI_params.Dilate=false;
    cannyGUI_params.Stretch=false;
    //ADDING ELEMENTS
    cannyGUI = new ofxUISuperCanvas("Canny", OFX_UI_FONT_SMALL);
    cannyGUI->addSpacer();
    cannyGUI->addRangeSlider("Threshold", 0, 1000, &cannyGUI_params.Threshold1, &cannyGUI_params.Threshold2);
    cannyGUI->addIntSlider("Aperture Size", 3, 7, &cannyGUI_params.Aperture);
    cannyGUI->addSpacer();
    cannyGUI->addToggle("Invert", cannyGUI_params.Invert);
    cannyGUI->addToggle("Dilate", cannyGUI_params.Dilate);
    cannyGUI->addToggle("Stretch", cannyGUI_params.Stretch);
    cannyGUI->addLabelButton("Save", false);
    //SETTINGS
    cannyGUI->setName("Canny");
    cannyGUI->autoSizeToFitWidgets();
    cannyGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(cannyGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUILaplace(){
    //INITIALIZE VALUES
    laplaceGUI_params.Aperture=5;
    laplaceGUI_params.Range=false;
    laplaceGUI_params.RangeMin=15;
    laplaceGUI_params.RangeMax=300;
    laplaceGUI_params.Invert=false;
    laplaceGUI_params.BlurGaussian=false;
    laplaceGUI_params.BlurGaussianValue=1;
    laplaceGUI_params.Erode=false;
    laplaceGUI_params.Dilate=false;
    laplaceGUI_params.Stretch=false;
    //ADDING ELEMENTS
    laplaceGUI = new ofxUISuperCanvas("Laplace", OFX_UI_FONT_SMALL);
    laplaceGUI->addSpacer();
    laplaceGUI->addIntSlider("Aperture Size", 1, 7, &laplaceGUI_params.Aperture);
    laplaceGUI->addSpacer();
    laplaceGUI->addToggle("Invert", laplaceGUI_params.Invert);
    laplaceGUI->addToggle("Erode", laplaceGUI_params.Erode);
    laplaceGUI->addToggle("Dilate", laplaceGUI_params.Dilate);
    laplaceGUI->addToggle("Stretch", laplaceGUI_params.Stretch);
    laplaceGUI->addToggle("Range", laplaceGUI_params.Range);
    laplaceGUI->addRangeSlider("Range", 0, 1000, &laplaceGUI_params.RangeMin, &laplaceGUI_params.RangeMax);
    laplaceGUI->addToggle("Blur Gaussian", laplaceGUI_params.BlurGaussian);
    laplaceGUI->addIntSlider("Value", 1, 500, &laplaceGUI_params.BlurGaussianValue);
    laplaceGUI->addLabelButton("Save", false);
    //SETTINGS
    laplaceGUI->setName("Laplace");
    laplaceGUI->autoSizeToFitWidgets();
    laplaceGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(laplaceGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUISobel(){
    //INITIALIZE VALUES
    sobelGUI_params.XOrder=1;
    sobelGUI_params.YOrder=0;
    sobelGUI_params.Aperture=3;
    sobelGUI_params.Range=false;
    sobelGUI_params.RangeMax=15;
    sobelGUI_params.RangeMin=300;
    sobelGUI_params.Invert=false;
    sobelGUI_params.BlurGaussian=false;
    sobelGUI_params.BlurGaussianValue=1;
    sobelGUI_params.Erode=false;
    sobelGUI_params.Dilate=false;
    sobelGUI_params.Stretch=false;
    //ADDING ELEMENTS
    sobelGUI = new ofxUISuperCanvas("Sobel", OFX_UI_FONT_SMALL);
    sobelGUI->addSpacer();
    sobelGUI->addIntSlider("x Order", 0, 2, &sobelGUI_params.XOrder);
    sobelGUI->addIntSlider("y Order", 0, 2, &sobelGUI_params.YOrder);
    sobelGUI->addIntSlider("Aperture Size", -1, 7, &sobelGUI_params.Aperture);
    sobelGUI->addSpacer();
    sobelGUI->addToggle("Invert", sobelGUI_params.Invert);
    sobelGUI->addToggle("Erode", sobelGUI_params.Erode);
    sobelGUI->addToggle("Dilate", sobelGUI_params.Dilate);
    sobelGUI->addToggle("Stretch", sobelGUI_params.Stretch);
    sobelGUI->addToggle("Range", sobelGUI_params.Range);
    sobelGUI->addRangeSlider("Range", 0, 1000, &sobelGUI_params.RangeMin, &sobelGUI_params.RangeMax);
    sobelGUI->addToggle("Blur Gaussian", sobelGUI_params.BlurGaussian);
    sobelGUI->addIntSlider("Value", 1, 500, &sobelGUI_params.BlurGaussianValue);
    sobelGUI->addLabelButton("Save", false);
    //SETTINGS
    sobelGUI->setName("Sobel");
    sobelGUI->autoSizeToFitWidgets();
    sobelGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(sobelGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUICornerHarris(){
    //INITIALIZE VALUES
    cornerHarrisGUI_params.BlockSize=2;
    cornerHarrisGUI_params.K=0.04;
    cornerHarrisGUI_params.Aperture=3;
    cornerHarrisGUI_params.Invert=true;
    cornerHarrisGUI_params.BlurGaussian=false;
    cornerHarrisGUI_params.BlurGaussianValue=1;
    cornerHarrisGUI_params.Erode=false;
    cornerHarrisGUI_params.Dilate=false;
    //ADDING ELEMENTS
    cornerHarrisGUI = new ofxUISuperCanvas("Corner Harris", OFX_UI_FONT_SMALL);
    cornerHarrisGUI->addSpacer();
    cornerHarrisGUI->addIntSlider("Block Size", 1, 150, &cornerHarrisGUI_params.BlockSize);
    cornerHarrisGUI->addDoubleSlider("K", 0.0, 0.5, &cornerHarrisGUI_params.K);
    cornerHarrisGUI->addIntSlider("Aperture Size", -1, 7, &cornerHarrisGUI_params.Aperture);
    cornerHarrisGUI->addSpacer();
    cornerHarrisGUI->addToggle("Invert", cornerHarrisGUI_params.Invert);
    cornerHarrisGUI->addToggle("Erode", cornerHarrisGUI_params.Erode);
    cornerHarrisGUI->addToggle("Dilate", cornerHarrisGUI_params.Dilate);
    cornerHarrisGUI->addToggle("Blur Gaussian", cornerHarrisGUI_params.BlurGaussian);
    cornerHarrisGUI->addIntSlider("Value", 1, 500, &cornerHarrisGUI_params.BlurGaussianValue);
    cornerHarrisGUI->addLabelButton("Save", false);
    //SETTINGS
    cornerHarrisGUI->setName("Corner Harris");
    cornerHarrisGUI->autoSizeToFitWidgets();
    cornerHarrisGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(cornerHarrisGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIAlgorithms(){
    //INITIALIZE VALUES
    
    //ADDING ELEMENTS
    algorithmsGUI = new ofxUISuperCanvas("Algorithms", OFX_UI_FONT_SMALL);
    algorithmsGUI->addSpacer();
    vector<string> anames; anames.push_back("Morph"); anames.push_back("Triangulation");
    ofxUIRadio *aradio = algorithmsGUI->addRadio("AR", anames, OFX_UI_ORIENTATION_VERTICAL);
    //SETTINGS
    algorithmsGUI->setName("Algorithms");
    algorithmsGUI->autoSizeToFitWidgets();
    algorithmsGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(algorithmsGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIZ(){
    //INITIALIZE VALUES
    ZGUI_params.Index=0;
    ZGUI_params.Threshold=40;
    //ADDING ELEMENTS
    ZGUI = new ofxUISuperCanvas("Z Index", OFX_UI_FONT_SMALL);
    ZGUI->addIntSlider("Threshold", 1, 100, &ZGUI_params.Threshold);
    ZGUI->addSpacer();
    vector<string> znames; znames.push_back("Cylinder"); znames.push_back("Saturation"); znames.push_back("Brightness"); znames.push_back("Lightness"); znames.push_back("Alpha"); znames.push_back("Noise");
    ofxUIRadio *zradio = ZGUI->addRadio("ZR", znames, OFX_UI_ORIENTATION_VERTICAL);
    //SETTINGS
    ZGUI->setName("Z Index");
    ZGUI->autoSizeToFitWidgets();
    ZGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(ZGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIMorph(){
    //INITIALIZE VALUES
    morphGUI_params.NoiseX=2.5;
    morphGUI_params.NoiseY=0.5;
    morphGUI_params.NoiseZ=5.0;
    morphGUI_params.Speed=0.003;
    //ADDING ELEMENTS */
    morphGUI = new ofxUISuperCanvas("Morph", OFX_UI_FONT_SMALL);
    morphGUI->addSpacer();
    morphGUI->addSlider("Noise x", 0, 5.0, &morphGUI_params.NoiseX);
    morphGUI->addSlider("Noise y", 0, 5.0, &morphGUI_params.NoiseY);
    morphGUI->addSlider("Noise z", 0, 5.0, &morphGUI_params.NoiseZ);
    morphGUI->addSlider("Speed", 0.001, 0.1, &morphGUI_params.Speed);
    //SETTINGS
    morphGUI->setName("Morph");
    morphGUI->autoSizeToFitWidgets();
    morphGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(morphGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUITriangulation(){
    //INITIALIZE VALUES
    triangulationGUI_params.TrianglesMax=300;
    triangulationGUI_params.Wireframe=false;
    //ADDING ELEMENTS */
    triangulationGUI = new ofxUISuperCanvas("Triangulation", OFX_UI_FONT_SMALL);
    triangulationGUI->addSpacer();
    triangulationGUI->addIntSlider("Max Nb Triangles", 1, 1000, &triangulationGUI_params.TrianglesMax);
    triangulationGUI->addSpacer();
    triangulationGUI->addToggle("Wireframe", triangulationGUI_params.Wireframe);
    triangulationGUI->addSpacer();
    vector<string> vnames; vnames.push_back("Points"); vnames.push_back("Lines"); vnames.push_back("Line Loop"); vnames.push_back("Line Strip");  vnames.push_back("Triangles"); vnames.push_back("Triangle Fan"); vnames.push_back("Triangle Strip");
    ofxUIRadio *radio = triangulationGUI->addRadio("TR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    //SETTINGS
    triangulationGUI->setName("Triangulation");
    triangulationGUI->autoSizeToFitWidgets();
    triangulationGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(triangulationGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUILinesConnection(){
    //INITIALIZE VALUES
    linesConnectionGUI_params.Enable=false;
    linesConnectionGUI_params.Total=50;
    linesConnectionGUI_params.ConnectionDistance=50.0;
    linesConnectionGUI_params.LineWidth=1.0f;
    //ADDING ELEMENTS */
    linesConnectionGUI = new ofxUISuperCanvas("Lines Connection", OFX_UI_FONT_SMALL);
    linesConnectionGUI->addSpacer();
    linesConnectionGUI->addToggle("Enable", linesConnectionGUI_params.Enable);
    linesConnectionGUI->addIntSlider("Total Number", 0, particlesGUI_params.Total, &linesConnectionGUI_params.Total);
    linesConnectionGUI->addSlider("Connection Distance", 1.0, 200.0, &linesConnectionGUI_params.ConnectionDistance);
    linesConnectionGUI->addSlider("Line Width", 0.0, 50.0, &linesConnectionGUI_params.LineWidth);
    //SETTINGS
    linesConnectionGUI->setName("Lines Connection");
    linesConnectionGUI->setPosition(ofGetWidth()-2*particlesGUI->getRect()->getWidth()-easycamGUI->getRect()->getWidth()-lightGUI->getRect()->getWidth( )-3, ofGetHeight()/2-60);
    linesConnectionGUI->setVisible(true);
    linesConnectionGUI->autoSizeToFitWidgets();
    linesConnectionGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(linesConnectionGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIEasyCam(){
    //INITIALIZE VALUES
    easycamGUI_params.Enable=true;
    easycamGUI_params.MouseInput=false;
    easycamGUI_params.Distance=800;
    easycamGUI_params.Orbit=true;
    easycamGUI_params.RadiusOrbit=800;
    easycamGUI_params.SpeedOrbitX=12;
    easycamGUI_params.SpeedOrbitY=0;
    easycamGUI_params.Drag=0;
    //ADDING ELEMENTS */
    easycamGUI = new ofxUISuperCanvas("EasyCam", OFX_UI_FONT_SMALL);
    easycamGUI->addSpacer();
    easycamGUI->addToggle("Enable", easycamGUI_params.Enable);
    easycamGUI->addSpacer();
    easycamGUI->addToggle("Mouse Input", easycamGUI_params.MouseInput);
    easycamGUI->addIntSlider("Distance", 0, 3000, &easycamGUI_params.Distance);
    easycamGUI->addSpacer();
    easycamGUI->addToggle("Orbit", easycamGUI_params.Orbit);
    easycamGUI->addIntSlider("Radius", 0, 3000, &easycamGUI_params.RadiusOrbit);
    easycamGUI->addIntSlider("Speed X", 0, 100, &easycamGUI_params.SpeedOrbitX);
    easycamGUI->addIntSlider("Speed y", 0, 100, &easycamGUI_params.SpeedOrbitY);
    easycamGUI->addSpacer();
    easycamGUI->addSlider("Drag", 0.0, 1.0, &easycamGUI_params.Drag);
    //SETTINGS
    easycamGUI->setName("EasyCam");
    easycamGUI->autoSizeToFitWidgets();
    easycamGUI->setPosition(ofGetWidth()-2*particlesGUI->getRect()->getWidth()-1, ofGetHeight()/2-60);
    easycamGUI->setVisible(true);
    easycamGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(easycamGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIShader(){
    //INITIALIZE VALUES
    shaderGUI_params.Reload=true;
    shaderGUI_params.Enable=true;
    //ADDING ELEMENTS */
    shaderGUI = new ofxUISuperCanvas("Shader", OFX_UI_FONT_SMALL);
    shaderGUI->addSpacer();
    shaderGUI->addButton("Reload", &shaderGUI_params.Reload);
    shaderGUI->addToggle("Enable", shaderGUI_params.Enable);
    //SETTINGS
    shaderGUI->setName("Shader");
    shaderGUI->autoSizeToFitWidgets();
    shaderGUI->setPosition(ofGetWidth()-2*particlesGUI->getRect()->getWidth()-1, easycamGUI->getRect()->getY()+ easycamGUI->getRect()->getHeight()+1);
    shaderGUI->setVisible(true);
    shaderGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(shaderGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUILight(){
    //INITIALIZE VALUES
    lightGUI_params.EnableSpot=false;
    lightGUI_params.SpotRed=255;
    lightGUI_params.SpotGreen=255;
    lightGUI_params.SpotBlue=255;
    lightGUI_params.SpotCutOff=50;
    lightGUI_params.SpotConcentration=45;
    lightGUI_params.EnableDirectional=false;
    lightGUI_params.DirectionalRed=255;
    lightGUI_params.DirectionalGreen=255;
    lightGUI_params.DirectionalBlue=255;
    lightGUI_params.DirectionalX=0;
    lightGUI_params.DirectionalY=90;
    lightGUI_params.DirectionalZ=0;
    //ADDING ELEMENTS */
    lightGUI = new ofxUISuperCanvas("Lighting", OFX_UI_FONT_SMALL);
    lightGUI->addSpacer();
    lightGUI->addToggle("Enable Spot", lightGUI_params.EnableSpot);
    lightGUI->addIntSlider("Red", 0, 255, &lightGUI_params.SpotRed);
    lightGUI->addIntSlider("Green", 0, 255, &lightGUI_params.SpotGreen);
    lightGUI->addIntSlider("Blue", 0, 255, &lightGUI_params.SpotBlue);
    lightGUI->addIntSlider("Cut Off", 0, 90, &lightGUI_params.SpotCutOff);
    lightGUI->addIntSlider("Concentration", 0, 128, &lightGUI_params.SpotConcentration);
    lightGUI->addSpacer();
    lightGUI->addToggle("Enable Directional", lightGUI_params.EnableDirectional);
    lightGUI->addIntSlider("Red", 0, 255, &lightGUI_params.DirectionalRed);
    lightGUI->addIntSlider("Green", 0, 255, &lightGUI_params.DirectionalGreen);
    lightGUI->addIntSlider("Blue", 0, 255, &lightGUI_params.DirectionalBlue);
    lightGUI->addIntSlider("Euler Angle X", 0, 360, &lightGUI_params.DirectionalX);
    lightGUI->addIntSlider("Euler Angle Y", 0, 360, &lightGUI_params.DirectionalY);
    lightGUI->addIntSlider("Euler Angle Z", 0, 360, &lightGUI_params.DirectionalZ);
    //SETTINGS
    lightGUI->setName("Lighting");
    lightGUI->autoSizeToFitWidgets();
    lightGUI->setPosition(ofGetWidth()-2*particlesGUI->getRect()->getWidth()-easycamGUI->getRect()->getWidth()-2, ofGetHeight()/2-60);
    lightGUI->setVisible(true);
    lightGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(lightGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::setupGUIRecordVideo(){
    //INITIALIZE VALUES
    recordVideoGUI_params.Start=false;
    recordVideoGUI_params.Stop=false;
    //ADDING ELEMENTS */
    recordVideoGUI = new ofxUISuperCanvas("Record Video", OFX_UI_FONT_SMALL);
    recordVideoGUI->addSpacer();
    recordVideoGUI->addLabelButton("Start", &recordVideoGUI_params.Start);
    recordVideoGUI->addLabelButton("Stop", &recordVideoGUI_params.Stop);
    //SETTINGS
    recordVideoGUI->setName("Record Video");
    recordVideoGUI->autoSizeToFitWidgets();
    recordVideoGUI->setPosition(ofGetWidth()-2*particlesGUI->getRect()->getWidth()-easycamGUI->getRect()->getWidth()-lightGUI->getRect()->getWidth( )-3, linesConnectionGUI->getRect()->getY()+linesConnectionGUI->getRect()->getHeight()+1);
    recordVideoGUI->setVisible(true);
    recordVideoGUI->setColorBack(ofColor(25,25,25,200));
    ofAddListener(recordVideoGUI->newGUIEvent,this,&GUIPanel::guiEvent);
}

//--------------------------------------------------------------
void GUIPanel::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    if(kind == OFX_UI_WIDGET_TOGGLE or kind == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        string nameGUI= toggle->getCanvasParent()->getName();
        if(nameGUI=="GUI")
        {
            if(name == "Fullscreen")
            {
                ofSetFullscreen(toggle->getValue());
            }
            else if(name=="2D"){
                GUI_params.Image=toggle->getValue();
                GUI_params.Model=!toggle->getValue();
                singleGUIPressed(GUI2D, GUI);
            }
            else if(name=="3D"){
                GUI_params.Model=toggle->getValue();
                GUI_params.Image=!toggle->getValue();
                singleGUIPressed(GUI3D, GUI);
            }
        }
        else if(nameGUI=="Input Image")
        {
            if(name=="Activate Camera"){
                if (toggle->getValue()){
                    inputImageGUI_params.ActivateCamera=true;
                    m_elapsedTimeActivationCamera = ofGetElapsedTimef();
                }
                else{
                    inputImageGUI_params.ActivateCamera=false;
                }
            }
            if(name=="OFF"){
                inputImageGUI_params.Mask=GUIParams::MASKOFF;
            }
            if(name=="Inside"){
                inputImageGUI_params.Mask=GUIParams::MASKINSIDE;
            }
            if(name=="Outside"){
                inputImageGUI_params.Mask=GUIParams::MASKOUTSIDE;
            }
        }
        else if(nameGUI=="Particles")
        {
            if(name=="Load Texture"){
                if (toggle->getValue()){
                    particlesGUI_params.Texture=true;
                }
                else{
                    particlesGUI_params.Texture=false;
                }
            }
            else if(name.substr(0,6) == "MATRIX"){
                int cols = tm->getColumnCount();
                int rows = tm->getRowCount();
                for(int row = 0; row < rows; row++){
                    for(int col = 0; col < cols; col++){
                        if(tm->getState(row, col) ==1){
                            particlesGUI_params.MatrixTexture=(row*cols)+(col+1);
                            row=rows;
                            break;
                        }
                        else{
                            particlesGUI_params.MatrixTexture=0;
                        }
                    }
                }
                textureChecked=true;
            }
            
        }
        else if(nameGUI=="Model processing")
        {
            if(name=="Texture"){
                GUI3D_params.DrawingStyle=GUIParams::TEXTURE;
            }
            else if(name=="Point Cloud"){
                GUI3D_params.DrawingStyle=GUIParams::VERTICES;
            }
            else if(name=="Wireframe"){
                GUI3D_params.DrawingStyle=GUIParams::WIREFRAME;
            }
            
        }
        else if(nameGUI=="Image processing")
        {
            if(name=="Original"){
                singleGUIPressed(originalGUI, GUI2D);
                updateValue=GUIParams::ORIGINAL;
            }
            else if(name=="Basic Threshold"){
                singleGUIPressed(basicGUI, GUI2D);
                updateValue=GUIParams::BASIC;
            }
            else if(name=="Adaptive Threshold"){
                singleGUIPressed(adaptiveGUI, GUI2D);
                updateValue=GUIParams::ADAPTIVE;
            }
            else if(name=="Canny"){
                singleGUIPressed(cannyGUI, GUI2D);
                updateValue=GUIParams::CANNY;
            }
            else if(name=="Laplace"){
                singleGUIPressed(laplaceGUI, GUI2D);
                updateValue=GUIParams::LAPLACE;
            }
            else if(name=="Sobel"){
                singleGUIPressed(sobelGUI, GUI2D);
                updateValue=GUIParams::SOBEL;
            }
            else if(name=="Corner Harris"){
                singleGUIPressed(cornerHarrisGUI, GUI2D);
                updateValue=GUIParams::CORNERHARRIS;
            }
        }
        else if(nameGUI=="Basic")
        {
            if(name=="Background"){
                if (toggle->getValue()){
                    basicGUI_params.Background=true;
                }
                else{
                    basicGUI_params.Background=false;
                }
            }
            else if(name=="Brightness/Contrast"){
                if (toggle->getValue()){
                    basicGUI_params.Brightness=true;
                }
                else{
                    basicGUI_params.Brightness=false;
                }
            }
            else if(name=="Range"){
                if (toggle->getValue()){
                    basicGUI_params.Range=true;
                }
                else{
                    basicGUI_params.Range=false;
                }
            }
            else if(name=="Erode"){
                if (toggle->getValue()){
                    basicGUI_params.Erode=true;
                }
                else{
                    basicGUI_params.Erode=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    basicGUI_params.Dilate=true;
                }
                else{
                    basicGUI_params.Dilate=false;
                }
            }
        }
        else if(nameGUI=="Adaptive")
        {
            if(name=="Invert"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Invert=true;
                }
                else{
                    adaptiveGUI_params.Invert=false;
                }
            }
            else if(name=="Gauss"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Gauss=true;
                }
                else{
                    adaptiveGUI_params.Gauss=false;
                }
            }
            else if(name=="Brightness/Contrast"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Brightness=true;
                }
                else{
                    adaptiveGUI_params.Brightness=false;
                }
            }
            else if(name=="Range"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Range=true;
                }
                else{
                    adaptiveGUI_params.Range=false;
                }
            }
            else if(name=="Erode"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Erode=true;
                }
                else{
                    adaptiveGUI_params.Erode=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    adaptiveGUI_params.Dilate=true;
                }
                else{
                    adaptiveGUI_params.Dilate=false;
                }
            }
        }
        else if(nameGUI=="Canny")
        {
            
            if(name=="Invert"){
                if (toggle->getValue()){
                    cannyGUI_params.Invert=true;
                }
                else{
                    cannyGUI_params.Invert=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    cannyGUI_params.Dilate=true;
                }
                else{
                    cannyGUI_params.Dilate=false;
                }
            }
            else if(name=="Stretch"){
                if (toggle->getValue()){
                    cannyGUI_params.Stretch=true;
                }
                else{
                    cannyGUI_params.Stretch=false;
                }
            }
        }
        else if(nameGUI=="Laplace")
        {
            if(name=="Range"){
                if (toggle->getValue()){
                    laplaceGUI_params.Range=true;
                }
                else{
                    laplaceGUI_params.Range=false;
                }
            }
            else if(name=="Invert"){
                if (toggle->getValue()){
                    laplaceGUI_params.Invert=true;
                }
                else{
                    laplaceGUI_params.Invert=false;
                }
            }
            else if(name=="Erode"){
                if (toggle->getValue()){
                    laplaceGUI_params.Erode=true;
                }
                else{
                    laplaceGUI_params.Erode=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    laplaceGUI_params.Dilate=true;
                }
                else{
                    laplaceGUI_params.Dilate=false;
                }
            }
            else if(name=="Blur Gaussian"){
                if (toggle->getValue()){
                    laplaceGUI_params.BlurGaussian=true;
                }
                else{
                    laplaceGUI_params.BlurGaussian=false;
                }
            }
            else if(name=="Stretch"){
                if (toggle->getValue()){
                    laplaceGUI_params.Stretch=true;
                }
                else{
                    laplaceGUI_params.Stretch=false;
                }
            }
        }
        else if(nameGUI=="Sobel")
        {
            if(name=="Range"){
                if (toggle->getValue()){
                    sobelGUI_params.Range=true;
                }
                else{
                    sobelGUI_params.Range=false;
                }
            }
            else if(name=="Invert"){
                if (toggle->getValue()){
                    sobelGUI_params.Invert=true;
                }
                else{
                    sobelGUI_params.Invert=false;
                }
            }
            else if(name=="Erode"){
                if (toggle->getValue()){
                    sobelGUI_params.Erode=true;
                }
                else{
                    sobelGUI_params.Erode=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    sobelGUI_params.Dilate=true;
                }
                else{
                    sobelGUI_params.Dilate=false;
                }
            }
            else if(name=="Blur Gaussian"){
                if (toggle->getValue()){
                    sobelGUI_params.BlurGaussian=true;
                }
                else{
                    sobelGUI_params.BlurGaussian=false;
                }
            }
            else if(name=="Stretch"){
                if (toggle->getValue()){
                    sobelGUI_params.Stretch=true;
                }
                else{
                    sobelGUI_params.Stretch=false;
                }
            }
        }
        else if(nameGUI=="Corner Harris")
        {
            if(name=="Invert"){
                if (toggle->getValue()){
                    cornerHarrisGUI_params.Invert=true;
                }
                else{
                    cornerHarrisGUI_params.Invert=false;
                }
            }
            else if(name=="Erode"){
                if (toggle->getValue()){
                    cornerHarrisGUI_params.Erode=true;
                }
                else{
                    cornerHarrisGUI_params.Erode=false;
                }
            }
            else if(name=="Dilate"){
                if (toggle->getValue()){
                    cornerHarrisGUI_params.Dilate=true;
                }
                else{
                    cornerHarrisGUI_params.Dilate=false;
                }
            }
            else if(name=="Blur Gaussian"){
                if (toggle->getValue()){
                    cornerHarrisGUI_params.BlurGaussian=true;
                }
                else{
                    cornerHarrisGUI_params.BlurGaussian=false;
                }
            }
        }
        else if(nameGUI=="Algorithms")
        {
            if(name=="Morph"){
                resetAlgorithmsGUIs();
                setImageProcessingAsInput();
                morphGUI->setVisible(true);
                morphChecked= true;
            }
            else if(name=="Triangulation"){
                resetAlgorithmsGUIs();
                setImageProcessingAsInput();
                triangulationGUI->setVisible(true);
                triangulationChecked= true;
            }
            if(!algorithmsGUI->isMinified()){
                algorithmsGUI->toggleMinified();
            }
        }
        else if(nameGUI=="Z Index")
        {
            if(name=="Cylinder"){
                ZGUI_params.Index= GUIParams::CYLINDER;
            }
            else if(name=="Saturation"){
                ZGUI_params.Index= GUIParams::SATURATION;
            }
            else if(name=="Lightness"){
                ZGUI_params.Index= GUIParams::LIGHTNESS;
            }
            else if(name=="Brightness"){
                ZGUI_params.Index= GUIParams::BRIGHTNESS;
            }
            else if(name=="Alpha"){
                ZGUI_params.Index= GUIParams::ALPHA;
            }
            else if(name=="Noise"){
                ZGUI_params.Index = GUIParams::NOISE;
            }
        }
        else if(nameGUI=="Lines Connection")
        {
            if(name=="Enable"){
                if (toggle->getValue()){
                    linesConnectionGUI_params.Enable=true;
                }
                else{
                    linesConnectionGUI_params.Enable=false;
                }
            }
        }
        else if(nameGUI=="Triangulation")
        {
            if(name=="Points"){
                primitiveMesh=GUIParams::POINTS;
            }
            else if(name=="Lines"){
                primitiveMesh=GUIParams::LINES;
            }
            else if(name=="Line Loop"){
                primitiveMesh=GUIParams::LINE_LOOP;
            }
            else if(name=="Line Strip"){
                primitiveMesh=GUIParams::LINE_STRIP;
            }
            else if(name=="Triangles"){
                primitiveMesh=GUIParams::TRIANGLES;
            }
            else if(name=="Triangle Fan"){
                primitiveMesh=GUIParams::TRIANGLE_FAN;
            }
            else if(name=="Triangle Strip"){
                primitiveMesh=GUIParams::TRIANGLE_STRIP;
            }
            else if(name=="Wireframe"){
                if (toggle->getValue()){
                    triangulationGUI_params.Wireframe=true;
                }
                else{
                    triangulationGUI_params.Wireframe=false;
                }
            }
        }
        else if(nameGUI=="EasyCam")
        {
            if(name=="Enable"){
                if (toggle->getValue()){
                    easycamGUI_params.Enable=true;
                }
                else{
                    easycamGUI_params.Enable=false;
                }
            }
            else if(name=="Mouse Input"){
                if (toggle->getValue()){
                    easycamGUI_params.MouseInput=true;
                }
                else{
                    easycamGUI_params.MouseInput=false;
                }
            }
            else if(name=="Orbit"){
                if (toggle->getValue()){
                    easycamGUI_params.Orbit=true;
                }
                else{
                    easycamGUI_params.Orbit=false;
                }
            }
        }
        else if(nameGUI=="Shader")
        {
            if(name=="Enable"){
                if (toggle->getValue()){
                    shaderGUI_params.Enable=true;
                }
                else{
                    shaderGUI_params.Enable=false;
                }
            }
        }
        else if(nameGUI=="Lighting")
        {
            if(name=="Enable Spot"){
                if (toggle->getValue()){
                    lightGUI_params.EnableSpot=true;
                }
                else{
                    lightGUI_params.EnableSpot=false;
                }
            }
            else if(name=="Enable Directional"){
                if (toggle->getValue()){
                    lightGUI_params.EnableDirectional=true;
                }
                else{
                    lightGUI_params.EnableDirectional=false;
                }
            }
        }
    }
    else if(kind == OFX_UI_WIDGET_BUTTON or kind == OFX_UI_WIDGET_LABELBUTTON){
        ofxUIButton *button = (ofxUIButton *) e.widget;
        string nameGUI= button->getCanvasParent()->getName();
        if (button->getValue()){
            if(nameGUI=="Basic")
            {
                if(name == "Save")
                {
                    basicGUI->saveSettings("settings-basic.xml");
                    saveImage=true;
                }
            }
            else if(nameGUI=="Adaptive")
            {
                if(name == "Save")
                {
                    adaptiveGUI->saveSettings("settings-adaptive.xml");
                    saveImage=true;
                }
            }
            else if(nameGUI=="Canny")
            {
                if(name == "Save")
                {
                    cannyGUI->saveSettings("setting-canny.xml");
                    saveImage32B=true;
                }
            }
            else if(nameGUI=="Laplace")
            {
                if(name == "Save")
                {
                    laplaceGUI->saveSettings("setting-laplace.xml");
                    saveImage32B=true;
                }
            }
            else if(nameGUI=="Sobel")
            {
                if(name == "Save")
                {
                    sobelGUI->saveSettings("setting-sobel.xml");
                    saveImage32B=true;
                }
            }
            else if(nameGUI=="Corner Harris")
            {
                if(name == "Save")
                {
                    cornerHarrisGUI->saveSettings("setting-cornerHarris.xml");
                    saveImage32B=true;
                }
            }
        }
    }
    else if(kind == OFX_UI_WIDGET_DROPDOWNLIST){
        if(name == "Files Images"){
            ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
            vector<ofxUIWidget *> &selected = ddlist->getSelected();
            for(int i = 0; i < selected.size(); i++){
                GUI2D_params.ImageFileName="images/"+selected[i]->getName();
                imageFileNameChecked= true;
            }
        }
        else if(name == "Files Models"){
            ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
            vector<ofxUIWidget *> &selected = ddlist->getSelected();
            for(int i = 0; i < selected.size(); i++){
                GUI3D_params.ModelFileName="models/"+selected[i]->getName();
                modelFileNameChecked= true;
            }
        }
    }
}

//--------------------------------------------------------------
void GUIPanel::update(){
    
    updateImage();
    
    updateInputImage();
    
    update3DProcessing();
    
    updateAlgorithms();
    
}

//--------------------------------------------------------------
void GUIPanel::updateImage(){
    if(imageGUIChecked){
        
        if(!m_image){
            m_image= new ImageProcessing();
            m_image->setup();
        }
        
        if(m_model){
            //delete m_model;
        }
        
        updateImageFileName();
        
        updateScaleFactor();
        
        updateImageProcessing();
        
        updateSaveImages();
        
        imageGUIChecked=false;
    }
}

//--------------------------------------------------------------
void GUIPanel::updateImageFileName(){
    if(imageFileNameChecked){
        m_image->loadImage(GUI2D_params.ImageFileName);
        imageFileNameChecked=false;
    }
}

//--------------------------------------------------------------
void GUIPanel::updateScaleFactor(){
    m_image->setScale(GUI2D_params.ScaleFactor);
}


//--------------------------------------------------------------
void GUIPanel::updateSaveImages(){
    if(saveImage){
        m_image->saveImage(false);
        saveImage=false;
    }
    else if(saveImage32B){
        m_image->saveImage(true);
        saveImage32B=false;
    }
}

//--------------------------------------------------------------
void GUIPanel::updateImageProcessing(){
    if(GUI2D->isVisible()){
        toggleGUIPosition(GUI, GUI2D, 5);
    }
    if(originalGUI->isVisible()){
        m_image->updateOriginal(originalGUI_params);
        
        toggleGUIPosition(GUI2D, originalGUI, 5);
        toggleGUIPosition(originalGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(basicGUI->isVisible()){
        m_image->updateBasic(basicGUI_params);
        
        updateValue=GUIParams::BASIC;
        toggleGUIPosition(GUI2D, basicGUI, 5);
        toggleGUIPosition(basicGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(adaptiveGUI->isVisible()){
        m_image->updateAdaptive(adaptiveGUI_params);
        
        updateValue=GUIParams::ADAPTIVE;
        toggleGUIPosition(GUI2D, adaptiveGUI, 5);
        toggleGUIPosition(adaptiveGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(cannyGUI->isVisible()){
        m_image->updateCanny(cannyGUI_params);
        
        updateValue=GUIParams::CANNY;
        toggleGUIPosition(GUI2D, cannyGUI, 5);
        toggleGUIPosition(cannyGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(laplaceGUI->isVisible()){
        m_image->updateLaplace(laplaceGUI_params);
        
        updateValue=GUIParams::LAPLACE;
        toggleGUIPosition(GUI2D, laplaceGUI, 5);
        toggleGUIPosition(laplaceGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(sobelGUI->isVisible()){
        m_image->updateSobel(sobelGUI_params);
        
        updateValue=GUIParams::SOBEL;
        toggleGUIPosition(GUI2D, sobelGUI, 5);
        toggleGUIPosition(sobelGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
    else if(cornerHarrisGUI->isVisible()){
        m_image->updateCornerHarris(cornerHarrisGUI_params);
        
        updateValue=GUIParams::CORNERHARRIS;
        toggleGUIPosition(GUI2D, cornerHarrisGUI, 5);
        toggleGUIPosition(cornerHarrisGUI, ZGUI, 5);
        toggleGUIPosition(ZGUI, algorithmsGUI, 5);
    }
}

//--------------------------------------------------------------
void GUIPanel::createInputImage(){
    
    m_inputImage =new InputImage();
    m_inputImage->setupSize(1920,1080);
    m_inputImage->setup();
}

//--------------------------------------------------------------
void GUIPanel::checkActivationTime(){
    if( (ofGetElapsedTimef() - m_elapsedTimeActivationCamera ) > 10){
        inputImageGUI_params.ActivateCamera=false;
        ((ofxUILabelToggle *)inputImageGUI->getWidget("Activate Camera"))->setValue(false);
        
    }
}

//--------------------------------------------------------------
void GUIPanel::updateInputImage(){
    
    if(inputImageGUI_params.ActivateCamera){
        if(!m_inputImage){
            createInputImage();
        }
        else{
            m_inputImage->update();
        }
        
        checkActivationTime();
        
        
        if(inputImageGUI_params.Shoot && m_inputImage){
            m_elapsedTimeActivationCamera = ofGetElapsedTimef();
            m_inputImage->shootPicture(inputImageGUI_params.Threshold);
            inputImageGUI_params.Shoot=false;
        }
        
    }
    else{
        if(m_inputImage!=NULL){
            m_inputImage->close();
        }
    }
}

//--------------------------------------------------------------
void GUIPanel::update3DProcessing(){
    if(modelGUIChecked){
        
        if(!m_model){
            m_model= new ThreeDProcessing();
        }
        
        if(m_image){
            // delete m_image;
        }
        
        updateModelFileName();
        
        
        modelGUIChecked=false;
    }
    if(GUI3D->isVisible()){
        toggleGUIPosition(GUI, GUI3D, 5);
    }
}

//--------------------------------------------------------------
void GUIPanel::updateModelFileName(){
    if(modelFileNameChecked){
        m_model->load(GUI3D_params.ModelFileName);
        m_model->setup();
        modelFileNameChecked=false;
    }
}

//--------------------------------------------------------------
void GUIPanel::updateAlgorithms(){
    if(triangulationGUI->isVisible()){
        toggleGUIPosition(algorithmsGUI, triangulationGUI, 5);
    }
    else if(morphGUI->isVisible()){
        toggleGUIPosition(algorithmsGUI, morphGUI, 5);
    }
}

//--------------------------------------------------------------
void GUIPanel::setImageProcessingAsInput(){
    if(!originalGUI->isMinified()){
        originalGUI->toggleMinified();
    }
    else if(!basicGUI->isMinified()){
        basicGUI->toggleMinified();
    }
    else if(!adaptiveGUI->isMinified()){
        adaptiveGUI->toggleMinified();
    }
    else if(!cannyGUI->isMinified()){
        cannyGUI->toggleMinified();
    }
    else if(!laplaceGUI->isMinified()){
        laplaceGUI->toggleMinified();
    }
    else if(!sobelGUI->isMinified()){
        sobelGUI->toggleMinified();
    }
    else if(!cornerHarrisGUI->isMinified()){
        cornerHarrisGUI->toggleMinified();
    }
}


//--------------------------------------------------------------
void GUIPanel::singleGUIPressed(ofxUISuperCanvas *singleGUI, ofxUISuperCanvas *minifiedGUI){
    //resetBool();
    resetVars();
    if (minifiedGUI->getName()=="Image processing"){
        resetImageGUIs();
        ZGUI->setVisible(true);
        algorithmsGUI->setVisible(true);
    }
    else if(minifiedGUI->getName()=="Model processing"){
        resetGUIs();
        GUI3D->setVisible(true);
    }
    else if(minifiedGUI->getName()=="GUI"){
        resetGUIs();
    }
    
    singleGUI->setVisible(true);
    if(singleGUI->isMinified()){
        singleGUI->toggleMinified();
    }
    minifiedGUI->toggleMinified();
}

//--------------------------------------------------------------
void GUIPanel::updateGUIPosition(ofxUISuperCanvas *singleGUI, float x, float y){
    singleGUI->setPosition(x, y);
}


//--------------------------------------------------------------
void GUIPanel::toggleGUIPosition(ofxUISuperCanvas *parentGUI, ofxUISuperCanvas *childGUI, float offset){
    if(!parentGUI->isMinified())
        updateGUIPosition(childGUI, 0, parentGUI->getRect()->getY() + parentGUI->getRect()->getHeight()+offset/2);
    else
        updateGUIPosition(childGUI, 0, parentGUI->getCanvasTitle()->getRect()->getY()+parentGUI->getCanvasTitle()->getRect()->getHeight()+offset);
}

//--------------------------------------------------------------
void GUIPanel::draw(){
    ofBackground(255, 255, 255);
    
    drawImage();
    
    drawInputImage();
    
}

//--------------------------------------------------------------
void GUIPanel::drawImage(){
    if(GUI_params.Image){
        
        m_image->drawStartingImage();
        
        drawImageProcessing();
    }
}

//--------------------------------------------------------------
void GUIPanel::drawImageProcessing(){
    
    switch(updateValue){
        case 1:
            m_image->drawImageProcessing();
            break;
        case 2:
            m_image->drawImageProcessing();
            break;
        case 3:
            m_image->drawImageProcessing();
            break;
        case 4:
            m_image->drawImageProcessing();
            break;
        case 5:
            m_image->drawImageProcessing32B();
            break;
        case 6:
            m_image->drawImageProcessing32B();
            break;
        case 7:
            m_image->drawImageProcessing32B();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void GUIPanel::drawInputImage(){
    if(m_inputImage){
        m_inputImage->draw(inputImageGUI->getRect()->getX(),inputImageGUI->getRect()->getY()+ inputImageGUI->getRect()->getHeight(), m_inputImage->getSize().x*.1, m_inputImage->getSize().y*.1);
    }
}

//--------------------------------------------------------------
void GUIPanel::resetBool(){
    textureChecked=false;
    imageFileNameChecked= false;
    modelFileNameChecked= false;
    imageGUIChecked=false;
    modelGUIChecked=false;
    saveImage=false;
    saveImage32B=false;
    triangulationChecked=false;
    morphChecked=false;
    easyCamChecked=false;
    lightChecked=false;
    boidsChecked=false;
}

//--------------------------------------------------------------
void GUIPanel::resetVars(){
    updateValue=0;
}

//--------------------------------------------------------------
void GUIPanel::resetGUIs(){
    GUI3D->setVisible(false);
    GUI2D->setVisible(false);
    originalGUI->setVisible(false);
    basicGUI->setVisible(false);
    adaptiveGUI->setVisible(false);
    cannyGUI->setVisible(false);
    laplaceGUI->setVisible(false);
    sobelGUI->setVisible(false);
    cornerHarrisGUI->setVisible(false);
    algorithmsGUI->setVisible(false);
    ZGUI->setVisible(false);
    morphGUI->setVisible(false);
    triangulationGUI->setVisible(false);
}

//--------------------------------------------------------------
void GUIPanel::resetImageGUIs(){
    originalGUI->setVisible(false);
    basicGUI->setVisible(false);
    adaptiveGUI->setVisible(false);
    cannyGUI->setVisible(false);
    laplaceGUI->setVisible(false);
    sobelGUI->setVisible(false);
    cornerHarrisGUI->setVisible(false);
    algorithmsGUI->setVisible(false);
    ZGUI->setVisible(false);
    morphGUI->setVisible(false);
    triangulationGUI->setVisible(false);
}

//--------------------------------------------------------------
void GUIPanel::resetAlgorithmsGUIs(){
    morphGUI->setVisible(false);
    triangulationGUI->setVisible(false);
}

//--------------------------------------------------------------
void GUIPanel::keyPressed(int key){
    if(key == 'l') {
        particlesGUI->loadSettings("settings-particles.xml");
        boidsGUI->loadSettings("settings-boids.xml");
        originalGUI->loadSettings("settings-original.xml");
        basicGUI->loadSettings("settings-basic.xml");
        adaptiveGUI->loadSettings("settings-adaptive.xml");
        cannyGUI->loadSettings("setting-canny.xml");
        laplaceGUI->loadSettings("setting-laplace.xml");
        sobelGUI->loadSettings("setting-sobel.xml");
        cornerHarrisGUI->loadSettings("setting-cornerHarris.xml");
        morphGUI->loadSettings("setting-morph.xml");
        triangulationGUI->loadSettings("setting-triangulation.xml");
        linesConnectionGUI->loadSettings("setting-linesconnection.xml");
        easycamGUI->loadSettings("setting-easycam.xml");
        shaderGUI->loadSettings("setting-shader.xml");
        lightGUI->loadSettings("setting-light.xml");
        inputImageGUI->loadSettings("setting-inputimage.xml");
    }
}

//--------------------------------------------------------------
void GUIPanel::mouseReleased(int x, int y, int button){
    if (GUI->isHit(x,y) or GUI2D->isHit(x,y) or originalGUI->isHit(x,y) or basicGUI->isHit(x, y) or  adaptiveGUI->isHit(x,y) or cannyGUI->isHit(x,y) or laplaceGUI->isHit(x,y) or sobelGUI->isHit(x,y) or cornerHarrisGUI->isHit(x,y) or algorithmsGUI->isHit(x,y) or morphGUI->isHit(x,y) or triangulationGUI->isHit(x,y) or ZGUI->isHit(x,y)){
        if(triangulationGUI->isVisible()){
            triangulationChecked=true;
        }
        else if(morphGUI->isVisible()){
            morphChecked=true;
        }
        imageGUIChecked=true;
        
    }
    if (GUI->isHit(x,y) or GUI3D->isHit(x,y)){
        modelGUIChecked=true;
    }
    if (easycamGUI->isHit(x,y)){
        easyCamChecked=true;
    }
    if (lightGUI->isHit(x,y)){
        lightChecked=true;
    }
    if (boidsGUI->isHit(x,y)){
        boidsChecked=true;
    }
    
}

//--------------------------------------------------------------
void GUIPanel::dragEvent(ofDragInfo dragInfo){
    m_image->dragEvent(dragInfo);
}


