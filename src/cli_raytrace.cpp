#include "cli_raytrace.h"
#include "cli_global.h"
#include <cmath>

using namespace CLI_Global;

namespace CLI_Raytrace {

	// The color of the background
	Pixel background = {0, 0, 0};

	// Should the raytracer use an orthographic perspective or camera perspective
	bool orthographic = true;

	// Where we're viewing from
	fvec viewpoint(3);

	// What direction we're looking at
	frowvec gaze_dir(3);

	// Which way is up
	frowvec up_dir(3);

	// Distance to the screen
	float screen_dist;

	// Bottom left and top right corners of the screen.
	// These are
	fvec screen_bot_left(2);
	fvec screen_top_right(2);

	// How many times should we recursively calculate specular color?
	int max_recursion_depth = 4;

	std::vector<Surface *> surfaces;

	std::vector<InfinityLight> lights;


	Pixel shade(fvec origin, fvec dir) {
		static int recurse_depth = 0;
		++recurse_depth;

		Pixel out;

		if (recurse_depth > max_recursion_depth) {
			--recurse_depth;
			return {0,0,0};
		}

		// Find the closest object that the ray intersects
		HitRecord closest;
		closest.hit = false;
		for (size_t i = 0; i < surfaces.size(); ++i) {
			HitRecord next = surfaces[i]->intersects(origin, dir);
			if (next.hit && next.t > 0 && (!closest.hit || next.t < closest.t))
				closest = next;
		}

		if (!closest.hit) {
			out = background;
		}
		else {
			out = closest.surface->getAmbientColor();

			// Calculate the reflective lighting component
			// TODO - Add phong lighting
			Pixel reflect = closest.surface->getReflectiveColor();
			if (!isZero(reflect)) {
				for (size_t i = 0; i < lights.size(); ++i) {
					// Since the lights are all at infinity, to get the ray from the
					// point of intersection to the light, just reverse the direction
					// of the light.
					fvec l = -lights[i].direction;

					// The cosine of the angle between the light and the normal
					float cos_theta = dot(l, closest.normal);
					cos_theta = (cos_theta < 0) ? 0 : cos_theta;

					out = out + (reflect * lights[i].color * cos_theta);
				}
			}

			// Calculate the specular component
			Pixel spec = closest.surface->getSpecularColor();
			if (!isZero(spec)) {
				fvec reflection = dir - 2 * dot (dir, closest.normal) * closest.normal;
				reflection = reflection / norm(reflection, 2);

				// Calculate the specular reflection from the point of contact.
				out = out + (spec * shade(origin + closest.t * dir, reflection));
			}
		}
		clamp(out);

		--recurse_depth;
		return out;
	}


	Box::Box(fvec lower_left_back, fvec upper_right_top, Pixel amb, Pixel ref, Pixel spec): Surface(amb, ref, spec),
			llb(lower_left_back), urt(upper_right_top){

		// Make sure that the lower left corner is actually the lower left corner.
		float tmp;
		for (int i = 0; i < 3 ; ++i) {
			if (urt(i) < llb(i)) {
				tmp = urt(i);
				urt(i) = llb(i);
				llb(i) = tmp;
			}
		}
	}

	HitRecord Box::intersects(fvec origin, fvec dir) {
		HitRecord record;
		record.hit = false;
		fvec normal = zeros<fvec>(3);
		float tmin, tmax, txmin, txmax, tymin, tymax, tzmin, tzmax;

		// Note: This code works because we assume that divide-by-0 results in either
		// infinity or negative infinity, as defined by the Annex F standard.

		txmin = (llb(0) - origin(0)) / dir(0);
		txmax = (urt(0) - origin(0)) / dir(0);

		normal(0) = -1;

		// No hit.
		if (txmin == txmax)
			return record;

		if (txmax < txmin) {
			std::swap(txmin, txmax);
			normal(0) = 1;
		}

		tmin = txmin;
		tmax = txmax;

		tymin = (llb(1) - origin(1)) / dir(1);
		tymax = (urt(1) - origin(1)) / dir(1);

		if (tymax < tymin)
			std::swap(tymin, tymax);

		// No intersection.
		if (tymin > tmax || tymax < tmin)
			return record;

		if (tymin > tmin) {
			tmin = tymin;

			normal(0) = 0;

			// If we bounced off the upper y plane
			if (dir(1) < 0) {
				normal(1) = 1;
			}
			else {
				normal(1) = -1;
			}
		}
		if (tymax < tmax)
			tmax = tymax;

		tzmin = (llb(2) - origin(2)) / dir(2);
		tzmax = (urt(2) - origin(2)) / dir(2);

		if (tzmax < tzmin)
			std::swap(tzmin, tzmax);

		// No intersection.
		if (tzmin > tmax || tzmax < tmin)
			return record;

		if (tzmin > tmin) {
			tmin = tzmin;

			normal(0) = 0;
			normal(1) = 0;

			// If we bounced off the upper z plane
			if (dir(2) < 0) {
				normal(2) = 1;
			}
			else {
				normal(2) = -1;
			}
		}
		if (tzmax < tmax)
			tmax = tzmax;

		// The ray intersects the box.
		record.hit = true;
		record.t = tmin;
		record.surface = this;
		record.normal = normal;

		return record;

	}

	Sphere::Sphere(fvec cent, float rad, Pixel amb, Pixel ref, Pixel spec):
			Surface(amb, ref, spec), center(cent), radius(rad) {}

	HitRecord Sphere::intersects(fvec origin, fvec dir) {
		HitRecord record;
		record.hit = false;

		fvec e_c = origin - center;
		float discrim = pow(dot(dir, e_c), 2) - dot(dir, dir) * (dot(e_c, e_c) - pow(radius, 2));

		// No hit.
		if (discrim < 0)
			return record;

		record.hit = true;
		record.surface = this;
		record.t = (dot(-dir, e_c) - sqrt(discrim)) / dot(dir, dir);

		fvec intersection = origin + record.t * dir;
		record.normal = (intersection - center) / radius;

		return record;
	}

	Triangle::Triangle(fvec first, fvec second, fvec third, Pixel amb, Pixel ref, Pixel spec):
			Surface(amb, ref, spec), a(first), b(second), c(third) {}

	HitRecord Triangle::intersects(fvec point, fvec dir) {
		HitRecord record;
		record.hit = false;

		// TODO - This can be optimized.

		// Using Cramer's rule to solve the system of equations that represent
		// the intersection of the ray with the plane the triangle is on.

		fmat A(3,3);

		A.col(0) = a - b;
		A.col(1) = a - c;
		A.col(2) = dir;

		float det_A = det(A);

		fvec a_p = a - point;

		fmat B = A;
		B.col(0) = a_p;

		float beta = det(B) / det_A;

		if (beta < 0 || beta > 1)
			// No hit.
			return record;

		B = A;
		B.col(1) = a_p;

		float gamma = det(B) / det_A;

		if (gamma < 0 || gamma > 1 - beta )
			// No hit.
			return record;

		B = A;
		B.col(2) = a_p;

		record.t = det(B) / det_A;
		record.normal = cross(c-a, b-a);
		record.normal = record.normal / norm(record.normal, 2);

		// The triangle has two outward facing normals
		if (dot(record.normal, dir) > 0)
			record.normal = -record.normal;

		record.surface = this;
		record.hit = true;

		return record;
	}

}
