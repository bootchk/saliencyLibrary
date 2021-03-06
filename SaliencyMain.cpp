/*
 * SaliencyMain.cpp
 *
 */
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "src/SaliencyDetector.h"

using namespace std;

int main(int argc, char *argv[]) {
	cv::Mat1f img = cv::imread("data/croppedBike.jpeg", CV_LOAD_IMAGE_GRAYSCALE);

	if (img.empty()) {
		cout << "No image loaded. Exiting.\n";
		return (EXIT_FAILURE);
	}

	sal::ImageSaliencyDetector detector(img);
	detector.setSamplingPercentage(0.10f);

	cout << "Computing...\n";
	detector.compute();

	cout << "Post-processing...\n";
	detector.performPostProcessing();

	cv::imwrite("SaliencyTestOutput.jpg", detector.getSaliencyMap());


	return 0;
}



