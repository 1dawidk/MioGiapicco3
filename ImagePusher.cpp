#include <sys/stat.h>
#include "ImagePusher.h"

ImagePusher::ImagePusher(const string &url) {
    this->url= url;
}

void ImagePusher::onStart() {
    curl_global_init(CURL_GLOBAL_SSL);

    camera= new Camera;
    camera->init(512, 512);
    triggerCnt=0;
}

void ImagePusher::onRun() {

    if(triggerCnt==0) {
        cv::Mat imgBuff;

        cout << "Take a photo" << endl;

        camera->getImage(&imgBuff);
        cv::imwrite("./imgs/lastshot.jpg", imgBuff);

        cout << "Done" << endl;


        /*CURL *curlHandle = curl_easy_init();
        curl_httppost *post;
        curl_httppost *lastpost;


        struct curl_slist *headerlist = NULL;
        headerlist = curl_slist_append(headerlist, "Content-Type: multipart/form-data");

        curl_formadd(&post, &lastpost,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, "./imgs/lastshot.jpg",
                     CURLFORM_END);

        curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curlHandle, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1L);

        curl_easy_perform(curlHandle);

        triggerCnt= IMAGEPUSHER_TRIGGER_INITVALUE;*/
    } else {
        triggerCnt--;
    }

    Thread::pause(60000);
}

void ImagePusher::onStop() {
    delete camera;
}