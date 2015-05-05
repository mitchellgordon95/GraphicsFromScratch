#ifndef CLI_PIPELINE_H
#define CLI_PIPELINE_H
#include <armadillo>
#include <stack>

using namespace arma;

namespace CLI_Pipeline {

extern std::vector<fmat> transform_stack;

void draw_line(float x0, float y0, float x1, float y1);
int near_far_clip(float, float, float *, float *, float *, float *, float *,
		float *);

void updateOrth(float left, float right, float bottom, float top, float near,
		float far);

extern fmat orth;

extern fmat perspect;

extern fmat camera;
}

#endif
