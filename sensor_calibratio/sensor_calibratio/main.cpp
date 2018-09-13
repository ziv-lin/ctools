#include "import_lib.h"
#include "coverage_ratio.h"
#include <fstream>
#include <iostream>
using namespace cv;
using namespace std;
//template <typename T>

string pt_file_chess = string(R"(G:\Dropbox\Dropbox\IROS2018_1\point\point2D_chess.txt)");
string pt_file_screen = string(R"(G:\Dropbox\Dropbox\IROS2018_1\point\point2D_screen.txt)");


vector<Point2f> load_point_from_txt(const string  & file_name)
{
    ifstream ifs;
    vector<Point2f> pt_vec(10000);
    int pt_count = 0;
    float p_x, p_y;
    ifs.open(file_name.c_str());
    while (!ifs.eof())
    {
        ifs >> p_x;
        ifs >> p_y;
        pt_vec[pt_count] = cv::Point2f(p_x, p_y);
        pt_count++;
    }
    ifs.close();
    pt_vec.resize(pt_count);
    return pt_vec;
}

void main()
{
    string pt_file_name[2];
    vector<Point2f> pt_vec[2];
    Mat img_draw[2];
    cv::Size image_size = cv::Size(1280, 1024);
    pt_file_name[0] = pt_file_chess;
    pt_file_name[1] = pt_file_screen;

    for (unsigned int i = 0; i < 2; i++)
    {
        pt_vec[i] = load_point_from_txt(pt_file_name[i].c_str());
        cout << pt_vec[i].size() << endl;
        img_draw[i] = Mat(image_size.height, image_size.width, CV_8UC(3)) * 0;
        cv_tools::draw_pt_on_img(img_draw[i], pt_vec[i], cv::Scalar(0, 255, 255));
        auto convex_hull_pt = cv_tools::points_convex_hull(pt_vec[i]);
        cv_tools::coverage_ratio(convex_hull_pt, image_size);
        cv_tools::draw_convex_hull(img_draw[i], convex_hull_pt, cv::Scalar(255, 255, 0));

        Mat dentisity = cv_tools::draw_dentisity(pt_vec[i], image_size, 100, 1);
        Mat mat_mean, mat_std;
        meanStdDev(dentisity, mat_mean, mat_std);
        cout << mat_mean / pt_vec[i].size() << endl;
        cout << mat_std / pt_vec[i].size() << endl;
        imshow(pt_file_name[i].c_str(), img_draw[i]);
        string dentisity_name = pt_file_name[i] + string("_detisity");
        
        //dentisity = dentisity/ (image_size.area() * mat_mean.at<float>(0) )* 255;
        cv::normalize(dentisity, dentisity, 255, 0, NORM_MINMAX);
        dentisity.convertTo(dentisity, CV_8U);
        //cv::medianBlur(dentisity, dentisity, 149);
        imshow(dentisity_name.c_str(), dentisity.clone());
        imwrite((pt_file_name[i] + string(".png")).c_str(), img_draw[i].clone());
        imwrite((dentisity_name + string(".png")).c_str(), dentisity.clone());
    }

    cv::waitKey(0);
    //cv_tools::evaluate();
}