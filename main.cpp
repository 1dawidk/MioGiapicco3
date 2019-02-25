#include <iostream>

#include "UI.h"
#include "ImagePusher.h"

int main() {
    UI *ui= new UI;
    ImagePusher *imagePusher= new ImagePusher;

    imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");
    ui->init();

    while(ui->isRunning());

    return 0;
}