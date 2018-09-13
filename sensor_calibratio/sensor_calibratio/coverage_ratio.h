#pragma once
#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>

namespace cv_tools
{
    //using namespace cv;
    using namespace std;

    template <typename T>
    vector<cv::Point_<T>> generate_random_pt(int pt_number, cv::Size image_size)
    {
        cv::RNG rng = cv::RNG(cv::getTickCount());
        vector<cv::Point_<T>> pt_vec(pt_number);
        for (int i = 0; i < pt_number; i++)
        {

            T pt_x = rng.uniform(0, image_size.width);
            T pt_y = rng.uniform(0, image_size.height);

            pt_vec[i] = cv::Point_<T>(pt_x, pt_y);
            //cout << pt_vec[i] << endl;

        }
        return pt_vec;
    }

    template <typename T>
    Mat draw_pt_on_img(cv::Mat & img, const vector<T> pt_vec, cv::Scalar pt_color = cv::Scalar::all(255))
    {
        int radius = std::ceil(img.cols*1/320);
        for (auto pt : pt_vec)
        {
            cv::circle(img, pt, radius, pt_color, -1, CV_AA);
        }
        return img;
    }

    template <typename T>
    vector<T> points_convex_hull(const vector<T> pt_vec)
    {
        unsigned int i = 0;
        vector<int> hull_vec;
        vector<T>   convex_hull_pt_vec;
        cv::convexHull(std::vector<Point2f>(pt_vec.begin(), pt_vec.end()), hull_vec, 1); // OpenCV interface only accept std::vector<Point2f>
        convex_hull_pt_vec.resize(hull_vec.size());
        for (i = 0; i < hull_vec.size(); i++)
        {
            convex_hull_pt_vec[i] = pt_vec[hull_vec[i]];
        }
        return convex_hull_pt_vec;
    }

    template <typename T>
    Mat draw_convex_hull(cv::Mat & img, const vector<T> convex_hull_pt , cv::Scalar line_color = cv::Scalar::all(255))
    {
        unsigned int i = 0;
        int line_size = std::ceil(img.cols * 1 / 640);
        for (i = 0; i < convex_hull_pt.size(); i++)
        {
            cv::line(img, convex_hull_pt[i], convex_hull_pt[(i + 1) % convex_hull_pt.size()], line_color, line_size, CV_AA);
        }
        return img;
    }

    template<typename T>
    Mat draw_pt_on_img(cv::Mat & img, const vector<vector<T>> pt_vec_vec)
    {
        vector<T> pt_vec;
        for (auto _pt_vec : pt_vec_vec)
        {
            pt_vec.reserve(_pt_vec.size() + pt_vec.size());
            pt_vec.insert(pt_vec.end(), _pt_vec.begin(), _pt_vec.end());
        }
        return draw_pt_on_img(img, pt_vec);
    }

    template<typename T>
    float coverage_ratio(const vector<T> convexhull_pt_vec, cv::Size image_size)
    {
        float convexhull_area = contourArea(std::vector<Point2f>(convexhull_pt_vec.begin(), convexhull_pt_vec.end() ) ); // OpenCV interface only accept std::vector<Point2f>
        float image_area = image_size.area(); // width X height
        cout << "======" << endl;
        cout << "Convexhull area = " << convexhull_area << endl;
        cout << "Image area =      " << image_area << endl;
        cout << "Coverage ratio=   " << convexhull_area / image_area << endl;
        cout << "======" << endl;
        return convexhull_area / image_area;
    }

    void evaluate()
    {
        Size img_size = cv::Size(640, 480);
        printf("Hello, this is %s\r\n", __FILE__);
        auto pt_vec = cv_tools::generate_random_pt<double>(100, img_size);
        auto convex_hull_pt = cv_tools::points_convex_hull(pt_vec);

        Mat img = Mat::zeros(img_size.height, img_size.width, CV_8U);
        cv_tools::draw_pt_on_img(img, pt_vec);
        cv_tools::draw_convex_hull(img, convex_hull_pt);
        cv_tools::coverage_ratio(convex_hull_pt, img_size);
        imshow("image", img);
        cv::waitKey(0);
    }

    template <typename T>
    Mat draw_dentisity(vector<T> pt_vec, cv::Size image_size, int slidin_windows = 3 , int down_sample = 10)
    {
        
        Mat img = Mat(int(image_size.height/down_sample),int( image_size.width / down_sample), CV_32F)*0;
        //Mat img_init_bias = init_weight_mat(img.clone(), slidin_windows, down_sample);

        cout << "image_size = " << img.size() << endl;
        for (auto pt : pt_vec)
        {
            float avail_size_x = std::min((int)(pt.x + slidin_windows), img.cols) - std::max((int)(pt.x - slidin_windows),0);
            float avail_size_y = std::min((int)(pt.y + slidin_windows), img.rows) - std::max((int)(pt.y - slidin_windows), 0);
            float score = slidin_windows * slidin_windows / avail_size_x / avail_size_y;
            //T pt = pt_vec[pt_idx];
#pragma omp parallel for 
            for (int pt_x = pt.x - slidin_windows; pt_x < (int)(pt.x + slidin_windows); pt_x+=  down_sample)
            {
                if (pt_x < 0 || pt_x / down_sample >= img.cols)
                    continue;
                for (int pt_y = pt.y - slidin_windows; pt_y <  (int)(pt.y + slidin_windows); pt_y+=  down_sample)
                {
                    if (pt_y < 0 || pt_y / down_sample >= img.rows)
                    {
                        continue;
                    }
                    Point pt_temp = Point(pt_x / down_sample, pt_y / down_sample);
                    //cout << pt_temp << endl;
                    //img.at<float>(pt_temp) = img.at<float>(pt_temp) + score;// img_init_bias.at<float>(pt_temp);
                    img.at<float>(pt_temp) = img.at<float>(pt_temp) + score;// img_init_bias.at<float>(pt_temp);
                }
            }
        }
        //cv::normalize(img, img, 255, 0, NORM_MINMAX);
        //img.convertTo(img, CV_8U);
        return img;
    }

}