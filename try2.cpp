#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <thread>

using namespace dlib;
using namespace std;

int main() {
  try {
    // Load face detection and shape prediction models
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;
    deserialize("/home/herman/workspace/emotion-check/"
                "shape_predictor_68_face_landmarks.dat") >>
        sp;

    // Open the webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
      cerr << "Unable to connect to the camera" << endl;
      return 1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // Lower resolution for speed
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

    // Create a window to display the image with landmarks
    image_window win;

    int frameCount = 0;
    while (true) {
      cv::Mat temp;
      cap >> temp;
      if (temp.empty()) {
        cerr << "Captured an empty frame" << endl;
        break;
      }

      // Skip every 2nd frame
      frameCount++;
      if (frameCount % 2 != 0) {
        cv::imshow("Webcam", temp);
        if (cv::waitKey(10) >= 0)
          break;
        continue;
      }

      // Convert the frame to dlib's image format
      array2d<bgr_pixel> img;
      assign_image(img, cv_image<bgr_pixel>(temp));

      // Detect faces in the frame
      std::vector<rectangle> dets = detector(img);
      cout << "Number of faces detected: " << dets.size() << endl;

      // Iterate through each detected face
      for (size_t i = 0; i < dets.size(); ++i) {
        // Detect landmarks for this face
        full_object_detection shape = sp(img, dets[i]);

        // Draw landmarks on the image
        for (size_t j = 0; j < shape.num_parts(); ++j) {
          int x = shape.part(j).x();
          int y = shape.part(j).y();
          draw_solid_circle(img, point(x, y), 2, rgb_pixel(0, 255, 0));
        }

        // Display image with landmarks
        win.clear_overlay();
        win.set_image(img);
        win.add_overlay(render_face_detections(shape));

        cout << "Number of landmarks: " << shape.num_parts() << endl;
        // Print landmark points
        for (size_t j = 0; j < shape.num_parts(); ++j) {
          cout << "Landmark #" << j << ": " << shape.part(j) << endl;
        }
      }

      // Display the frame
      cv::imshow("Webcam", temp);

      // Wait for 'q' key press to exit
      if (cv::waitKey(10) >= 0)
        break;
    }

  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
