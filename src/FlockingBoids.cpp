#include "FlockingBoids.hpp"

//--------------------------------------------------------------
FlockingBoids::FlockingBoids()
{
    
}

//--------------------------------------------------------------
FlockingBoids::~FlockingBoids()
{

}

//--------------------------------------------------------------
void FlockingBoids::setup(){
    flock3D.setup(500, ofGetWidth()/2, ofGetHeight()/2,-ofGetHeight()/2, 1);
    flock3D.setBounds(0,0,-ofGetHeight()/2,ofGetWidth(), ofGetHeight(),0);
    flock3D.setBoundmode(2);
}

//--------------------------------------------------------------
void FlockingBoids::setup(GUIParams::boidsGUI_p params){
    flock3D.setup(500, ofGetWidth()/2, ofGetHeight()/2,-ofGetHeight()/2, 1);
    flock3D.setMaxSpeed(params.Speed);
    flock3D.setAlign(params.Align);
    flock3D.setDistSeparation(params.DistSeparation);
    flock3D.setMaxForce(params.GravityForce);
    flock3D.setBounds(0,0,-ofGetHeight()/2,ofGetWidth(), ofGetHeight(),0);
    flock3D.setBoundmode(params.BoundMode);
    //TODO set Lifetime from GUI in Flock class
}

//--------------------------------------------------------------
void FlockingBoids::update(int total, bool BUpdateSetting, GUIParams::boidsGUI_p params){

    updateSettings(BUpdateSetting, params);

    flock3D.update();
    
    deleteBoids();
    
    updateEmmiterBoids(total);
}

//--------------------------------------------------------------
void FlockingBoids::updateSettings(bool BUpdateSetting, GUIParams::boidsGUI_p params){
    if(BUpdateSetting){
        flock3D.setMaxSpeed(params.Speed);
        flock3D.setAlign(params.Align);
        flock3D.setDistSeparation(params.DistSeparation);
        flock3D.setMaxForce(params.GravityForce);
        flock3D.setBoundmode(params.BoundMode);
    }

}


//--------------------------------------------------------------
void FlockingBoids::updateEmmiterBoids(int total){
    if (flock3D.size()<total){
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        float z = 0;// ofRandom(-ofGetHeight()/4, ofGetHeight()/4);
        flock3D.add(x, y, z);
    }
}

//--------------------------------------------------------------
void FlockingBoids::deleteBoids(){
    /*if(ofGetFrameNum()%240==0){
     flock.removeBoid(0);
     } */
    
    for (unsigned i=0; i<flock3D.size(); i++){
        Boid3d * b = flock3D.get(i);
        if(b->getLife()==0.0f){
            //flock3D.removeBoid(i);
        }
    }
}

//--------------------------------------------------------------
void FlockingBoids::setBoidsAttractors(){
    /*ofMesh mesh = image->getMesh();
    for(int i=0; i<mesh.getNumVertices(); i++) {
        float force = ofRandom(4000,10000);
        float dist = ofRandom(80,100);
        flock.addAttractionPoint(mesh.getVertex(i).x,mesh.getVertex(i).y,mesh.getVertex(i).z,force,dist);
    }*/
}