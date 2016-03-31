#include <cstdlib>
#include <iostream>
#include <cassert>
#include "Gradienter.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace sal {

Gradienter::Gradienter(const float& sig) {
	if (sig > 0) {
		this->sigma = sig;
	} else {
		this->sigma = 1.20; // Default
	}

	windowSize = static_cast<int> (1 + (2 * ceil(2.5 * sigma)));

}


Gradienter::~Gradienter() { }


void Gradienter::compute(const cv::Mat1f& src) {
	assert(!src.empty() && src.cols >= 3 && src.rows >= 3);

	cv::Mat1f smoothedImg;
	cv::Mat1f deltaX, deltaY;

	smoothImage(src, smoothedImg);
	calculateXAndYDerivatives(src, deltaX, deltaY);


	calculateGradientDirections(deltaX, deltaY);
	calculateGradientMagnitudes(deltaX, deltaY);
}

void Gradienter::smoothImage(const cv::Mat1f& src, cv::Mat1f& smoothedImg) {
	assert(!src.empty() && src.cols >= 3 && src.rows >= 3);

	if (!smoothedImg.empty()) {
			std::cout << "Gradienter WARNING: Expected an empty matrix for [smoothedImg]\n";
			std::cout << "\t... may have unexpected behavior!\n";
	}
	for ( int i = 1; i < this->windowSize; i = i + 2 ) {
		cv::GaussianBlur( src, smoothedImg, cv::Size( i, i ), 0, 0 );
    }

}




void Gradienter::calculateXAndYDerivatives(
		const cv::Mat1f& inImage,
		cv::Mat1f& deltaX,
		cv::Mat1f& deltaY) {
	deltaX.create(inImage.rows, inImage.cols);
	deltaY.create(inImage.rows, inImage.cols);

	// Adjusted to handle pixels at borders
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Sobel( inImage, deltaX, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
}

// Direction of gradient, in radians specified counteclockwise from the positive x-axis
void Gradienter::calculateGradientDirections(const cv::Mat1f& deltaX, const cv::Mat1f& deltaY) {
	assert(deltaX.size == deltaY.size);
	gradOrientations.create(deltaX.rows, deltaX.cols);

	for (int r = 0; r < deltaX.rows; r++) {
		for (int c = 0; c < deltaY.cols; c++) {
			float dx = deltaX(r, c);
			float dy = -deltaY(r, c);

			gradOrientations(r, c) = calculateVectorAngle(dx, dy);

		}
	}
}


void Gradienter::calculateGradientMagnitudes(const cv::Mat1f& deltaX, const cv::Mat1f& deltaY) {
	assert(deltaX.size == deltaY.size);

	gradMagnitudes.create(deltaX.rows, deltaX.cols);

	for (int r = 0; r < deltaX.rows; r++) {
		for (int c = 0; c < deltaX.cols; c++) {
			float sqX = deltaX(r, c) * deltaX(r, c);
			float sqY = deltaY(r, c) * deltaY(r, c);
			gradMagnitudes(r, c) = sqrt(sqX + sqY);
		}
	}
}


float Gradienter::calculateVectorAngle(const float& x, const float& y) {
	float xu, yu, angle;

	xu = fabs(x);
	yu = fabs(y);

	if ((xu == 0) && (yu == 0)) {
		return (0.f);
	}

	angle = atan(yu / xu);

	if (x >= 0) {
		if (y >= 0) {
			return (angle);
		} else {
			return (2 * M_PI - angle);
		}

	} else {
		if (y >= 0) {
			return (M_PI - angle);
		} else {
			return (M_PI + angle);
		}
	}
}







} /* namespace sal */
