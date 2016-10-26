#include "ImageProcessing.hpp"
//--------------------------------------------------------------
ImageProcessing::ImageProcessing()
{
    
}

//--------------------------------------------------------------
ImageProcessing::~ImageProcessing()
{
    
}

//--------------------------------------------------------------
void ImageProcessing::setup(){
    m_counter=0;
    loadImage("images/221307_bearbeitet.jpg");
    //glEnable( GL_POINT_SMOOTH );
    m_mesh.clear();
    m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    m_vboMesh.clear();
    m_vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

//--------------------------------------------------------------
void ImageProcessing::loadImage(string imageFileName){
    m_image.load(imageFileName);
    m_image.setImageType(OF_IMAGE_COLOR);
    if(m_image.isAllocated()){
        setupImages();
    }
}

//--------------------------------------------------------------
void ImageProcessing::setupImages(){
    
    m_width = m_image.getWidth();
    m_height = m_image.getHeight();
    
    m_drawingHeight= 300;
    m_drawingWidth= (int)(m_width/(float)(m_height/300.0));
    
    m_scaleFactor= 1;
    setScale(m_scaleFactor);
    
    allocateImages();
    
    m_colorImg.setFromPixels(m_image.getPixels());
    m_grayImage = m_colorImg;
}

//--------------------------------------------------------------
void ImageProcessing::setScale(int scaleFactor){
   // if(m_scaleFactor!=scaleFactor){
        m_scaleFactor=scaleFactor;
        m_scaledWidth=(int)(m_width/scaleFactor);
        m_scaledHeight=(int)(m_height/scaleFactor);
  //  }
}

//--------------------------------------------------------------
void ImageProcessing::allocateImages(){
    m_colorImg.clear();
    m_colorImg.allocate(m_width,m_height);
    m_tempColor.clear();
    m_tempColor.allocate(m_width,m_height);
    m_colorResult.clear();
    m_colorResult.allocate(m_width, m_height);
    m_grayImage.clear();
    m_grayImage.allocate(m_width,m_height);
    m_grayBg.clear();
    m_grayBg.allocate(m_width,m_height);
    
    m_outputImage32B.clear();
    m_outputImage32B.allocate(m_width, m_height);
    m_outputImage.clear();
    m_outputImage.allocate(m_width, m_height);
    m_colorContour.clear();
    m_colorContour.allocate(ofGetWidth(), ofGetHeight());
    m_temp.clear();
    m_temp.allocate(ofGetWidth(), ofGetHeight());
    
    m_result.clear();
    m_result.allocate(m_width, m_height, OF_IMAGE_GRAYSCALE);
    m_img.clear();
    m_img.allocate(m_width, m_height, OF_IMAGE_COLOR);

}

//--------------------------------------------------------------
void ImageProcessing::updateOriginal(GUIParams::originalGUI_p params){
    m_outputImage = m_colorImg;
}

//--------------------------------------------------------------
void ImageProcessing::updateBasic(GUIParams::basicGUI_p params){
    if(params.Background){
        m_img.setColor(ofColor(params.GrayValue,params.GrayValue,params.GrayValue));
        m_img.update();
        m_grayBg.setFromPixels(m_img.getPixels());
        m_outputImage.absDiff(m_grayBg, m_grayImage);
    }
    else
        m_outputImage=m_grayImage;
    if(params.Range)
        m_outputImage.convertToRange(params.RangeMin, params.RangeMax);
    if(params.Brightness)
        m_outputImage.brightnessContrast(params.BrightnessValue, params.ContrastValue);
    m_outputImage.threshold(params.ThreshHold, params.Invert);
    if(params.Erode)
        m_outputImage.erode();
    if(params.Dilate)
        m_outputImage.dilate();
    m_outputImage.contrastStretch();
    m_outputImage.flagImageChanged();
}


//--------------------------------------------------------------
void ImageProcessing::updateAdaptive(GUIParams::adaptiveGUI_p params){
    m_outputImage =m_grayImage;
    if (params.Range)
        m_outputImage.convertToRange(params.RangeMin, params.RangeMax); // super low contrast
    if(params.Brightness)
        m_outputImage.brightnessContrast(params.BrightnessValue, params.ContrastValue);
    if(params.BlockSize % 2 == 0)
        params.BlockSize++;
    m_outputImage.adaptiveThreshold(params.BlockSize, params.Offset, params.Invert, params.Gauss);
    if(params.Erode)
        m_outputImage.erode();
    if(params.Dilate)
        m_outputImage.dilate();
    m_outputImage.contrastStretch();
    m_outputImage.flagImageChanged();
}


//--------------------------------------------------------------
void ImageProcessing::updateCanny(GUIParams::cannyGUI_p params){
    if(params.Aperture % 2 == 0)
        params.Aperture++;
    cvCanny(m_grayImage.getCvImage(), m_outputImage.getCvImage(), (double)params.Threshold1, (double)params.Threshold2, params.Aperture);
    if(params.Dilate)
        m_outputImage.dilate();
    if(params.Invert)
        m_outputImage.invert();
    if(params.Stretch)
        m_outputImage.contrastStretch();
    m_outputImage.flagImageChanged();
}

//--------------------------------------------------------------
void ImageProcessing::updateLaplace(GUIParams::laplaceGUI_p params){
    if(params.Aperture % 2 == 0)
        params.Aperture++;
    if(params.BlurGaussianValue % 2 == 0)
        params.BlurGaussianValue++;
    cvLaplace(m_grayImage.getCvImage(), m_outputImage32B.getCvImage(),params.Aperture);
    if (params.Range)
        m_outputImage32B.convertToRange(params.RangeMin, params.RangeMax); // super low contrast
    if(params.BlurGaussian)
        m_outputImage32B.blurGaussian(params.BlurGaussianValue);
    if(params.Erode)
        m_outputImage32B.erode();
    if(params.Dilate)
        m_outputImage32B.dilate();
    if(params.Invert)
        m_outputImage32B.invert();
    if(params.Stretch)
        m_outputImage32B.contrastStretch();
    m_outputImage32B.flagImageChanged();
}

//--------------------------------------------------------------
void ImageProcessing::updateSobel(GUIParams::sobelGUI_p params){
    if(params.Aperture % 2 == 0)
        params.Aperture++;
    if(params.XOrder==params.YOrder && params.XOrder==0)
        params.XOrder=1;
    cvSobel(m_grayImage.getCvImage(), m_outputImage32B.getCvImage(),params.XOrder,params.YOrder,params.Aperture);
    if (params.Range)
        m_outputImage32B.convertToRange(params.RangeMin, params.RangeMax); // super low contrast
    if(params.BlurGaussian)
        m_outputImage32B.blurGaussian(params.BlurGaussianValue);
    if(params.Erode)
        m_outputImage32B.erode();
    if(params.Dilate)
        m_outputImage32B.dilate();
    if(params.Invert)
        m_outputImage32B.invert();
    if(params.Stretch)
        m_outputImage32B.contrastStretch();
    m_outputImage32B.flagImageChanged();
}

//--------------------------------------------------------------
void ImageProcessing::updateCornerHarris(GUIParams::cornerHarrisGUI_p params){
    if(params.Aperture % 2 == 0)
        params.Aperture++;
    cvCornerHarris(m_grayImage.getCvImage(), m_outputImage32B.getCvImage(),params.BlockSize, params.Aperture, params.K);
    if(params.BlurGaussian)
        m_outputImage32B.blurGaussian(params.BlurGaussianValue);
    if(params.Erode)
        m_outputImage32B.erode();
    if(params.Dilate)
        m_outputImage32B.dilate();
    if(params.Invert)
        m_outputImage32B.invert();
    m_outputImage32B.flagImageChanged();
}


//--------------------------------------------------------------
void ImageProcessing::saveImage(bool image32B){
    if(image32B){
        m_colorResult=m_outputImage32B;
    }
    else{
        m_colorResult=m_outputImage;
    }
    //unsigned char * pixels = m_colorResult.getPixels();
    //m_result.setFromPixels(pixels, m_width,m_height, OF_IMAGE_COLOR);
    //m_result.save("result-"+ofToString(m_counter)+".png");
    m_counter++;
}


//--------------------------------------------------------------
void ImageProcessing::drawStartingImage(){
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofNoFill();
    ofSetColor(0,0,0);
    m_rect= ofRectangle(/*GUI->getRect()->getWidth()*/211+5.0f, 1.0f, m_drawingWidth, m_drawingHeight);
    ofDrawRectangle(m_rect);
    ofDrawBitmapString("drop an image here", m_rect.getCenter().x-70, m_drawingHeight+10);
    ofSetColor(255);
    if( m_image.getWidth() > 0 ){
        m_image.draw(m_rect.x, m_rect.y, m_drawingWidth, m_drawingHeight);
    }
}

//--------------------------------------------------------------
void ImageProcessing::drawImageProcessing(){
    m_outputImage.draw(/*GUI->getRect()->getWidth()*/211+10+m_drawingWidth, 0, m_drawingWidth, m_drawingHeight);
}

//--------------------------------------------------------------
void ImageProcessing::drawImageProcessing32B(){
    m_outputImage32B.draw(/*GUI->getRect()->getWidth()*/211+10+m_drawingWidth, 0, m_drawingWidth, m_drawingHeight);
}

//--------------------------------------------------------------
void ImageProcessing::dragEvent(ofDragInfo dragInfo){
    if( m_rect.inside( dragInfo.position ) ){
        loadImage( dragInfo.files[0] );
        //meshToUpdate=true;
    }
}

//--------------------------------------------------------------
void ImageProcessing::setupImageOutput(){

    m_tempColor=m_outputImage;
    m_tempColor.resize(m_scaledWidth, m_scaledHeight);
}

//--------------------------------------------------------------
void ImageProcessing::setupImageOutput32B(){
    
    m_tempColor=m_outputImage32B;
    m_tempColor.resize(m_scaledWidth, m_scaledHeight);
}

//--------------------------------------------------------------
void ImageProcessing::scanColorImage(ofColor color){
    m_mesh.clear();
    float z;
    for (unsigned int y=0; y<m_scaledHeight; y++) {
        for (unsigned int x=0; x<m_scaledWidth; x++) {
            ofColor c = m_tempColor.getPixels().getColor(x,y);
            if(c == color){
                 z=getZIndex(c, x*m_scaleFactor);
                 m_mesh.addVertex(ofVec3f(x*m_scaleFactor,y*m_scaleFactor, z));

            }
        }
    }
}

//--------------------------------------------------------------
void ImageProcessing::scanBrightnessImage(){
    /*m_points.clear();
    for (int y=0; y<m_scaledHeight; y++) {
        for (int x=0; x<m_scaledWidth; x++) {
            int v = m_tempColor.getPixelsRef().getColor(x, y).getBrightness()*0.5;
            if(m_points.size()>67108808){
                break;
            }
            for (int i=0; i<v; i++) {
                m_points.push_back(ofVec3f(x*m_scaleFactor,y*m_scaleFactor, 0));
            }
        }
    }*/
}


//--------------------------------------------------------------
void ImageProcessing::setZIndex(int zIndex, int zThreshold){
    m_z=zIndex;
    m_zThreshold = zThreshold;
}

//--------------------------------------------------------------
float ImageProcessing::getZIndex(ofColor pixel, float vertexX){
    float tempZ;
    switch(m_z){
        case 0:
            tempZ = getZCylinder(vertexX);
            break;
        case 1:
            tempZ = getZPixel(pixel.getSaturation());
            break;
        case 2:
            tempZ = getZPixel(pixel.getBrightness());
            break;
        case 3:
            tempZ = getZPixel(pixel.getLightness());
            break;
        case 4:
            tempZ = getZPixel(pixel.a);
            break;
        case 5:
            tempZ = getZRandom();
            break;
        default:
            tempZ = getZCylinder(vertexX);
            break;
    }
    return tempZ;
}


//--------------------------------------------------------------
float ImageProcessing::getZCylinder(float vertexX){
    //peojection on cylinder
    float Rad= m_width /** getScaledMeshFactor()*/ * m_zThreshold*0.01; //in this case zThreshold is the Radius
    float z;
    z = (sqrt( fabs( Rad * Rad - vertexX * vertexX ) ) - Rad)/5;
    return z;
}


//--------------------------------------------------------------
float ImageProcessing::getZPixel(float value){
    float   z;
    return  z = ofMap(value, 0, 255, -m_zThreshold, m_zThreshold);
}


//--------------------------------------------------------------
float ImageProcessing::getZRandom(){
    float   z;
    return  z = ofRandom(-m_zThreshold, m_zThreshold);

}

//--------------------------------------------------------------
void ImageProcessing::setTriangulation(GUIParams::triangulationGUI_p params){

    m_vboMesh.clear();
    //cout<<m_contourFinder.nBlobs<<endl;
    for(unsigned int i = 0; i < m_contourFinder.nBlobs; i++) {
        
        m_triangle.clear();
        m_triangle.triangulate(m_contourFinder.blobs[i].pts, params.TrianglesMax);
        
        for (int k = 0; k < m_triangle.nTriangles; k++){
            /*ofVec3f a = m_triangle.triangles[k].a * m_scaleFactor;
            ofVec3f b = m_triangle.triangles[k].b * m_scaleFactor;
            ofVec3f c = m_triangle.triangles[k].c * m_scaleFactor;*/
            
            ofVec3f a = m_triangle.triangles[k].a * m_scaleFactor;
            ofVec3f b = m_triangle.triangles[k].b;
            ofVec3f c = m_triangle.triangles[k].c;
            m_vboMesh.addTexCoord(a);
            m_vboMesh.addVertex(a);
            m_vboMesh.addTexCoord(b);
            m_vboMesh.addVertex(b);
            m_vboMesh.addTexCoord(c);
            m_vboMesh.addVertex(c);
        }
        
    }
    setNormals(m_vboMesh);
}

//--------------------------------------------------------------
void ImageProcessing::setNormals(ofMesh &mesh){
    //The number of vertices
    int nV = mesh.getNumVertices();
    //The number of triangles
    int nT = mesh.getNumIndices() / 3;
    vector<ofPoint> norm( nV ); //Array for the normals
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).getCrossed( v3 - v1 ) ).getNormalized();
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//--------------------------------------------------------------
void ImageProcessing::scalingMesh(){
    m_outputHeight=ofGetHeight()*1.0f;
    m_outputScale=1.0/(getHeightImage()/m_outputHeight);
    m_outputWidth= getWidthImage()*m_outputScale;
    //todo controllo sulla width
    ofVec3f vertex;
    for(unsigned int i=0; i<m_mesh.getNumVertices(); i++) {
        vertex = m_mesh.getVertex(i);
        m_mesh.setVertex(i,vertex*m_outputScale);
    }
}

