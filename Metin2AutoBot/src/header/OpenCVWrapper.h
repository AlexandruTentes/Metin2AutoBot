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
		Mat& get_color_map_mat()			{ return color_map_mat; };
		void update();

		virtual ~OpenCVWrapper();
	private:
		void init();
		Mat color_detection(Mat & mat);

	private:
		Mat mat;
		Mat map_mat;
		Mat color_map_mat;

		Global& global = Global::get_instance();
	};
}