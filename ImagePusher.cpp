#include <sys/stat.h>
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

    struct curl_slist *headerlist=NULL;
    headerlist = curl_slist_append( headerlist, "Content-Type: image/jpeg");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
}

void ImagePusher::onRun() {
    cv::Mat imgBuff;

    camera->getImage(&imgBuff);
    cv::imwrite("./imgs/lastshot.jpg", imgBuff);

    FILE *fd= fopen("./imgs/lastshot.jpg", "rb");
    struct stat file_info;
    fstat(fileno(fd), &file_info);

    curl_easy_setopt(curlHandle, CURLOPT_READDATA, fd);
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDSIZE, (curl_off_t)file_info.st_size);

    curl_easy_perform(curlHandle);

    Thread::pause(2000);
}

void ImagePusher::onStop() {
    delete camera;
}