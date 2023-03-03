#include <opencv2/opencv.hpp>

int main()
{
    // Load the Haar Cascade classifiers
    cv::CascadeClassifier face_cascade("/Users/henryzelenak/opencv/install/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
    cv::CascadeClassifier eye_cascade("/Users/henryzelenak/opencv/install/share/opencv4/haarcascades/haarcascade_eye.xml");

    // Load an image
    cv::Mat image = cv::imread("eyes2.jpg");

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // For each face, detect eyes
    for (size_t i = 0; i < faces.size(); i++)
    {
        cv::Mat face_roi = gray(faces[i]);
        std::vector<cv::Rect> eyes;
        eye_cascade.detectMultiScale(face_roi, eyes, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Draw rectangles around the detected features
        cv::rectangle(image, faces[i], cv::Scalar(255, 0, 0), 2);
        for (size_t j = 0; j < eyes.size(); j++)
        {
            cv::Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2);
            int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            cv::circle(image, eye_center, radius, cv::Scalar(0, 0, 255), 2);

            /** Draw rectangles around the eyes
            cv::Rect eye_rect(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y, eyes[j].width, eyes[j].height);
            cv::rectangle(image, eye_rect, cv::Scalar(0, 255, 0), 2); */
        }
    }

    // Display the result
    cv::imshow("Facial feature detection", image);
    cv::waitKey(0);

    return 0;
}