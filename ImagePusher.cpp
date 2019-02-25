#include "ImagePusher.h"

void ImagePusher::init(const string &url) {
    this->url= url;

    curl_global_init(CURL_GLOBAL_SSL);

    this->start();
}

void ImagePusher::onStart() {
    camera= new Camera;
    camera->init(512, 512);

    curlHandle= curl_easy_init();

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
}

void ImagePusher::onRun() {
    cv::Mat imgBuff;

    camera->getImage(imgBuff);

    //TODO: Push image
    //curl_easy_perform(curlHandle);

    //TODO: Wait for push finished

    Thread::pause(2000);
}

void ImagePusher::onStop() {
    delete camera;
}