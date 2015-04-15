#include "cli_raytrace.h"

namespace CLI_Raytrace {

	// The color of the background
	Pixel background = {0, 0, 0};

	// Where we're viewing from
	fvec eye;

	// What direction we're looking at
	fvec gaze_dir;

	// Which way is up
	fvec up_dir;

	// Distance to the screen
	fvec screen_dist;

	// Bottom left and top right corners of the screen.
	// These are
	fvec screen_bot_left;
	fvec screen_bot_right;

	std::vector<Surface> surfaces;

	std::vector<InfinityLight> lights;

}
