#pragma once

#define USE_PROGRAMMABLE_GL

#include "ofMain.h"
#include "GUIPanel.hpp"
#include "MSAOpenCL.h"
#include "FlockingBoids.hpp"
#include "VideoRecorder.hpp"

#include "PathFollowing.hpp"
#include "ObstacleAvoidance.hpp"
#include "PursuitAndEvade.hpp"

#define N 500000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    void setupApplication();
    void setupVideoRec();
    void setupTexture(string textureName);
    void setupEasyCam();
    void setupOpenCL();
    void setupVboMesh();
    void setupVbo();
    void setupParticles();
    void setupOpenSteer();
    void setupBoids();
    void setupLights();
    void setupFbo();
    
    void updateShaders();
    void updateParticles();
    void updateAnimation();
    void updateBoids();
    void updateOpenSteer();
    void updateParticlesTexture();
    void updateOpenCL();
    void updateTriangulation();
    void updateLinesConnection();
    void updateMorph();
    void updateLights();
    void updateAlpha();
    void updateCamera();
    void updateVideoRecord();
    
    
    void drawAnimation();
    void drawOpenSteer();
    void drawBoids();
    void drawBoidsDrawing();
    void drawMorph();
    void drawTriangulation();
    void drawLinesConnection();
    void drawScene();
    void drawMask();
    void drawInsideMask();
    void drawOutsideMask();
    void drawFboTrails();
    void drawCurrent();
    void drawVbo();
    
    void drawTextureGLPoints(int size);
    
    void beginLights();
    void endLights();
    
    void morphToCube( bool setPos );       //Morphing to cube
    void morph();
    
    shared_ptr<GUIPanel>    gui;
    
    shared_ptr<ofShader>	m_shader;
    
    //Starting time
    float                   m_startingAppTime;
    //scene alpha value
    float                   m_alpha;
    //var to check if to increse or decrease alpha value
    bool                    m_alphaGrow;
    
    //Camera
    ofEasyCam               m_cam;
    //Lights
    ofLight                 m_spotLight;
    ofLight                 m_directionalLight;
    
    //Records video from scene
    VideoRecorder*          m_videoRec;
    
    /*Boids using ofxboids*/
    //Particles boids
    FlockingBoids*          m_flock;
    //Partciles boids to morphing drawings
    FlockingBoids*          m_flockDrawing;
    
    ofTexture               m_texture;
    
    ofFbo                   m_fbo;
    
    ofFbo                   m_maskFbo;
    
    ofFbo                   m_insideMaskFbo;
    
    ofFbo                   m_outsideMaskFbo;
    
    ofVboMesh               m_linesMesh;
    
    // ofxDelaunay             m_triangulation;
    
    
    /*      OPENCL      */
    
    //Particle type - contains all information about particle except particle's position.
    typedef struct{
        float4 target;  //target point where to fly
        float speed;    //speed of flying
        float dummy1;
        float dummy2;
        float dummy3;
    } Particle;
    
    msa::OpenCL                                 m_opencl;
    
    msa::OpenCLBufferManagedT<Particle>         m_particles; // vector of Particles on host and corresponding clBuffer on device
    msa::OpenCLBufferManagedT<float4>           m_particlePos; // vector of particle positions on host and corresponding clBuffer on device
    
    msa::OpenCLBufferManagedT<Particle>         m_drawing;
    msa::OpenCLBufferManagedT<float4>           m_drawingPos;
    
    ofVbo           m_vboDrawing;
    ofVbo           m_vboParticles;
    
    
    /* OPENSTEER */
    
    void setSimulation( int simulationIndex );
    
    PathFollowing           m_pathFollowing;
    ObstacleAvoidance       m_obstacleAvoidance;
    PursuitAndEvade         m_pursuitAndEvade;
    
    vector<ofxOpenSteerPlugin*>     m_simulations;
    ofxOpenSteerPlugin*             m_currentSimulation;
    int                             m_simulationIndex;
};
