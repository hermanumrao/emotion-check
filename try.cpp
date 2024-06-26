#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>

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

    // Load input image
    array2d<rgb_pixel> img;
    load_image(img,
               "/home/herman/workspace/emotion-check/2024-06-26-141925.jpg");

    // Detect faces in the image
    std::vector<rectangle> dets = detector(img);
    cout << "Number of faces detected: " << dets.size() << endl;

    // Create a window to display the image with landmarks
    image_window win;

    // Iterate through each detected face
    for (size_t i = 0; i < dets.size(); ++i) {
      // Detect landmarks for this face
      full_object_detection shape = sp(img, dets[i]);

      // Draw landmarks on the image
      for (size_t j = 0; j < shape.num_parts(); ++j) {
        int x = shape.part(j).x();
        int y = shape.part(j).y();
        // cv::circle(img, cv::Point(x, y), 2, cv::Scalar(0, 255, 0), -1); //
        // Green color Draw a circle at the specified point (x, y) with a radius
        // of 2 pixels
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
      // Wait for a key press to proceed to the next face
      cin.get();
    }

    // Save the image with landmarks
    save_png(img, "../exp9_image.png");

  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
