#include "opencv2/opencv.hpp"
#include <iostream>
#include <thread>         // std::thread
#include <conio.h>

using namespace std;
using namespace cv;

int capture(int device, int *termino){
	VideoCapture vcap(device);
	if (!vcap.isOpened()){
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	int frame_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	std::string s = std::to_string(device) + ".avi";

	char const *pchar = s.c_str();  //use char const* as target type

	VideoWriter video(pchar, CV_FOURCC('M', 'J', 'P', 'G'), 25, Size(frame_width, frame_height), true);

	while(1){

		Mat frame;
		vcap >> frame;
		video.write(frame);
		imshow(pchar, frame);
		char c = (char)waitKey(1);
		if (*termino == 1)
			break;
		//if (c == 27) break;
	}
	return 0;
}

int terminar(int *termino){
	char i;
	while (1){
		printf("[Haga clic aquí y presione ESC para terminar]...\n");
		i = _getch();
		if (i == 27){
			printf("Terminando");
			*termino = 1;
			return 0;
		}
	}
	return 0;
}

int main(){

	int termino = 0;

	std::thread first(capture,0,&termino);
	std::thread second(terminar, &termino);
	
	first.join();
	second.join();

	return 0;
}