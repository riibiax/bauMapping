#include "ofMain.h"
#include "ofApp.h"
#include "GUIPanel.hpp"
#include "ofAppGLFWWindow.h"


#ifdef USE_PROGRAMMABLE_GL
    #include "ofGLProgrammableRenderer.h"
#endif

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    
    settings.width = 1280;
    settings.height = 768;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;

    
#ifdef USE_PROGRAMMABLE_GL
    settings.setGLVersion(4, 1);
#else
    settings.setGLVersion(2, 1);
#endif
    
    auto mainWindow = ofCreateWindow(settings);
    mainWindow->setVerticalSync(false);
    
    settings.width = 1280;
    settings.height = 768;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;

    auto guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<GUIPanel> guiApp(new GUIPanel);
    mainApp->gui = guiApp;
    
    
    ofRunApp(guiWindow, guiApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
