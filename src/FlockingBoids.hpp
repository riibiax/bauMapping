#ifndef __bauMapping__FlockingBoids__
#define __bauMapping__FlockingBoids__


#include "ofMain.h"
#include "Flock3d.h"
#include "GUIParams.h"

class FlockingBoids{
    
public:
    FlockingBoids();
    virtual ~FlockingBoids();
    
    void setup();
    void setup(GUIParams::boidsGUI_p params);
    void update(int total, bool BUpdateSetting, GUIParams::boidsGUI_p params);
    void draw();
    int size() {return flock3D.size();};
    
    Flock3d flock3D;
    
private:
    
    void setBoidsAttractors();
    void updateSettings(bool BUpdateSetting, GUIParams::boidsGUI_p params);
    void updateEmmiterBoids(int total);
    void deleteBoids();
    

    
};
#endif
