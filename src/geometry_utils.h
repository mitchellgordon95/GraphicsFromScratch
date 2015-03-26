#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H
#include <armadillo>
#include <stack>

using namespace arma;

namespace CLI_Geometry {

	extern std::stack<fmat> transform_stack;


	void gtLookAt( float fx, float fy, float fz, float atx, float aty,
			   float atz, float upx, float upy, float upz);
	void gtVertex3f(float x, float y, float z);

	void draw_line(float, float, float, float);
	int near_far_clip(float, float, float *, float *, float *, float *,
					  float *, float *);
}


#endif
