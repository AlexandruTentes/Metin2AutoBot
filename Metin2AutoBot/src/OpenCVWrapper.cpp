#include "header/OpenCVWrapper.h"

void mt2::OpenCVWrapper::init()
{
	
}

Mat mt2::OpenCVWrapper::color_detection(Mat & mat)
{
	Mat rez_dark_metin;
	Mat rez_light_metin;
	Mat rez_player;
	
	Mat rez_metin, rez;

	auto lower1 = Scalar(global.lower_map_metin_b1, global.lower_map_metin_g1, global.lower_map_metin_r1);
	auto upper1 = Scalar(global.upper_map_metin_b1, global.upper_map_metin_g1, global.upper_map_metin_r1);
	auto lower2 = Scalar(global.lower_map_metin_b2, global.lower_map_metin_g2, global.lower_map_metin_r2);
	auto upper2 = Scalar(global.upper_map_metin_b2, global.upper_map_metin_g2, global.upper_map_metin_r2);
	auto lower3 = Scalar(global.lower_map_player_b, global.lower_map_player_g, global.lower_map_player_r);
	auto upper3 = Scalar(global.upper_map_player_b, global.upper_map_player_g, global.upper_map_player_r);

	inRange(mat, lower1, upper1, rez_dark_metin);
	inRange(mat, lower2, upper2, rez_light_metin);

	int x = mat.size().width * 0.33;
	int y = mat.size().height * 0.33;
	Rect roi(x, y, mat.size().width * 0.33, mat.size().height * 0.33);
	Mat small_mat = mat(roi);
	Mat normal_player;
	inRange(small_mat, lower3, upper3, rez_player);
	resize(rez_player, normal_player, Size(), (float)mat.size().width / small_mat.size().width, (float)mat.size().height / small_mat.size().height);
	
	bitwise_or(rez_dark_metin, rez_light_metin, rez_metin);
	bitwise_or(rez_metin, normal_player, rez);

	return rez;
}

void mt2::OpenCVWrapper::update()
{
	if (mat.empty())
		return;

	Mat wide_map_mat;
	resize(map_mat, wide_map_mat, Size(), 2, 2, INTER_CUBIC);
	color_map_mat = color_detection(wide_map_mat);
	
}

mt2::OpenCVWrapper::~OpenCVWrapper()
{
}
