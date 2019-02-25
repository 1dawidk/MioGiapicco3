#include <iostream>

#include "UI.h"
#include "ImagePusher.h"

int main() {
    UI *ui= new UI;
    ImagePusher *imagePusher= new ImagePusher;


    ui->init();
    imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");



    return 0;
}