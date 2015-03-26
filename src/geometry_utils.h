#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H
#include <armadillo>
#include <stack>

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

	const int ROW = 4;
	const int COL = 4;

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

    static float Near, Far;

    float w;

    int perspflag=0;

    static matrix_unit I = {
       { {1., 0., 0., 0.},
         {0., 1., 0., 0.},
         {0., 0., 1., 0.},
         {0., 0., 0., 1.}  },
    };

    matrix_unit *stack[50];    /* array of pointers to act as a stack */

    int top = 0;                   /* points to top of the stack */

    int width, height;         /* height and width of frame buffer */

    static matrix_unit orth;       /* global ortho and perspective matrices */
                                   /* to be used in Vertex3f */
    static matrix_unit perspect;

}


#endif
