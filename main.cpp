#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/opencv.h>      // Include dlib's OpenCV conversion functions
#include <opencv2/opencv.hpp> // Include OpenCV

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
    cv::VideoCapture cap(0); // 0 is the default ID for the built-in webcam
    if (!cap.isOpened()) {
      cerr << "Unable to connect to the camera" << endl;
      return 1;
    }

    // Create a window to display the image with landmarks
    image_window win;

    while (true) {
      cv::Mat temp;
      cap >> temp; // Capture a frame
      if (temp.empty()) {
        cerr << "Captured an empty frame" << endl;
        break;
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
          // Draw a circle at the specified point (x, y) with a radius of 2
          // pixels
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
      if (cv::waitKey(30) >= 0)
        break;
    }

  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
