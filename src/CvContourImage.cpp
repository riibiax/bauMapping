#include "CvContourImage.hpp"

//--------------------------------------------------------------
CvContourImage::CvContourImage():ofxCvContourFinder()
{

}

//--------------------------------------------------------------
CvContourImage::~CvContourImage()
{
    free( myMoments );
}

//--------------------------------------------------------------
void CvContourImage::setVertices() {
    
    m_paths.clear();
    for( int i=0; i<(int)blobs.size(); i++ ) {
        
        ofPath temp;
        for( int j=0; j<blobs[i].nPts; j=j+10) {
            temp.lineTo(blobs[i].pts[j].x, blobs[i].pts[j].y);
        }
        temp.close();
        m_paths.push_back(temp);
    }
}


//--------------------------------------------------------------
void CvContourImage::draw(float x, float y, float w, float h ) const{
    float scalex = 0.0f;
    float scaley = 0.0f;
    if( _width != 0 ) { scalex = w/_width; } else { scalex = 1.0f; }
    if( _height != 0 ) { scaley = h/_height; } else { scaley = 1.0f; }
    
    if(bAnchorIsPct){
        x -= anchor.x * w;
        y -= anchor.y * h;
    }else{
        x -= anchor.x;
        y -= anchor.y;
    }
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate( x, y, 0.0 );
    ofScale( scalex, scaley, 0.0 );
    
    
    // ---------------------------- draw the blobs
    ofSetHexColor(0x00FFFF);
    
    
    for( int i=0; i<m_paths.size(); i++ ) {
        ofVboMesh vboM = m_paths[i].getTessellation();
        vboM.draw(OF_MESH_FILL);
    }
    
    ofPopMatrix();
    ofPopStyle();
}
