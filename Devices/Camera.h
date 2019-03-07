#ifndef MIOGIAPICCO_CAMERA_H
#define MIOGIAPICCO_CAMERA_H

#include <raspicam/raspicam_cv.h>

using namespace raspicam;

class Camera {
public:
    Camera();
    ~Camera();
    void init(unsigned int resX, unsigned int resY);

    int getImage(cv::Mat *img);
private:
    unsigned int resY;
    unsigned int resX;

    RaspiCam_Cv *cam_h;
};


#endif //MIOGIAPICCO_CAMERA_H
