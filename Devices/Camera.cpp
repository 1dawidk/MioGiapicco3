#include <zconf.h>
#include "Camera.h"

Camera::Camera() {
    cam_h= new RaspiCam_Cv();
}

Camera::~Camera() {
    cam_h->release();
    delete cam_h;
}

void Camera::init(unsigned int resX, unsigned int resY) {
    this->resX= resX;
    this->resY= resY;

    cam_h->set(CV_CAP_PROP_FORMAT, CV_8UC1);

    cam_h->open();
    sleep(3);
}

int Camera::getImage(cv::Mat *img) {
    cam_h->grab();
    cam_h->retrieve(*img);

    return 1;
}