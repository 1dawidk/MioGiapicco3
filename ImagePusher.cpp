#include <sys/stat.h>
#include "ImagePusher.h"

ImagePusher::ImagePusher(const string &url) {
    this->url= url;
}

void ImagePusher::onStart() {
    curl_global_init(CURL_GLOBAL_SSL);

    camera= new Camera;
    camera->init(2048, 1536);
    lastSentHour=120;
}

void ImagePusher::onRun() {
    int m= Clock::GetDayMinutes();
    int h= m/60;

    if(lastSentHour!=h && (h%6==0)) {
        cv::Mat imgBuff;

        // Take a photo
        camera->getImage(&imgBuff);
        cv::imwrite("./imgs/lastshot.jpg", imgBuff);
        Thread::pause(500);


        // Create curl handle
        CURL *curlHandle = curl_easy_init();
        curl_httppost *post=NULL;
        curl_httppost *lastpost=NULL;


        // Create http header
        struct curl_slist *headerlist = NULL;
        headerlist = curl_slist_append(headerlist, "Content-Type: multipart/form-data");

        // Prepare post form
        curl_formadd(&post, &lastpost,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, "./imgs/lastshot.jpg",
                     CURLFORM_END);

        // Set curl opts
        curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curlHandle, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 0);

        // Perform curl
        curl_easy_perform(curlHandle);
        curl_easy_cleanup(curlHandle);

        cout << "Image uploaded" << endl;

        lastSentHour=h;
    }

    Thread::pause(120000);
}

void ImagePusher::onStop() {
    delete camera;
}