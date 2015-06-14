#include "opencv2/opencv.hpp"
#include <iostream>
#include <thread>         // std::thread

using namespace std;
using namespace cv;

int capture(int device){
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

	for (;;){

		Mat frame;
		vcap >> frame;
		video.write(frame);
		imshow(pchar, frame);
		char c = (char)waitKey(33);
		if (c == 27) break;
	}
	return 0;
}

int main(){
	capture(0);
}