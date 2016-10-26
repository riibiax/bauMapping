#include "ThreeDProcessing.hpp"


//--------------------------------------------------------------
ThreeDProcessing::ThreeDProcessing()
{
    
}

//--------------------------------------------------------------
ThreeDProcessing::~ThreeDProcessing()
{
    
}

//--------------------------------------------------------------
void ThreeDProcessing::load(string fileName){
    cout<< fileName<<endl;
    m_model.loadModel(fileName, true);
}

//--------------------------------------------------------------
void ThreeDProcessing::setup(){
    
    m_model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.75, 0);
}

//--------------------------------------------------------------
void ThreeDProcessing::update(){
    m_model.update();
}

//--------------------------------------------------------------
void ThreeDProcessing::draw(){
    //get the model attributes we need
    ofVec3f scale = m_model.getScale();
    ofVec3f position = m_model.getPosition();
    float normalizedScale = m_model.getNormalizedScale();
    ofVboMesh mesh = m_model.getMesh(0);
    ofTexture texture;
    ofxAssimpMeshHelper& meshHelper = m_model.getMeshHelper( 0 );
    bool bHasTexture = meshHelper.hasTexture();
    if( bHasTexture ) {
        texture = m_model.getTextureForMesh(0);
    }
    
    ofMaterial material = m_model.getMaterialForMesh(0);
    
    ofPushMatrix();
    
    //translate and scale based on the positioning.
    ofTranslate(position);
    ofRotate(-ofGetMouseX(), 0, 1, 0);
    ofRotate(90,1,0,0);
    
    
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
    //modify mesh with some noise
  /*  float liquidness = 5;
    float amplitude = mouseY/100.0;
    float speedDampen = 5;
    vector<ofVec3f>& verts = mesh.getVertices();
    for(unsigned int i = 0; i < verts.size(); i++){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }*/
    
    //draw the model manually
    if(bHasTexture) texture.bind();
    material.begin();
    mesh.drawWireframe(); //you can draw wireframe too
    //mesh.drawFaces();
    material.end();
    if(bHasTexture) texture.unbind();
    
    ofPopMatrix();
    

}
