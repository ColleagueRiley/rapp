#include <rapp.h>

#include <math.h>

rapp_bool rapp_circleCollidePoint(rapp_circle c, rapp_point p) { return rapp_circleCollideRect(c, (rapp_rect) {p.x, p.y, 1, 1}); }
rapp_bool rapp_circleCollidePointF(rapp_circleF c, rapp_pointF p) { return rapp_circleCollideRectF(c, (rapp_rectF) {p.x, p.y, 1, 1}); }

rapp_bool rapp_circleCollideRectF(rapp_circleF c, rapp_rectF r) {
    // test cords
    float testX = c.x; 
    float testY = c.y;

    // fill cords based on x/ys of the shapes
    if (c.x < r.x)
      testX = r.x;  

    else if (c.x > r.x+r.w) 
      testX = r.x-r.w;

    if (c.y < r.y)  
      testY = r.y;  

    else if (c.y > r.y+r.h)
      testY = r.y+r.h; 
    
    // check
    return ( sqrt( ( (c.x - testX) * (c.x - testX) ) + ( (c.y - testY) * (c.y - testY) ) )  <= (c.d/2) );
}
rapp_bool rapp_circleCollideRect(rapp_circle c, rapp_rect r) { return rapp_circleCollideRectF(RAPP_CIRCLEF(c.x, c.y, c.d), RAPP_RECTF(r.x, r.y, r.w, r.h)); }

rapp_bool rapp_circleCollideF(rapp_circleF cir, rapp_circleF cir2) {
    float distanceBetweenCircles = (float) sqrt(
        (cir2.x - cir.x) * (cir2.x - cir.x) + 
        (cir2.y - cir.y) * (cir2.y - cir.y)
    );

    return !(distanceBetweenCircles > (cir.d/2) + (cir2.d/2)); // check if there is a collide
}

rapp_bool rapp_circleCollide(rapp_circle cir, rapp_circle cir2) { return rapp_circleCollideF(RAPP_CIRCLEF(cir.x, cir.y, cir.d), RAPP_CIRCLEF(cir2.x, cir2.y, cir2.d)); }

rapp_bool rapp_rectCollidePoint(rapp_rect r, rapp_point p){ return (p.x >= r.x &&  p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h); }
rapp_bool rapp_rectCollide(rapp_rect r, rapp_rect r2){ return (r.x + r.w >= r2.x && r.x <= r2.x + r2.w && r.y + r.h >= r2.y && r.y <= r2.y + r2.h); }
rapp_bool rapp_pointCollide(rapp_point p, rapp_point p2){ return (p.x == p2.x && p.y == p2.y); }

rapp_bool rapp_rectCollidePointF(rapp_rectF r, rapp_pointF p){ return (p.x >= r.x &&  p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h); }
rapp_bool rapp_rectCollideF(rapp_rectF r, rapp_rectF r2){ return (r.x + r.w >= r2.x && r.x <= r2.x + r2.w && r.y + r.h >= r2.y && r.y <= r2.y + r2.h); }
rapp_bool rapp_pointCollideF(rapp_pointF p, rapp_pointF p2){ return (p.x == p2.x && p.y == p2.y); }

