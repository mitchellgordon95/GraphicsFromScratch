#ifndef CLI_RAYTRACE_H
#define CLI_RAYTRACE_H
#include "cli_global.h"
#include <vector>
#include <armadillo>

using namespace arma;
using namespace CLI_Global;

namespace CLI_Raytrace {

	// Given a ray in 3D space, calculate the appropriate color given the environment settings.
	Pixel shade(fvec origin, fvec dir);

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
	struct HitRecord;

	class Surface {
	private:
		Pixel ambient, reflective, specular;
	public:
		Surface(Pixel amb, Pixel ref, Pixel spec): ambient(amb), reflective(ref), specular(spec){}
		virtual ~Surface() {};

		// Does this surface intersect with a ray, given it's direction and point of origin?
		// If it does, return a hit record. If not, null.
		virtual HitRecord intersects(fvec eye, fvec dir) = 0;

		virtual Pixel getAmbientColor() { return ambient; }
		virtual Pixel getReflectiveColor() { return reflective; }
		virtual Pixel getSpecularColor() { return specular; }
	};

	struct HitRecord {
		// Did the ray hit the surface?
		bool hit;
		// The normal of the surface at the point of contact.
		fvec normal;
		// The distance along the ray that the surface was intersected at.
		float t;
		// A pointer to the surface that was intersected
		Surface * surface;
	};

	extern std::vector<Surface *> surfaces;

	struct InfinityLight {
		Pixel color;
		fvec direction;
	};

	extern std::vector<InfinityLight> lights;

	class Box : public Surface {
	private:
		fvec llb, urt;
	public:
		Box(fvec lower_left_back, fvec upper_right_top, Pixel amb, Pixel ref, Pixel spec);
		HitRecord intersects(fvec eye, fvec dir);
	};

	class Triangle: public Surface {
	private:
		fvec a, b, c;
	public:
		Triangle(fvec a, fvec b, fvec c, Pixel amb, Pixel ref, Pixel spec);
		HitRecord intersects(fvec eye, fvec dir);
	};

	class Sphere: public Surface {
	private:
		fvec center;
		float radius;
	public:
		Sphere(fvec cent, float rad, Pixel amb, Pixel ref, Pixel spec);
		HitRecord intersects(fvec eye, fvec dir);
	};
}

#endif
