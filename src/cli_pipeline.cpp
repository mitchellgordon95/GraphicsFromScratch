#include "cli_pipeline.h"
#include "cli_global.h"
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <armadillo>
#include <stack>

using namespace arma;
using namespace CLI_Global;

std::vector<fmat> init_transform_stack() {
	std::vector<fmat> stack;
	fmat ident = eye<fmat>(4, 4);
	stack.push_back(ident);
	return stack;
}

namespace CLI_Pipeline {

std::vector<fmat> transform_stack = init_transform_stack();

bool perspectiveProjection = false;

fmat orth = eye<fmat>(4, 4);

fmat perspect = eye<fmat>(4, 4);

fmat camera = eye<fmat>(4, 4);

void updateOrth(float left, float right, float bottom, float top, float near,
		float far) {

	orth = eye<fmat>(4,4);

	orth(0,0) = 2 / (right - left);
	orth(1,1) = 2 / (top - bottom);
	orth(2,2) = 2 / (near - far);
	orth(0,3) = - (right + left) / (right - left);
	orth(1,3) = - (top + bottom) / (top - bottom);
	orth(2,3) = - (near + far) / (near - far);

	if (diagnostics) {
        std::cout << "Updated orthographic project matrix: l=" << left;
        std::cout << ",r=" << right << ",b=" << bottom << ",t=" << top;
        std::cout << ",n=" << near << ",f=" << far << std::endl;
		std::cout << "Orthographic matrix: " << std::endl << orth << std::endl;
	}
}

/* the clipping window */
static float xmin = 0.0;
static float xmax = 1.0;
static float ymin = 0.0;
static float ymax = 1.0;

static void set_clip_window(float, float, float, float);
static int clip_line(float *, float *, float *, float *);

/******************************************************************************
 Draw a white line.

 Entry:
 x0,y0 - first endpoint of line
 x1,y1 - second line endpoint
 ******************************************************************************/

void draw_line(float x0, float y0, float x1, float y1) {
	GLint viewport[4];
	int i;
	float x, y;
	float dx, dy;
	float xinc, yinc;
	float length = 0.;
	int result;
	int width, height;
	Pixel white = { 1, 1, 1 };

	/* set the clipping window */

	glGetIntegerv(GL_VIEWPORT, viewport);
	width = abs(viewport[2] - viewport[0]);
	height = abs(viewport[3] - viewport[1]);

	set_clip_window(0.0, 0.0, width - 0.51, height - 0.51);

	/* clip the line in 2D */
	result = clip_line(&x0, &y0, &x1, &y1);

	/* return if line is entirely outside the clip window */
	if (result == 0)
		return;

	/* incremental line drawing */

	dx = x1 - x0;
	dy = y1 - y0;

	/* determine whether horizontal or vertical change is larger */

	if (fabs(dx) > fabs(dy))
		length = fabs(dx);
	else
		length = fabs(dy);

	/* special case to avoid dividing by zero */

	if (length == 0) {
		setPixel(x0, y0, white);
		return;
	}

	xinc = dx / length;
	yinc = dy / length;

	x = x0;
	y = y0;

	/* write "length" number of pixels along the line */

	for (i = 0; i <= length; i++) {

		if (x < displayImage.width && y < displayImage.height)
			setPixel(y, x, white);

		x += xinc;
		y += yinc;
	}
	glFlush();
}

/******************************************************************************
 Specify a clipping window.

 Entry:
 x0,y0 - lower left boundaries of clipping window
 x1,y1 - upper right boundaries
 ******************************************************************************/

static void set_clip_window(float x0, float y0, float x1, float y1) {
	xmin = x0;
	ymin = y0;

	xmax = x1;
	ymax = y1;
}

/******************************************************************************
 Given a point P outside the window and the rise and run of a line, return
 the intersection of line with window that is nearest P.

 Entry:
 dx,dy - run and rise of line
 x,y   - the given point P

 Exit:
 ix,iy - intersection point
 return 1 if there was a valid intersection, 0 if not
 ******************************************************************************/

static int clip_helper(float dx, float dy, float x, float y, float *ix,
		float *iy) {
	/* if line not vertical, check against left and right edges of window */

	if (dx != 0) {

		/* check against left edge */
		*iy = dy / dx * (xmin - x) + y;
		if (xmin >= x && *iy >= ymin && *iy <= ymax) {
			*ix = xmin;
			return (1);
		}

		/* check against right edge */
		*iy = dy / dx * (xmax - x) + y;
		if (xmax <= x && *iy >= ymin && *iy <= ymax) {
			*ix = xmax;
			return (1);
		}
	}

	/* if line not horizontal, check against top and bottom edges of window */

	if (dy != 0) {

		/* check against bottom edge */
		*ix = dx / dy * (ymin - y) + x;
		if (ymin >= y && *ix >= xmin && *ix <= xmax) {
			*iy = ymin;
			return (1);
		}

		/* check against top edge */
		*ix = dx / dy * (ymax - y) + x;
		if (ymax <= y && *ix >= xmin && *ix <= xmax) {
			*iy = ymax;
			return (1);
		}
	}

	/* if we get here, we found no intersection */
	return (0);
}

/******************************************************************************
 Clip a line segment to a pre-specified window.

 Entry:
 x0,y0 - first line segment endpoint
 x1,y1 - second endpoint

 Exit:
 x0,y0,x1,y1 - clipped endpoint positions
 returns 1 if segment is at least partially in window,
 returns 0 if segment is entirely outside window
 ******************************************************************************/

static int clip_line(float *x0, float *y0, float *x1, float *y1) {
	int count;
	float dx, dy;
	float xx0 = *x0;
	float yy0 = *y0;
	float xx1 = *x1;
	float yy1 = *y1;

	int code04 = (xx0 < xmin) ? 1 : 0;
	int code03 = (xx0 > xmax) ? 1 : 0;
	int code02 = (yy0 < ymin) ? 1 : 0;
	int code01 = (yy0 > ymax) ? 1 : 0;

	int code14 = (xx1 < xmin) ? 1 : 0;
	int code13 = (xx1 > xmax) ? 1 : 0;
	int code12 = (yy1 < ymin) ? 1 : 0;
	int code11 = (yy1 > ymax) ? 1 : 0;

	int sum0 = code01 + code02 + code03 + code04;
	int sum1 = code11 + code12 + code13 + code14;

	/* completely inside window? */
	if (sum0 == 0 && sum1 == 0)
		return (1);

	/* check for trivial invisibility (both endpoints on wrong side of */
	/* a single side of the window) */

	if ((code01 && code11) || (code02 && code12) || (code03 && code13)
			|| (code04 && code14)) {
		return (0);
	}

	/* compute run and rise */
	dx = xx1 - xx0;
	dy = yy1 - yy0;

	/* case: only x0,y0 is inside window */
	if (sum0 == 0) {
		//int dummy =
		clip_helper(dx, dy, xx1, yy1, &xx1, &yy1);
		*x0 = xx0;
		*y0 = yy0;
		*x1 = xx1;
		*y1 = yy1;
		return (1);
	}

	/* case: only x1,y1 is inside window */
	if (sum1 == 0) {
		// int dummy =
		clip_helper(dx, dy, xx0, yy0, &xx0, &yy0);
		*x0 = xx0;
		*y0 = yy0;
		*x1 = xx1;
		*y1 = yy1;
		return (1);
	}

	/* neither endpoint is inside the window */

	count = 0;
	count += clip_helper(dx, dy, xx0, yy0, &xx0, &yy0);
	count += clip_helper(dx, dy, xx1, yy1, &xx1, &yy1);

	*x0 = xx0;
	*y0 = yy0;
	*x1 = xx1;
	*y1 = yy1;

	if (count)
		return (1);
	else
		return (0);
}

/******************************************************************************
 Clip a line segment to front and back clipping planes.  These clip planes
 are along the z-axis.  If your objects are on the negative z portion of
 the axis, be sure to specify negative values for "near" and "far".

 Entry:
 near,far - clip planes along z-axis
 x0,y0,z0 - first line segment endpoint
 x1,y1,z1 - second endpoint

 Exit:
 x0,y0,z0,x1,y1,z1 - clipped endpoint positions
 returns 1 if segment is at least partially in window,
 returns 0 if segment is entirely outside window
 ******************************************************************************/

int near_far_clip(float near, float far, float *x0, float *y0, float *z0,
		float *x1, float *y1, float *z1) {
	float temp;
	float fract;
	float xx0 = *x0;
	float yy0 = *y0;
	float zz0 = *z0;
	float xx1 = *x1;
	float yy1 = *y1;
	float zz1 = *z1;
	int code00, code01, code10, code11;

	/* make sure near < far */

	if (near > far) {
		temp = far;
		far = near;
		near = temp;
	}

	/* figure out which endpoints are outside the clipping volume */

	code00 = (zz0 < near) ? 1 : 0;
	code01 = (zz0 > far) ? 1 : 0;
	code10 = (zz1 < near) ? 1 : 0;
	code11 = (zz1 > far) ? 1 : 0;

	/* return without clipping if all endpoints are inside clip volume */

	if (code00 + code01 + code10 + code11 == 0)
		return (1); /* signals inside volume */

	/* if both endpoints are entirely out of clip volume, exit and signal this */

	if ((code00 && code10) || (code01 && code11))
		return (0); /* signals outside volume */

	/* clip to near plane if necessary */

	if (code00) {
		fract = (near - zz0) / (zz1 - zz0);
		xx0 = xx0 + fract * (xx1 - xx0);
		yy0 = yy0 + fract * (yy1 - yy0);
		zz0 = near;
	} else if (code10) {
		fract = (near - zz1) / (zz0 - zz1);
		xx1 = xx1 + fract * (xx0 - xx1);
		yy1 = yy1 + fract * (yy0 - yy1);
		zz1 = near;
	}

	/* clip to far plane if necessary */

	if (code01) {
		fract = (far - zz0) / (zz1 - zz0);
		xx0 = xx0 + fract * (xx1 - xx0);
		yy0 = yy0 + fract * (yy1 - yy0);
		zz0 = far;
	} else if (code11) {
		fract = (far - zz1) / (zz0 - zz1);
		xx1 = xx1 + fract * (xx0 - xx1);
		yy1 = yy1 + fract * (yy0 - yy1);
		zz1 = far;
	}

	/* copy the clipped endpoints */

	*x0 = xx0;
	*y0 = yy0;
	*z0 = zz0;
	*x1 = xx1;
	*y1 = yy1;
	*z1 = zz1;

	/* signal that we're inside the clip volume */
	return (1);
}
}
