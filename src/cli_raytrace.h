#ifndef CLI_RAYTRACE_H
#define CLI_RAYTRACE_H
#include "cli_global.h"
#include <vector>
#include <armadillo>

using namespace arma;
using namespace CLI_Global;

namespace CLI_Raytrace {

	// The color of the background
	extern Pixel background;

	// Where we're viewing from
	extern fvec eye;

	// What direction we're looking at
	extern fvec gaze_dir;

	// Which way is up
	extern fvec up_dir;

	// Distance to the screen
	extern fvec screen_dist;

	// Bottom left and top right corners of the screen.
	// These are
	extern fvec screen_bot_left;
	extern fvec screen_bot_right;

	// Information about an intersection between a surface and a ray.
	struct HitRecord {
		// The point of contact on the surface.
		fvec contact_pt;
		// The normal of the surface at the point of contact.
		fvec normal;
		// The distance along the ray that the surface was intersected at.
		float t;
	};

	class Surface {
	public:
		virtual ~Surface();

		// Does this surface intersect with a ray, given it's direction and point of origin?
		// If it does, return a hit record. If not, null.
		virtual HitRecord * intersects(fvec eye, fvec dir) = 0;

		virtual Pixel getAmbientColor() { return {0, 0, 0}; }
		virtual Pixel getReflectiveColor() { return {0, 0, 0}; }
		virtual Pixel getSpecularColor() { return {0, 0, 0}; }
	};

	extern std::vector<Surface> surfaces;

	struct InfinityLight {
		Pixel color;
		fvec direction;
	};

	extern std::vector<InfinityLight> lights;

}

#endif
