#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setupApplication();
    //setupTexture("particle_textures/dot.png");
    setupEasyCam();
    setupOpenCL();
    setupVboMesh();
    setupVbo();
    setupParticles();
    setupOpenSteer();
    setupBoids();
    setupLights();
    setupFbo();
}

//--------------------------------------------------------------
void ofApp::setupApplication(){
    ofSetVerticalSync(false);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofHideCursor();
    //ofSetFrameRate( 60 );
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    setupVideoRec();
    
    m_startingAppTime=ofGetElapsedTimeMillis();
    m_alpha=255.0f;
    m_alphaGrow=false;
}

//--------------------------------------------------------------
void ofApp::setupVideoRec(){
    
    m_videoRec= new VideoRecorder();
}

//--------------------------------------------------------------
void ofApp::setupTexture(string textureName){
    // load the texure
    ofDisableArbTex();
    ofLoadImage(m_texture, textureName);
}

//--------------------------------------------------------------
void ofApp::setupEasyCam(){
    m_cam.setDistance(gui->easycamGUI_params.Distance);
    
    if(!gui->easycamGUI_params.MouseInput){
        m_cam.disableMouseInput();    //disable mouse control - we will rotate camera by ourselves
    }
    else{
        m_cam.enableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::setupOpenCL(){
    m_opencl.setupFromOpenGL();
    m_opencl.loadProgramFromFile("Particle.cl");
    m_opencl.loadKernel("updateParticle");
    m_opencl.loadKernel("drawingParticle");
}

//--------------------------------------------------------------
void ofApp::setupVboMesh(){
    m_linesMesh.clear();
    m_linesMesh.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::setupVbo(){
    m_vboParticles.setVertexData(0, 3, sizeof(float4) * N, GL_DYNAMIC_COPY, sizeof(float4));
    m_vboDrawing.setVertexData(0, 3, sizeof(float4) * N, GL_DYNAMIC_COPY, sizeof(float4));
    
}

//--------------------------------------------------------------
void ofApp::setupParticles(){
    // init host and CL buffers
    m_particles.initBuffer( N );
    m_particlePos.initFromGLObject( m_vboParticles.getVertexBuffer().getId(), N );
    m_drawing.initBuffer( N );
    m_drawingPos.initFromGLObject( m_vboDrawing.getVertexBuffer().getId(), N );
}

//--------------------------------------------------------------
void ofApp::setupOpenSteer(){
    // add the simulations to the vector and initialize the first one
    m_simulations.push_back(&m_pathFollowing);
    m_simulations.push_back(&m_obstacleAvoidance);
    m_simulations.push_back(&m_pursuitAndEvade);
    
    m_currentSimulation = NULL;
    setSimulation(0);
}

//--------------------------------------------------------------
void ofApp::setupBoids(){
    m_flock= new FlockingBoids();
    m_flockDrawing= new FlockingBoids();
    m_flock->setup(gui->boidsGUI_params);
    m_flockDrawing->setup(gui->boidsGUI_params);
}

//--------------------------------------------------------------
void ofApp::setupLights(){
    // turn on smooth lighting //
    ofSetSmoothLighting(true);
    
    m_spotLight.setDiffuseColor(ofColor(gui->lightGUI_params.SpotRed,
                                        gui->lightGUI_params.SpotGreen,
                                        gui->lightGUI_params.SpotBlue));
    m_spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    m_spotLight.setSpotlight();
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
    m_spotLight.setSpotlightCutOff( gui->lightGUI_params.SpotCutOff );
    // rate of falloff, illumitation decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
    m_spotLight.setSpotConcentration( gui->lightGUI_params.SpotConcentration );
    
    // Directional Lights emit light based on their orientation, regardless of their position //
    m_directionalLight.setDiffuseColor(ofColor(gui->lightGUI_params.DirectionalRed,
                                               gui->lightGUI_params.DirectionalGreen,
                                               gui->lightGUI_params.DirectionalBlue));
    m_directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    m_directionalLight.setDirectional();
    m_directionalLight.setOrientation( ofVec3f(gui->lightGUI_params.DirectionalX,
                                               gui->lightGUI_params.DirectionalY,
                                               gui->lightGUI_params.DirectionalZ));
}

//--------------------------------------------------------------
void ofApp::setupFbo(){
#ifdef TARGET_OPENGLES
    m_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    m_maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    m_insideMaskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    m_outsideMaskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    m_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha
    m_maskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    m_insideMaskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    m_outsideMaskFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
#endif
    
    m_fbo.begin();
    ofClear(0,0,0, 255);
    m_fbo.end();
    
    m_maskFbo.begin();
    ofClear(0,0,0,255);
    m_maskFbo.end();
    
    m_insideMaskFbo.begin();
    ofClear(0,0,0,255);
    m_insideMaskFbo.end();
    
    m_outsideMaskFbo.begin();
    ofClear(0,0,0,255);
    m_outsideMaskFbo.end();
}


//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    updateShaders();
    
    updateParticles();
    
    updateVideoRecord();
}

//--------------------------------------------------------------
void ofApp::updateShaders(){
    if (gui->shaderGUI_params.Reload){
        
        m_shader = shared_ptr<ofShader>(new ofShader());
        
        if(ofIsGLProgrammableRenderer()){
            m_shader->load("shaders410/shader.vert", "shaders410/shader.frag");
        }
        else{
            m_shader->load("", "shaders120/shader.frag");
        }
        GLint err = glGetError();
        if (err != GL_NO_ERROR){
            ofLogNotice() << "Load Shader came back with GL error:	" << err;
        }
        gui->shaderGUI_params.Reload = false;
    }
}


//--------------------------------------------------------------
void ofApp::updateParticles(){
    updateOpenCL();
    
    updateParticlesTexture();
    
    updateAnimation();
    
    updateMorph();
    
    updateLinesConnection();
    
    updateTriangulation();
}

//--------------------------------------------------------------
void ofApp::updateOpenCL(){
    //Link parameters to OpenCL (see Particle.cl):
    m_opencl.kernel("updateParticle")->setArg(0, m_particles.getCLMem());
    m_opencl.kernel("updateParticle")->setArg(1, m_particlePos.getCLMem());
    
    m_opencl.kernel("drawingParticle")->setArg(0, m_drawing.getCLMem());
    m_opencl.kernel("drawingParticle")->setArg(1, m_drawingPos.getCLMem());
    
    //force execution of GL commands in finite time
    glFlush();
    //Execute OpenCL computation and wait it finishes
    m_opencl.kernel("updateParticle")->run1D( N );
    m_opencl.kernel("drawingParticle")->run1D( N );
    m_opencl.finish();
}

//--------------------------------------------------------------
void ofApp::updateParticlesTexture(){
    if(gui->textureChecked){
        switch(gui->particlesGUI_params.MatrixTexture){
            case 1:
                setupTexture("particle_textures/dot.png");
                break;
            case 2:
                setupTexture("particle_textures/circle1.png");
                break;
            case 3:
                setupTexture("particle_textures/circle2.png");
                break;
            case 4:
                setupTexture("particle_textures/circle3.png");
                break;
            case 5:
                setupTexture("particle_textures/jellyfish_particle.png");
                break;
            case 6:
                setupTexture("particle_textures/particle1.png");
                break;
            case 7:
                setupTexture("particle_textures/particle2.png");
                break;
            case 8:
                setupTexture("particle_textures/particle3.png");
                break;
            case 9:
                setupTexture("particle_textures/particle4.png");
                break;
            case 10:
                setupTexture("particle_textures/particle5.png");
                break;
            case 11:
                setupTexture("particle_textures/particle6.png");
                break;
            default:
                break;
        }
        gui->textureChecked=false;
    }
}

//--------------------------------------------------------------
void ofApp::updateAnimation(){
    if(false){
        //if (m_panel->GUIOPENSTEER is visible OR CHECKED)
        updateOpenSteer();
    }
    else{
        updateBoids();
    }
}

//--------------------------------------------------------------
void ofApp::updateOpenSteer(){
    m_currentSimulation->update();
}

//--------------------------------------------------------------
void ofApp::updateBoids(){
    m_flock->update(gui->particlesGUI_params.Total, gui->boidsChecked, gui->boidsGUI_params);
    m_flockDrawing->update(gui->particlesGUI_params.Total, gui->boidsChecked, gui->boidsGUI_params);
    gui->boidsChecked=false;
}

//--------------------------------------------------------------
void ofApp::updateMorph(){
    
    if(gui->morphChecked){
        gui->m_image->setupImageOutput();
        gui->m_image->setZIndex(gui->ZGUI_params.Index, gui->ZGUI_params.Threshold);
        switch(gui->updateValue){
            case 1:
                gui->m_image->scanBrightnessImage();
                break;
            default:
                gui->m_image->scanColorImage(ofColor::white);
                break;
        }
        morph();
        gui->morphChecked=false;
    }
}


//--------------------------------------------------------------
void ofApp::updateTriangulation(){
    if(gui->triangulationChecked){
        gui->morphChecked=true;
        updateMorph();
        gui->triangulationChecked=false;
    }
    if(gui->triangulationGUI->isVisible()){
        if (ofGetFrameNum() % 5 == 0){
            gui->m_image->createImgFromFbo(m_fbo);
            gui->m_image->findContourImage();
            gui->m_image->setTriangulation(gui->triangulationGUI_params);
        }
    }
}

//--------------------------------------------------------------
void ofApp::updateLinesConnection(){
    if(gui->linesConnectionGUI_params.Enable){
        m_linesMesh.clear();
        float tempX;
        float tempY;
        int iter;
        if(gui->linesConnectionGUI_params.Total>m_flockDrawing->size()){
            iter=m_flockDrawing->size();
        }
        else{
            iter=gui->linesConnectionGUI_params.Total;
        }
        for(unsigned int k=0; k<iter; k++){
            Boid3d * b = m_flockDrawing->flock3D.get(k);
            tempX= b->x - ofGetWidth()*0.5;
            tempY= b->y - ofGetHeight()*0.5;
            m_linesMesh.addVertex(ofVec3f(tempX, tempY, b->z));
            //m_linesMesh.addTexCoord(ofVec2f(tempX* ofGetWidth()/128, tempY *ofGetHeight()/53));
        }
        int numVerts = m_linesMesh.getNumVertices();
        for (int a=0; a<numVerts; ++a) {
            ofVec3f verta = m_linesMesh.getVertex(a);
            for (int b=a+1; b<numVerts; ++b) {
                ofVec3f vertb = m_linesMesh.getVertex(b);
                float distance = verta.distance(vertb);
                if (distance <= gui->linesConnectionGUI_params.ConnectionDistance) {
                    m_linesMesh.addIndex(a);
                    m_linesMesh.addIndex(b);
                    //just one "line" connection...to avoid polygons
                    break;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::updateLights(){
    if(gui->lightChecked){
        m_spotLight.setDiffuseColor(ofColor(gui->lightGUI_params.SpotRed,
                                            gui->lightGUI_params.SpotGreen,
                                            gui->lightGUI_params.SpotBlue));
        m_spotLight.setSpotlightCutOff( gui->lightGUI_params.SpotCutOff );
        m_spotLight.setSpotConcentration( gui->lightGUI_params.SpotConcentration );
        
        m_directionalLight.setDiffuseColor(ofColor(gui->lightGUI_params.DirectionalRed,
                                                   gui->lightGUI_params.DirectionalGreen,
                                                   gui->lightGUI_params.DirectionalBlue));
        m_directionalLight.setOrientation( ofVec3f(gui->lightGUI_params.DirectionalX,
                                                   gui->lightGUI_params.DirectionalY,
                                                   gui->lightGUI_params.DirectionalZ));
        gui->lightChecked=false;
    }
    if(gui->lightGUI_params.EnableSpot){
        m_spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
        m_spotLight.setPosition( mouseX, mouseY, 200);
    }
}


//--------------------------------------------------------------
void ofApp::updateAlpha(){
    if(gui->particlesGUI_params.FreqFlickering!=0){
        if(m_alphaGrow){
            m_alpha+= gui->particlesGUI_params.FreqFlickering;
            if(m_alpha>=255){
                m_alphaGrow=false;
            }
        }
        else{
            m_alpha-= gui->particlesGUI_params.FreqFlickering;
            if(m_alpha<=0){
                m_alphaGrow=true;
            }
        }
    }
    else{
        m_alpha= gui->particlesGUI_params.Alpha;
    }
    
}

//--------------------------------------------------------------
void ofApp::updateCamera(){
    if(gui->easyCamChecked){
        setupEasyCam();
        //drag is how quickly the camera picks up and slows down
        m_cam.setDrag(gui->easycamGUI_params.Drag);
        gui->easyCamChecked=false;
    }
    if(gui->easycamGUI_params.Orbit){
        float time = ofGetElapsedTimef();
        m_cam.orbit(sin(time*0.5) * gui->easycamGUI_params.SpeedOrbitX,
                    sin(time*0.5) * gui->easycamGUI_params.SpeedOrbitY,
                    gui->easycamGUI_params.RadiusOrbit,
                    ofPoint(0,0,0));
    }
}

//--------------------------------------------------------------
void ofApp::updateVideoRecord(){
    if(m_videoRec){
        if(gui->recordVideoGUI_params.Start){
            gui->recordVideoGUI_params.Start=false;
            m_videoRec->setStartRecord();
        }
        if(gui->recordVideoGUI_params.Stop){
            gui->recordVideoGUI_params.Stop=false;
            m_videoRec->setStopRecord();
        }
        m_videoRec->update(m_fbo);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    
    drawAnimation();
    
    drawScene();
}


//--------------------------------------------------------------
void ofApp::drawAnimation(){
    if(false){
        //if (m_panel->GUIOPENSTEER is visible OR CHECKED)
        drawOpenSteer();
    }
    else{
        drawBoids();
        if(!gui->morphGUI->isVisible() && !gui->triangulationGUI->isVisible()){
            drawBoidsDrawing();
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawOpenSteer(){
    for(unsigned int k=0; k<m_currentSimulation->getSize(); k++){
        ofxOpenSteerVehicle *b = m_currentSimulation->getVehicle(k);
        ofVec3f pos = b->getPosition();
        m_particlePos[k].set(pos.x, pos.y, pos.z, 0);
    }
    m_particlePos.writeToDevice();
}


//--------------------------------------------------------------
void ofApp::drawBoids(){
    float tempX;
    float tempY;
    cout<<m_flock->size()<<endl;
    for(unsigned int k=0; k<m_flock->size(); k++){
        Boid3d * b = m_flock->flock3D.get(k);
        tempX= b->x - ofGetWidth()*0.5;
        tempY= b->y - ofGetHeight()*0.5;
        m_particlePos[k].set( tempX, tempY, b->z, 0 );
    }
    m_particlePos.writeToDevice();
}

//--------------------------------------------------------------
void ofApp::drawBoidsDrawing(){
    float tempX;
    float tempY;
    for(unsigned int k=0; k<m_flockDrawing->size(); k++){
        Boid3d * b = m_flockDrawing->flock3D.get(k);
        tempX= b->x - ofGetWidth()*0.5;
        tempY= b->y - ofGetHeight()*0.5;
        m_drawingPos[k].set( tempX, tempY, b->z, 0 );
    }
    m_drawingPos.writeToDevice();
}


//--------------------------------------------------------------
void ofApp::drawScene(){
    drawMask();
    drawInsideMask();
    drawOutsideMask();
    
    m_fbo.begin();
    ofClear(0,0,0, 255);
    
    if(gui->shaderGUI_params.Enable){
        m_shader->begin();
        // Pass the image texture
        m_shader->setUniformTexture("tex0", m_outsideMaskFbo.getTexture() , 1 );
        m_shader->setUniformTexture("tex1", m_insideMaskFbo.getTexture(), 2 );
        //if(gui->inputImageGUI_params.Mask!=GUIParams::MASKOFF && gui->m_inputImage->isMaskExist()){
        m_shader->setUniformTexture("maskTex", m_maskFbo.getTexture() , 3 );
        //}
    }
    
    m_maskFbo.draw(0,0);
    
    if(gui->shaderGUI_params.Enable){
        m_shader->end();
    }
    m_fbo.end();
    
    m_fbo.draw(0,0);
}


//--------------------------------------------------------------
void ofApp::drawMask(){
    
    m_maskFbo.begin();
    ofClear(255, 0, 0,255);
    if(gui->inputImageGUI_params.Mask!=GUIParams::MASKOFF && gui->m_inputImage->isMaskExist()){
        gui->m_inputImage->m_contourFinder.draw(0,0, ofGetWidth(),ofGetHeight());
    }
    m_maskFbo.end();
}

//--------------------------------------------------------------
void ofApp::drawInsideMask(){
    m_insideMaskFbo.begin();
    
    if(gui->inputImageGUI_params.Mask==GUIParams::MASKINSIDE && gui->m_inputImage->isMaskExist()){
        drawCurrent();
    }
    else if(gui->inputImageGUI_params.Mask==GUIParams::MASKOUTSIDE){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    }
    
    m_insideMaskFbo.end();
}

//--------------------------------------------------------------
void ofApp::drawOutsideMask(){
    m_outsideMaskFbo.begin();
    
    if(gui->inputImageGUI_params.Mask==GUIParams::MASKINSIDE){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    }
    else{
        drawCurrent();
    }
    
    m_outsideMaskFbo.end();
}


//--------------------------------------------------------------
void ofApp::drawCurrent(){
    glDepthMask(GL_FALSE);
    
    drawFboTrails();
    
    beginLights();
    
    updateCamera();
    
    if(gui->easycamGUI_params.Enable){
        m_cam.begin();
    }
    
    m_opencl.finish();
    
    updateAlpha();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //ofEnablePointSprites();
    
    ofSetColor(gui->particlesGUI_params.Red, gui->particlesGUI_params.Green, gui->particlesGUI_params.Blue, m_alpha);
    
    glPointSize(gui->particlesGUI_params.Size);
    
    drawVbo();
    
    drawTriangulation();
    
    drawLinesConnection();
    
    ofDisablePointSprites();
    ofDisableBlendMode();
    
    if(gui->easycamGUI_params.Enable){
        m_cam.end();
    }
    
    endLights();
    
    glDepthMask(GL_TRUE);
}

//--------------------------------------------------------------
void ofApp::drawFboTrails(){
    ofEnableAlphaBlending();
    if(gui->particlesGUI_params.AlphaFboTrails<51){
        ofFill();
        ofSetColor(255,255,255, gui->particlesGUI_params.AlphaFboTrails);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    }
    else{
        ofClear(0,0,0, 255);
    }
}


//--------------------------------------------------------------
void ofApp::beginLights(){
    if(gui->lightGUI_params.EnableSpot or gui->lightGUI_params.EnableDirectional){
        ofEnableLighting();
        updateLights();
    }
    if(gui->lightGUI_params.EnableSpot){
        m_spotLight.enable();
    }
    if(gui->lightGUI_params.EnableDirectional) {
        m_directionalLight.enable();
    }
}

//--------------------------------------------------------------
void ofApp::endLights(){
    if(gui->lightGUI_params.EnableSpot){
        m_spotLight.disable();
    }
    if(gui->lightGUI_params.EnableDirectional){
        m_directionalLight.disable();
    }
    if(gui->lightGUI_params.EnableSpot or gui->lightGUI_params.EnableDirectional){
        ofDisableLighting();
    }
}

//--------------------------------------------------------------
void ofApp::drawVbo(){
    
    if(gui->particlesGUI_params.Texture && m_texture.isAllocated()){
        m_texture.bind();
    }
    
    m_vboParticles.draw(GL_POINTS, 0, m_flock->size());
    
    m_vboDrawing.draw(GL_POINTS, 0, m_flockDrawing->size());
    
    if(gui->particlesGUI_params.Texture && m_texture.isAllocated()){
        m_texture.unbind();
    }
}


//--------------------------------------------------------------
void ofApp::drawTriangulation(){
    if(gui->triangulationGUI->isVisible()){
        ofPushMatrix();
        ofTranslate(-ofGetWidth()*0.5-50, -ofGetHeight()*0.5+50);
        gui->m_image->getVboMesh().drawInstanced(OF_MESH_WIREFRAME, 0);
        ofPopMatrix();
    }
    //if(m_triangulation.getNumPoints()!=0 /*and panel->triangulationGUI->isVisible()*/){
    //    m_triangulation.triangleMesh.drawInstanced(OF_MESH_WIREFRAME, 0);
    //}*/
}

//--------------------------------------------------------------
void ofApp::drawLinesConnection(){
    if(m_linesMesh.getNumIndices()!=0 && gui->linesConnectionGUI_params.Enable){
        //texture.bind();
        ofSetLineWidth(gui->linesConnectionGUI_params.LineWidth);
        m_linesMesh.draw(OF_MESH_FILL);
        //texture.unbind();
    }
}


//--------------------------------------------------------------
void ofApp::morph(){
    //if(panel->getMorphChecked()){
    ofMesh mesh = gui->m_image->getMesh();
    
    //Set up particles
    double scl = gui->m_image->getScaledMeshFactor()*2;
    float noisex = gui->morphGUI_params.NoiseX;
    float noisey = gui->morphGUI_params.NoiseY;
    float noisez = gui->morphGUI_params.NoiseZ;
    for(int i=0; i<gui->particlesGUI_params.Total; i++) {
        Particle &p = m_drawing[i];
        unsigned int q = (int)ofRandom( 0, mesh.getNumVertices());
        ofVec3f vertex = mesh.getVertex(q);
        vertex.x -= gui->m_image->getWidthImage()*0.5;   //centering
        vertex.y -= gui->m_image->getHeightImage()*0.5;
        vertex.x *= scl;       //scaling
        vertex.y *= -scl;
        
        //add noise to x, y
        vertex.x += ofRandom( -scl*0.5, scl*0.5);
        vertex.y += ofRandom( -scl*0.5, scl*0.5 );
        
        vertex.x += ofRandom( -noisex, noisex );
        vertex.y += ofRandom( -noisey, noisey );
        
        //add noise to z
        vertex.z += ofRandom( -noisez, noisez );
        
        //set to particle
        p.target.set( vertex.x, vertex.y, vertex.z, 0 );
        p.speed = gui->morphGUI_params.Speed;
    }
    
    //upload to GPU
    m_drawing.writeToDevice();
    //  }
}

//--------------------------------------------------------------
void ofApp::morphToCube( bool setPos ) {       //Morphing to cube
    
    for(int i=0; i<N; i++) {
        //Getting random point at cube
        float rad = 90;
        ofPoint pnt( ofRandom(-rad, rad), ofRandom(-rad, rad), ofRandom(-rad, rad) );
        
        //project point on cube's surface
        int axe = ofRandom( 0, 3 );
        if ( axe == 0 ) { pnt.x = ( pnt.x >= 0 ) ? rad : (-rad ); }
        if ( axe == 1 ) { pnt.y = ( pnt.y >= 0 ) ? rad : (-rad ); }
        if ( axe == 2 ) { pnt.z = ( pnt.z >= 0 ) ? rad : (-rad ); }
        axe = (axe + 1)%3;
        if ( axe == 0 ) { pnt.x = ( pnt.x >= 0 ) ? rad : (-rad ); }
        if ( axe == 1 ) { pnt.y = ( pnt.y >= 0 ) ? rad : (-rad ); }
        if ( axe == 2 ) { pnt.z = ( pnt.z >= 0 ) ? rad : (-rad ); }
        
        //add noise
        //float noise = 10;
        //pnt.x += ofRandom( -noise, noise );
        //pnt.y += ofRandom( -noise, noise );
        //pnt.z += ofRandom( -noise, noise );
        
        pnt.y -= 150;   //shift down
        
        //Setting to particle
        Particle &p = m_particles[i];
        p.target.set( pnt.x, pnt.y, pnt.z, 0 );
        p.speed = 0.05;
        
        /*if ( setPos ) {
         particlePos[i].set( pnt.x, pnt.y, pnt.z, 0 );
         }*/
    }
    
    //upload to GPU
    m_particles.writeToDevice();
    if ( setPos ) {
        m_particlePos.writeToDevice();
    }
}

//--------------------------------------------------------------
void ofApp::setSimulation( int simulationIndex ){
    // just make sure we are inside out vector
    m_simulationIndex = ofClamp(m_simulationIndex, 0, m_simulations.size() - 1);
    
    // exit the current simulation
    if(m_currentSimulation){
        m_currentSimulation->exit();
    }
    
    // define the current simulation
    m_currentSimulation = m_simulations[m_simulationIndex];
    
    // initialize the current simulation
    m_currentSimulation->setSize(gui->particlesGUI_params.Total);
    m_currentSimulation->setup();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    morphToCube(true);
    gui->keyPressed(key);
    if( key == OF_KEY_LEFT ){
        m_simulationIndex--;
        if(m_simulationIndex < 0){
            m_simulationIndex = m_simulations.size() - 1;
        }
        setSimulation(m_simulationIndex);
    }
    else if( key == OF_KEY_RIGHT ){
        m_simulationIndex++;
        if(m_simulationIndex > m_simulations.size() - 1){
            m_simulationIndex = 0;
        }
        setSimulation(m_simulationIndex);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // gui->mouseReleased( x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
    if(m_videoRec)
        delete m_videoRec;
    if(m_flock)
        delete m_flock;
    if(m_flockDrawing)
        delete m_flockDrawing;
}