//--------------------------------------------------------------
double ImageProcessing::getScaledMeshFactor(){
    m_outputHeight=ofGetHeight()*1.0f;
    m_outputScale=1.0/(getHeightImage()/m_outputHeight);
    m_outputWidth= getWidthImage()*m_outputScale;
    //todo controllo sulla width
    return m_outputScale;
}


//--------------------------------------------------------------
void ImageProcessing::translateMesh(ofVec3f coords){
    for(int i=0; i<m_mesh.getNumVertices(); i++) {
        ofVec3f vertex = m_mesh.getVertex(i);
        m_mesh.setVertex(i,vertex+coords);
    }
}

//--------------------------------------------------------------
void ImageProcessing::createImgFromFbo(ofFbo &fbo){
    m_pixels.clear();
    m_pixels.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR_ALPHA);
    fbo.readToPixels(m_pixels);
    unsigned char temp[int(ofGetWidth()*ofGetHeight()*3)];
    for (int t = 0; t < ofGetWidth()*ofGetHeight(); t++){
        temp[t*3+0] = m_pixels[t*4+0];
        temp[t*3+1] = m_pixels[t*4+1];
        temp[t*3+2] = m_pixels[t*4+2];
    }
    m_colorContour.setFromPixels(temp, ofGetWidth(), ofGetHeight());
    m_colorContour.mirror(true, false);
    
}

//--------------------------------------------------------------
void ImageProcessing::findContourImage(){
    m_temp=m_colorContour;
    m_contourFinder.findContours(m_temp,  1200, (ofGetWidth()*ofGetHeight()*0.3), 20, true);
}

//--------------------------------------------------------------
void ImageProcessing::drawContour(){
    m_contourFinder.draw(211+10, 300, m_drawingWidth, m_drawingHeight);
}

