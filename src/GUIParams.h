#ifndef __bauMapping__GUIParams__
#define __bauMapping__GUIParams__


class GUIParams{
    
public:
    
    enum type_name {
        ORIGINAL=1,
        BASIC,
        ADAPTIVE,
        CANNY,
        LAPLACE,
        SOBEL,
        CORNERHARRIS
    };
    
    enum type_value {
        POINTS=1,
        LINES,
        LINE_STRIP,
        LINE_LOOP,
        TRIANGLES,
        TRIANGLE_FAN,
        TRIANGLE_STRIP
    };
    
    
    enum type_z {
        CYLINDER=0,
        SATURATION,
        BRIGHTNESS,
        LIGHTNESS,
        ALPHA,
        NOISE
    };
    
    enum type_3d {
        TEXTURE=1,
        VERTICES,
        WIREFRAME
    };
    
    enum type_mask {
        MASKOFF=0,
        MASKINSIDE,
        MASKOUTSIDE
    };
    
    //particles GUI
    struct particlesGUI_p {
        int Total;
        int Size;
        int Red;
        int Green;
        int Blue;
        int Alpha;
        float FreqFlickering;
        int AlphaFboTrails;
        bool Texture;
        int MatrixTexture;
    };
    
    //starting GUI
    struct GUI_p {
        bool Image;
        bool Model;
    };
    
    //GUI 2D
    struct GUI2D_p {
        string          ImageFileName;
        int             ScaleFactor;
    };
    
    //GUI 3D
    struct GUI3D_p {
        string          ModelFileName;
        int             DrawingStyle;
    };
    
    //Original image GUI
    struct originalGUI_p {
        
    };
    
    //Basic threshold GUI
    struct basicGUI_p {
        bool            Range;
        float           RangeMax;
        float           RangeMin;
        int             ThreshHold;
        int             Invert;
        int             GrayValue;
        bool            Brightness;
        float           BrightnessValue;
        float           ContrastValue;
        bool            Background;
        bool            Erode;
        bool            Dilate;
    };
    
    
    //Adaptive Threshold GUI
    struct adaptiveGUI_p {
        int             BlockSize;
        int             Offset;
        bool            Invert;
        bool            Gauss;
        bool            Brightness;
        float           BrightnessValue;
        float           ContrastValue;
        bool            Range;
        float           RangeMax;
        float           RangeMin;
        bool            Erode;
        bool            Dilate;
    };
    
    
    //Canny GUI
    struct cannyGUI_p {
        float           Threshold1;
        float           Threshold2;
        int             Aperture;
        bool            Invert;
        bool            Dilate;
        bool            Stretch;
    };
    
    
    //Laplace GUI
    struct laplaceGUI_p {
        int             Aperture;
        bool            Range;
        float           RangeMax;
        float           RangeMin;
        bool            Invert;
        bool            BlurGaussian;
        int             BlurGaussianValue;
        bool            Erode;
        bool            Dilate;
        bool            Stretch;
    };
    
    
    //Sobel GUI
    struct sobelGUI_p {
        int             XOrder;
        int             YOrder;
        int             Aperture;
        bool            Range;
        float           RangeMax;
        float           RangeMin;
        bool            Invert;
        bool            BlurGaussian;
        int             BlurGaussianValue;
        bool            Erode;
        bool            Dilate;
        bool            Stretch;
    };
    
    
    //Corner Harris GUI
    struct cornerHarrisGUI_p {
        int             BlockSize;
        double          K;
        int             Aperture;
        bool            Invert;
        bool            BlurGaussian;
        int             BlurGaussianValue;
        bool            Erode;
        bool            Dilate;
    };
    
    
    //Algorithms GUI
    struct algorithmsGUI_p {
    };
    
    //Morph GUI
    struct morphGUI_p {
        float NoiseX;
        float NoiseY;
        float NoiseZ;
        float Speed;
    };
    
    //Triangulation GUI
    struct triangulationGUI_p {
        int TrianglesMax;
        bool Wireframe;
    };
    
    //Lines Connection GUI
    struct linesConnectionGUI_p {
        bool Enable;
        int Total;
        float ConnectionDistance;
        float LineWidth;
    };
    
    //Z GUI
    struct ZGUI_p {
        int Index;
        int Threshold;
    };
    
    //EasyCam GUI
    struct easycamGUI_p {
        bool Enable;
        bool MouseInput;
        int Distance;
        bool Orbit;
        int RadiusOrbit;
        int SpeedOrbitX;
        int SpeedOrbitY;
        float Drag;
    };
    
    //Shader GUI
    struct shaderGUI_p {
        bool            Reload;
        bool            Enable;
    };
    
    //Light GUI
    struct lightGUI_p {
        bool EnableSpot;
        int SpotRed;
        int SpotGreen;
        int SpotBlue;
        int SpotCutOff;
        int SpotConcentration;
        bool EnableDirectional;
        int DirectionalRed;
        int DirectionalGreen;
        int DirectionalBlue;
        int DirectionalX;
        int DirectionalY;
        int DirectionalZ;
    };
    
    //Boids GUI
    struct boidsGUI_p {
        float   LifeTime;
        float   Speed;
        float   Align;
        float   DistSeparation;
        float   GravityForce;
        int     BoundMode;
    };
    
    //OpenSteer GUI
    struct openSteerGUI_p {
        int   simulation;
    };
    
    //InputImage GUI
    struct inputImageGUI_p {
        bool    Shoot;
        bool    ActivateCamera;
        int     Threshold;
        int     Mask;
    };
    
    //RecordVideo GUI
    struct recordVideoGUI_p {
        bool    Start;
        bool    Stop;
    };
    
};
#endif
