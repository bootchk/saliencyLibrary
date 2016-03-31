

#ifndef GRADIENTER_H_
#define GRADIENTER_H_

#include <opencv2/core/core.hpp>


namespace sal {


/*
 * \brief Class to compute gradient: magnitude and direction.

 Valid calling sequence:  compute ... getGradMagnitude
 */
class Gradienter {
public:
	explicit Gradienter(const float& sig = 1.20f);
	virtual ~Gradienter();

	/// Perform Canny edge detection on the given image
	void compute(const cv::Mat1f& src);

	/// Smooth the input image and store the result in smoothedImg
	void smoothImage(const cv::Mat1f& src, cv::Mat1f& smoothedImg);


	/// Get sigma value
	float getSigma() const {
		return sigma;
	}

	/// Get the Gaussian window size
	int getWindowSize() const {
		return windowSize;
	}

	cv::Mat1f getGradMagnitudes() const {
		return gradMagnitudes;
	}

	cv::Mat1f getGradOrientations() const {
		return gradOrientations;
	}

	/// Set the sigma value (should be greater than 0)
	void setSigma(const float& value) {
		if (value > 0) {
			sigma = value;
		}
	}


private:
	/// Create a 1-D Gaussian kernel
	void createGaussianKernel(cv::Mat1f& kernel);

	void calculateXAndYDerivatives(const cv::Mat1f& smoothedImg, cv::Mat1f& deltaX, cv::Mat1f& deltaY);
	void calculateGradientDirections(const cv::Mat1f& deltaX, const cv::Mat1f& deltaY);
	void calculateGradientMagnitudes(const cv::Mat1f& deltaX, const cv::Mat1f& deltaY);

	/// Calculate the angle of the vector represented by x and y
	float calculateVectorAngle(const float& x, const float& y);


	/// Standard deviation for the Gaussian smoothing filter
	float sigma;

	/// The Gaussian window size based on sigma
	int windowSize;

	cv::Mat1f gradMagnitudes;
	cv::Mat1f gradOrientations;	// sic direction
};

} // namespace

#endif // GRADIENTER_H_
