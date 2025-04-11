#include <rapp.h>

#define RMATH_SHAPES_DEFINED
#define rmCircle rapp_circleF 
#define rmRect rapp_rectF
#define rmCube rapp_cube

#define RMATH_BOOL_DEFINED
#define rmBool rapp_bool


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

rapp_bool rapp_rectCollidePointF(rapp_rectF r, rapp_pointF p){ return rmRectCollideVec2(r, (rmVec2){p.x, p.y}); }
rapp_bool rapp_rectCollideF(rapp_rectF r, rapp_rectF r2){ return rmRectCollide(r, r2); }
rapp_bool rapp_pointCollideF(rapp_pointF p, rapp_pointF p2){ return rmVec2Collide((rmVec2){p.x, p.y}, (rmVec2){p2.x, p2.y}); }

rapp_bool rapp_cubeCollideVec3(rapp_cube cube, rapp_point3D p) { return rmCubeCollide(cube, (rmCube){p.x, p.y, p.z, 1, 1, 1}); }
rapp_bool rapp_cubeCollide(rapp_cube r, rapp_cube r2) { return rmCubeCollide(r, r2); }


