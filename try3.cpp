#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/opencv.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace dlib;
using namespace std;

int main() {
  try {

    // Load face detection and pose estimation models.
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor pose_model;
    deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

    int frame_count = 0;
    const int frame_skip = 0; // Skip 5 frames to reduce processing load

    cv::VideoCapture cap(0); // opening OpenCV VideoCapture
    if (!cap.isOpened()) {
      cerr << "Unable to connect to camera" << endl;
      return 1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640); // Lower resolution for speed
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

    // Grab and process frames until the user closes the window.
    while (true) {
      // Grab a frame
      cv::Mat temp;
      if (!cap.read(temp)) {
        break;
      }

      // if (frame_count % frame_skip == 0) {
      // Convert from OpenCV's Mat to dlib's cv_image
      cv::Mat temp_rgb;
      cv::cvtColor(temp, temp_rgb, cv::COLOR_BGR2RGB);
      dlib::cv_image<dlib::rgb_pixel> cimg(temp_rgb);

      // Detect faces
      std::vector<rectangle> faces = detector(cimg);
      // Find the pose of each face.
      std::vector<full_object_detection> shapes;
      for (unsigned long i = 0; i < faces.size(); ++i) {
        shapes.push_back(pose_model(cimg, faces[i]));
      }

      // Draw the face landmarks using OpenCV
      for (const auto &shape : shapes) {
        for (unsigned long i = 0; i < shape.num_parts(); ++i) {
          cv::circle(temp, cv::Point(shape.part(i).x(), shape.part(i).y()), 2,
                     cv::Scalar(0, 0, 255), -1);
        }
      }
      // }

      // Display the frame with landmarks
      cv::imshow("Face Landmark Detection", temp);

      // Check for exit key
      if (cv::waitKey(1) >= 0) {
        break;
      }

      frame_count++;
    }
  } catch (serialization_error &e) {
    cout << "You need dlib's default face landmarking model file to run this "
            "example."
         << endl;
    cout << "You can get it from the following URL: " << endl;
    cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2"
         << endl;
    cout << endl << e.what() << endl;
  } catch (exception &e) {
    cout << e.what() << endl;
  }
}
