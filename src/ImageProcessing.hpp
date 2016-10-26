#ifndef __bauMapping__ImageProcessing__
#define __bauMapping__ImageProcessing__


#include "ofxOpenCv.h"
#include "GUIParams.h"
#include "ofxTriangle.h"


//--------------------------------------------------------------
class ImageProcessing: private ofImage{
    
public:
    
    ImageProcessing();
    virtual ~ImageProcessing();
    
    void setup();
    void dragEvent(ofDragInfo dragInfo);
    
    void loadImage(string imageFileName);
    void setupImages();
    void setPrimitiveMesh(int primitive);
    void setupImageOutput();
    void setupImageOutput32B();
    void setScale(int scaleFactor);
    void setNormals(ofMesh &mesh);
    void allocateImages();
    
    void updateOriginal(GUIParams::originalGUI_p params);
    void updateBasic(GUIParams::basicGUI_p params);
    void updateAdaptive(GUIParams::adaptiveGUI_p params);
    void updateCanny(GUIParams::cannyGUI_p params);
    void updateSobel(GUIParams::sobelGUI_p params);
    void updateLaplace(GUIParams::laplaceGUI_p params);
    void updateCornerHarris(GUIParams::cornerHarrisGUI_p params);

    
    vector<ofVec3f> getScannedPoints();
    int getWidthImage() {return m_width;};
    int getHeightImage(){return m_height;};
    int getScaledWidthImage() {return m_scaledWidth;};
    int getScaledHeightImage(){return m_scaledHeight;};
    ofVboMesh   getVboMesh(){return m_vboMesh;};
    ofMesh      getMesh(){return m_mesh;};
    
    void saveImage(bool image32B);
    
    
    void drawStartingImage();
    void drawImageProcessing();
    void drawImageProcessing32B();
    void drawBlackRectangle(float w, float h);
    
    
    void scanColorImage(ofColor color);
    
    void scanBrightnessImage();
    
    void scanLightnessImage(float intensityThreshold);

    void morphTo2D();
    
    void setTriangulation(GUIParams::triangulationGUI_p params);
    void setZSaturation(int saturation);
    void setZLightness(float intensityThreshold);
    void setZBrightness(float brightnessThreshold);
    void setZAlpha(float alphaThreshold);
    void setZCylinder(float radius);
    void setZRandom(int frame);
    
    void  setZIndex(int zIndex, int zThreshold);
    float getZIndex(ofColor pixel, float vertexX);
    float getZCylinder(float vertexX);
    float getZPixel(float value);
    float getZRandom();

    
    void scalingMesh();
    void translateMesh(ofVec3f coords);
    
    double getScaledMeshFactor();
    
    void createImgFromFbo(ofFbo &fbo);
    void findContourImage();
    void drawContour();
    
    
private:
    
    int         m_counter;
    int         m_z, m_zThreshold;
    int         m_width, m_height;
    int         m_scaledWidth, m_scaledHeight;
    int         m_scaleFactor;
    int         m_drawingWidth, m_drawingHeight;
    int         m_triangleMax;
    
    float       m_outputWidth, m_outputHeight;
    double      m_outputScale;
    
    
    ofPixels                    m_pixels;
    ofImage                     m_image;
    ofImage                     m_img;
    ofImage                     m_result;
    ofxCvColorImage             m_colorImg;
    ofxCvColorImage             m_tempColor;
    ofxCvColorImage             m_colorResult;
    ofxCvColorImage             m_colorContour;
    ofxCvGrayscaleImage         m_grayImage;
    ofxCvGrayscaleImage         m_grayBg;
    ofxCvGrayscaleImage         m_outputImage;
    ofxCvGrayscaleImage         m_temp;
    ofxCvFloatImage             m_outputImage32B;
    ofxCvContourFinder          m_contourFinder;
    
    
    ofRectangle     m_rect;
    
    ofMesh          m_mesh;
    ofxTriangle     m_triangle;
    ofVboMesh       m_vboMesh;

    
};

#endif
