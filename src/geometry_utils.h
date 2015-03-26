#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H
#include <armadillo>
#include <stack>
#define ROW 4
#define COL 4

// NOTE: 95% of this code is Bobby B's code from the 90's.
// TODO - Fix it.

using namespace arma;

namespace CLI_Geometry {

	extern std::vector<fmat> transform_stack;

	void gtLookAt( float fx, float fy, float fz, float atx, float aty,
			   float atz, float upx, float upy, float upz);
	void gtVertex3f(float x, float y, float z);

	void draw_line(float, float, float, float);
	int near_far_clip(float, float, float *, float *, float *, float *,
					  float *, float *);

    typedef struct                  /* structure definitions */
    {
       float  mat[ROW][COL];
    }  matrix_unit;

    typedef struct
    {
       float i;
       float j;
       float k;
    } Vector;

    typedef struct
    {
       float x;
       float y;
       float z;
       float r;
       float g;
       float b;
    } Vertex_unit;

    typedef struct
    {
      float mat41[ROW];
    } matrix41;

    extern matrix_unit Identity;

    extern float Near, Far;

    extern int perspflag;

    extern matrix_unit *stack[50];    /* array of pointers to act as a stack */

    extern int top;                   /* points to top of the stack */

    extern int width, height;         /* height and width of frame buffer */

    extern matrix_unit orth;       /* global ortho and perspective matrices */
                                   /* to be used in Vertex3f */
    extern matrix_unit perspect;

}


#endif
