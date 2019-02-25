#include "ImagePusher.h"

void ImagePusher::init(string &url) {
    this->url= url;

    curl_global_init(CURL_GLOBAL_SSL);

    this->start();
}

void ImagePusher::onStart() {

}

void ImagePusher::onRun() {

}

void ImagePusher::onStop() {

}