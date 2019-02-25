#ifndef MIOGIAPICCO_IMAGEPUSHER_H
#define MIOGIAPICCO_IMAGEPUSHER_H

#include "dkulpaclibs/misc/Thread.h"
#include "dkulpaclibs/hw/Camera.h"
#include "string"
#include "curl/curl.h"

using namespace std;

class ImagePusher : public Thread {
public:
    void init(string &url);
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    string url;
    Camera *camera;
};


#endif //MIOGIAPICCO_IMAGEPUSHER_H
