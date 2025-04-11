#include <rapp.h>

#define RMATH_SHAPES_DEFINED
#define rmCircle rapp_circleF 
#define rmRect rapp_rectF
#define rmCube rapp_cube

#define RMATH_BOOL_DEFINED
#define rmBool rapp_bool
#define rmMat4 rapp_mat4

#define RMATH_VECTORS_DEFINED
#define rmVec2 rapp_pointF
#define rmVec3 rapp_point3D
#define rmVec4 rapp_point4D

#include "deps/rmath.h"

rapp_bool rapp_circleCollidePoint(rapp_circle c, rapp_point p) { return rapp_circleCollideRect(c, (rapp_rect) {p.x, p.y, 1, 1}); }
rapp_bool rapp_circleCollidePointF(rapp_circleF c, rapp_pointF p) { return rapp_circleCollideRectF(c, (rapp_rectF) {p.x, p.y, 1, 1}); }

rapp_bool rapp_circleCollideRectF(rapp_circleF c, rapp_rectF r) { return rmCircleCollideRect(c, r); }
rapp_bool rapp_circleCollideRect(rapp_circle c, rapp_rect r) { return rapp_circleCollideRectF(RAPP_CIRCLEF(c.x, c.y, c.d), RAPP_RECTF(r.x, r.y, r.w, r.h)); }

rapp_bool rapp_circleCollideF(rapp_circleF cir, rapp_circleF cir2) { return rmCircleCollide(cir, cir2); }

rapp_bool rapp_circleCollide(rapp_circle cir, rapp_circle cir2) { return rapp_circleCollideF(RAPP_CIRCLEF(cir.x, cir.y, cir.d), RAPP_CIRCLEF(cir2.x, cir2.y, cir2.d)); }

rapp_bool rapp_rectCollidePoint(rapp_rect r, rapp_point p){ return rapp_rectCollidePointF(RAPP_RECTF(r.x, r.y, r.w, r.h), RAPP_POINTF(p.x, p.y)); }
rapp_bool rapp_rectCollide(rapp_rect r, rapp_rect r2){ return rapp_rectCollideF(RAPP_RECTF(r.x, r.y, r.w, r.h), RAPP_RECTF(r2.x, r2.y, r2.w, r2.h));  }
rapp_bool rapp_pointCollide(rapp_point p, rapp_point p2){ return rapp_pointCollideF(RAPP_POINTF(p.x, p.y), RAPP_POINTF(p2.x, p2.y)); }

rapp_bool rapp_rectCollidePointF(rapp_rectF r, rapp_pointF p){ return rmRectCollideVec2(r, p); }
rapp_bool rapp_rectCollideF(rapp_rectF r, rapp_rectF r2){ return rmRectCollide(r, r2); }
rapp_bool rapp_pointCollideF(rapp_pointF p, rapp_pointF p2){ return rmVec2Collide((rmVec2){p.x, p.y}, p2); }

rapp_bool rapp_cubeCollideVec3(rapp_cube cube, rapp_point3D p) { return rmCubeCollide(cube, (rmCube){p.x, p.y, p.z, 1, 1, 1}); }
rapp_bool rapp_cubeCollide(rapp_cube r, rapp_cube r2) { return rmCubeCollide(r, r2); }

rapp_mat4 rapp_scale(rapp_mat4 matrix, float x, float y, float z) {
    return rmScale(matrix.m, x, y, z);
}

rapp_point rapp_pointAdd(rapp_point v1, rapp_point v2) {
    rmVec2 output = rmVec2Add(RAPP_POINTF(v1.x, v2.y), RAPP_POINTF(v1.x, v2.y));
    return RAPP_POINT(output.x, output.y);
}
rapp_point rapp_pointSubrtact(rapp_point v1, rapp_point v2) { 
    rmVec2 output = rmVec2Subrtact(RAPP_POINTF(v1.x, v2.y), RAPP_POINTF(v1.x, v2.y));
    return RAPP_POINT(output.x, output.y);
}
rapp_point rapp_pointMultiply(rapp_point v1, rapp_point v2) { 
    rmVec2 output = rmVec2Multiply(RAPP_POINTF(v1.x, v2.y), RAPP_POINTF(v1.x, v2.y));
    return RAPP_POINT(output.x, output.y);
}

rapp_point rapp_pointDivide(rapp_point v1, rapp_point v2) {
    rmVec2 output = rmVec2Divide(RAPP_POINTF(v1.x, v2.y), RAPP_POINTF(v1.x, v2.y));
    return RAPP_POINT(output.x, output.y);
}

rapp_pointF rapp_pointFAdd(rapp_pointF v1, rapp_pointF v2) { return rmVec2Add(v1, v2); }
rapp_point3D rapp_point3DAdd(rapp_point3D v1, rapp_point3D v2) { return rmVec3Add(v1, v2); }
rapp_point4D rapp_point4DAdd(rapp_point4D v1, rapp_point4D v2) {  return rmVec4Add(v1, v2); }

rapp_pointF rapp_pointFSubrtact(rapp_pointF v1, rapp_pointF v2) { return rmVec2Subtract(v1, v2); }
rapp_point3D rapp_point3DSubtract(rapp_point3D v1, rapp_point3D v2) { return rm3VecSubtract(v1, v2); }
rapp_point4D rapp_point4DSubtract(rapp_point4D v1, rapp_point4D v2) { return rmVec4Subtract(v1, v2); }

rapp_pointF rapp_pointFMultiply(rapp_pointF v1, rapp_pointF v2) { return rmVec2Multiply(v1, v2); }

rapp_point3D rapp_point3DMultiply(rapp_point3D v1, rapp_point3D v2) { return rmVec3Multiply(v1, v2); }
rapp_point4D rapp_point4DMultiply(rapp_point4D v1, rapp_point4D v2) { return rmVec4Multiply(v1, v2); }

rapp_pointF rapp_pointFDivide(rapp_pointF v1, rapp_pointF v2) { return rmVec2Divide(v1, v2); }

rapp_point3D rapp_point3DDivide(rapp_point3D v1, rapp_point3D v2) { return rmVec3Divide(v1, v2); }

rapp_point4D rapp_point4DDivide(rapp_point4D v1, rapp_point4D v2) { return rmVec4Divide(v1, v2); }

rapp_point rapp_pointMultiplyMat4(rapp_point vec, rapp_mat4 matrix) {
    rmVec2 vector = rmVec2MultiplyMat4((rmVec2){vec.x, vec.y}, matrix); 
    return RAPP_POINT(vector.x, vector.y);
}


rapp_pointF rapp_pointFMultiplyMat4(rapp_pointF vec, rapp_mat4 matrix) { return rmVec2MultiplyMat4(vec, matrix);  }

rapp_point3D rapp_point3DMultiplyMat4(rapp_point3D vec, rapp_mat4 matrix) { return rmVec3MultiplyMat4(vec, matrix); } 

rapp_point4D rapp_point4DMultiplyMat4(rapp_point4D vec, rapp_mat4 matrix) { return rmVec4MultiplyMat4(vec, matrix); } 

rapp_point3D rapp_point4ToVec3(rapp_point4D v) { return rmVec4ToVec3(v);  }


