#include "trace_module.h"
#include "cli_raytrace.h"

CLI_Trace::~CLI_Trace()
{
}

using namespace CLI_Global;
using namespace CLI_Raytrace;
using namespace arma;

void CLI_Trace::execute(std::vector<char *> &params)
{
	if(orthographic) {
		// Shoot a ray straight through each pixel, with all rays parallel to the z axis.
		fvec point = zeros<fvec>(3);
		fvec dir = zeros<fvec>(3);
		dir(2) = -1;

		for (int row = 0; row < displayImage.height; ++row)
			for (int col = 0; col < displayImage.width; ++col){
				point(0) = col;
				point(1) = row;
				setPixel(row, col, shade(point, dir));
			}
	}
	else {
		// Construct a camera space, , which is constructed from
		// the gaze direction and up vector.
		gaze_dir = gaze_dir / norm(gaze_dir, 2);
		frowvec right_dir = cross(gaze_dir, up_dir);
		right_dir = right_dir / norm(right_dir, 2);
		up_dir = cross(right_dir, gaze_dir);

		// Construct a rotation from camera space into normal xyz space.
		fmat camera_to_xyz(3,3);
		camera_to_xyz.submat(0, 0, 0, 2) = right_dir;
		camera_to_xyz.submat(1, 0, 1, 2) = up_dir;
		camera_to_xyz.submat(2, 0, 2, 2) = gaze_dir;

		// The direction of each ray.
		fvec ray_dir(3);

		float deltaX = (screen_top_right(0) - screen_bot_left(0)) / displayImage.width;
		float deltaY = (screen_top_right(1) - screen_bot_left(1)) / displayImage.height;

		for (int row = 0; row < displayImage.height; ++row)
		for (int col = 0; col < displayImage.width; ++col){
			// First calculate the ray in camera-space
			ray_dir(0) = screen_bot_left(0) + (col + 0.5) * deltaX;
			ray_dir(1) = screen_bot_left(1) + (row + 0.5) * deltaY;
			ray_dir(2) = screen_dist;

			// Translate the ray into xyz space.
			ray_dir = camera_to_xyz * ray_dir;

			// Normalize the ray
			ray_dir = ray_dir / norm(ray_dir, 2);

			if(diagnostics)
				std::cout << "ray direction:" << std::endl << ray_dir;

			setPixel(row, col, shade(viewpoint, ray_dir));
		}
	}

	glutPostRedisplay();
}
