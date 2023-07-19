
#include <cstdlib>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <array>
#include <format>
#include <iostream>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <string>
#include <string_view>
#include <vector>

using namespace cv;
using namespace std;

int main() {

  const string_view pl =
      "/Users/idobbins/Downloads/musco/20230608-185535_Center-Left.mkv";

  const string_view pr =
      "/Users/idobbins/Downloads/musco/20230608-185535_Center-Right.mkv";

  string outl = "./";
  string outr = "./";

  VideoCapture vl(pl.data());
  VideoCapture vr(pr.data());

  //const int nl = vl.get(cv::CAP_PROP_FRAME_COUNT);
  // const int nr = vr.get(cv::CAP_PROP_FRAME_COUNT);

  array<Mat, 2> images_distorted{};
  array<Mat, 2> images_undistorted{};

  cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << 2686.7916000882988, 0,
                           1920, 0, 2686.7916000882988, 1080, 0, 0, 1);

  cv::Mat dist_coeff = (cv::Mat_<double>(5, 1) << -0.3615797679385818,
                        0.18157573354774362, 0, 0, -0.0532463150908359);

  Mat result{};

//  for (int i = 0; i < nl; i++) {

    vl.read(images_distorted[0]);
    undistort(images_distorted[0], images_undistorted[0], camera_matrix,
              dist_coeff);

    // outl += "frame_";
    // outl += to_string(i);
    // outl += "_l.jpg";

    // imwrite(outl, images_undistorted[0]);

    // outl = "./";

    vr.read(images_distorted[1]);
    undistort(images_distorted[1], images_undistorted[1], camera_matrix,
              dist_coeff);

    // outr += "frame_";
    // outr += to_string(i);
    // outr += "_r.jpg";

    // imwrite(outr, images_undistorted[1]);

    // outr = "./";
    Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(400);
    vector<KeyPoint> k1{};
    Mat d1{};
    detector->detectAndCompute(images_undistorted[0], noArray(), k1, d1);

    vector<KeyPoint> k2{};
    Mat d2{};
    detector->detectAndCompute(images_undistorted[1], noArray(), k2, d2);

    Ptr<DescriptorMatcher> matcher =
        DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);

    std::vector<std::vector<DMatch>> knn_matches;
    matcher->knnMatch(d1, d2, knn_matches, 2);

    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.7f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++) {
      if (knn_matches[i][0].distance <
          ratio_thresh * knn_matches[i][1].distance) {
        good_matches.push_back(knn_matches[i][0]);
      }
    }
    //-- Draw matches
    Mat img_matches;
    drawMatches(images_undistorted[0], k1, images_undistorted[1], k2, good_matches, img_matches,
                Scalar::all(-1), Scalar::all(-1), std::vector<char>(),
                DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
    string out = "./m.jpg";
    imwrite(out, img_matches);
  //}
}
