#pragma once

#include "../../Global.h"

#include <opencv2/opencv.hpp>

using namespace cv;

namespace mt2
{
	class OpenCVWrapper
	{
	public:
		SINGLETONIZE_INIT(OpenCVWrapper)

		Mat& get_mat()						{ return mat; };
		Mat& get_map_mat()					{ return map_mat; };

		virtual ~OpenCVWrapper();
	private:
		void init();

	private:
		Mat mat;
		Mat map_mat;
	};
}