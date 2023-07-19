
#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/videoio.hpp>

#include <array>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

using namespace cv;
using namespace std;

int main() {

  //Stitcher::Mode mode = Stitcher::PANORAMA;

  const string_view pl =
      "/Users/idobbins/Downloads/musco/20230608-185535_Center-Left.mkv";

  const string_view pr =
      "/Users/idobbins/Downloads/musco/20230608-185535_Center-Right.mkv";

  string outl = "./";
  string outr = "./";

  VideoCapture vl(pl.data());
  VideoCapture vr(pr.data());

  const int nl = vl.get(cv::CAP_PROP_FRAME_COUNT);
  // const int nr = vr.get(cv::CAP_PROP_FRAME_COUNT);

  array<Mat, 2> images_distorted{};
  array<Mat, 2> images_undistorted{};

  cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << 2686.7916000882988, 0,
                           1920, 0, 2686.7916000882988, 1080, 0, 0, 1);

  cv::Mat dist_coeff = (cv::Mat_<double>(5, 1) << -0.3615797679385818,
                        0.18157573354774362, 0, 0, -0.0532463150908359);

  Mat result{};

  for (int i = 0; i < nl; i++) {

    vl.read(images_distorted[0]);
    undistort(images_distorted[0], images_undistorted[0], camera_matrix, dist_coeff);

    outl += "frame_";
    outl += to_string(i);
    outl += "_l.jpg";

    imwrite(outl, images_undistorted[0]);

    outl = "./";


    vr.read(images_distorted[1]);
    undistort(images_distorted[1], images_undistorted[1], camera_matrix, dist_coeff);

    outr += "frame_";
    outr += to_string(i);
    outr += "_r.jpg";

    imwrite(outr, images_undistorted[1]);

    outr = "./";


    //Ptr<Stitcher> stitcher = Stitcher::create(mode);
    //Stitcher::Status status = stitcher->stitch(images_undistorted, result);

    //if (status != Stitcher::OK) {
      //cout << "Can't stitch images, error code = " << int(status) << endl;
      //continue;
    //}

  }
}
