#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SevenSegmentDisplay.h"
#include "SunController.h"
#include "NJU6450Driver.h"

int main() {
    UI *ui= new UI;

    ImagePusher *imagePusher= new ImagePusher;
    NJU6450Driver *display;
    SunController *sunController;

    //Create objects
    int disp_dp[]= {0, 1};
    int disp_sp[]= {0, 1, 2, 3, 4, 5, 6};
    tempDisplay= new SevenSegmentDisplay(disp_dp, disp_sp, 2);
    disp_dp[0]= 0; disp_dp[1]= 1;
    disp_sp[0]= 0; disp_sp[1]= 1; disp_sp[2]= 2; disp_sp[3]=3; disp_sp[4]= 4; disp_sp[5]= 5; disp_sp[6]= 6;
    humDisplay= new SevenSegmentDisplay(disp_dp, disp_sp, 2);
    sunController= new SunController;

    //Init / Start
    imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");
    tempDisplay->start();
    humDisplay->start();
    sunController->start();


    ui->init();



    while(ui->isRunning());

    return 0;
}