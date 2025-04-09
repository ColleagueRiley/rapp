/*
*
*	rapp 0.01-dev
*
* Copyright (C) 2025 ColleagueRiley
*
* libpng license
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*
*/



#ifndef RAPP_HEADER
#define RAPP_LIB_SHARED
#include "rapp.h"
#endif

#ifndef RAPP_ALLOC
#include <malloc.h>
#define RAPP_ALLOC malloc
#define RAPP_FREE free
#define RAPP_REALLOC realloc
#endif

#define RSGL_MALLOC RAPP_ALLOC
#define RSGL_REALLOC RAPP_REALLOC
#define RSGL_FREE RAPP_FREE
#define RSGL_bool rapp_bool
#define RSGL_color rapp_color
#define RSGL_rect rapp_rect
#define RSGL_rectF rapp_rectF
#define RSGL_point rapp_point
#define RSGL_triangleF rapp_triangleF
#define RSGL_triangle rapp_triangle
#define RSGL_triangle3D rapp_triangle3D
#define RSGL_pointF rapp_pointF
#define RSGL_point3D rapp_point3D
#define RSGL_circle rapp_circle
#define RSGL_circleF rapp_circleF
#define RSGL_mat4 rapp_mat4
#define RSGL_programInfo rapp_programInfo
#define RSGL_texture rapp_texture
#define RSGL_area rapp_area


#define RSGL_NO_DEPS_FOLDER
#define RSGL_IMPLEMENTATION
#define RSGL_INT_DEFINED
#define RSGL_BOOL_DEFINED

#include "deps/RSGL.h"


#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef RAPP_RENDERER_OPENGL
#include "deps/RSGL_gl.h"
#else
#error no renderer defined
#endif

void rapp_setTexture(rapp_texture texture) {
    RSGL_setTexture(texture);
}

void rapp_setProgram(u32 program) {
    RSGL_setProgram(program);
}

void rapp_setGradient(float* gradient, size_t len) {
    RSGL_setGradient(gradient, len);
}

void rapp_fill(rapp_bool fill) {

}

void rapp_center(rapp_point3D center) {
    RSGL_setCenter(center);
}

void rapp_setClearArgs(rapp_bool clearArgs) {
    RSGL_setClearArgs(clearArgs);
}

void rapp_clearArgs(void) {
    RSGL_clearArgs();
}

rapp_rect rapp_alignRect(rapp_rect larger, rapp_rect smaller, u16 alignment) {

}

rapp_rectF rapp_alignRectF(rapp_rectF larger, rapp_rectF smaller, u16 alignment) {

}

rapp_mat4 rapp_initDrawMatrix(rapp_point3D center) {
    return RSGL_initDrawMatrix(center);
}

void rapp_clear(rapp_color color) {
    RSGL_clear(color);
}

void rapp_viewport(i32 x, i32 y, i32 w, i32 h) {
    RSGL_renderViewport(x, y, w, h);
}

rapp_texture rapp_createTexture(u8* bitmap, rapp_area memsize,  u8 channels) {
    return RSGL_renderCreateTexture(bitmap, memsize, channels);
}

void rapp_deleteTexture(rapp_texture tex) {
    RSGL_renderDeleteTexture(tex);
}

void rapp_scissorStart(rapp_rectF scissor) {
    RSGL_renderScissorStart(scissor);
}

void rapp_scissorEnd(void) {
    RSGL_renderScissorEnd();
}

rapp_programInfo rapp_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName) {
    return RSGL_renderCreateProgram(VShaderCode, FShaderCode, posName, texName, colorName);
}

void rapp_renderDeleteProgram(rapp_programInfo program) {
    RSGL_renderDeleteProgram(program);
}

void rapp_renderSetShaderValue(u32 program, char* var, float value[], u8 len) {
    RSGL_renderSetShaderValue(program, var, value, len);
}

rapp_mat4 rapp_mat4Multiply(float left[16], float right[16]) {
    return RSGL_mat4Multiply(left, right);
}

rapp_mat4 rapp_rotate(rapp_mat4 matrix, float angle, float x, float y, float z) {
    return RSGL_rotate(matrix.m, angle, x, y, z);
}

rapp_mat4 rapp_translate(rapp_mat4 matrix, float x, float y, float z) {
    return RSGL_translate(matrix.m, x, y, z);
}

void rapp_drawPoint(rapp_point p, rapp_color c) {
    RSGL_drawPoint(p, c);
}

void rapp_drawPointF(rapp_pointF p, rapp_color c) {
    RSGL_drawPointF(p, c);
}

void rapp_drawTriangle(rapp_triangle t, rapp_color c) {
    RSGL_drawTriangle(t, c);
}

void rapp_drawTriangleF(rapp_triangleF t, rapp_color c) {
    RSGL_drawTriangleF(t, c);
}

void rapp_drawTriangleHyp(rapp_pointF p, size_t angle, float hypotenuse, rapp_color color) {
    RSGL_drawTriangleHyp(p, angle, hypotenuse, color);
}

void rapp_drawRect(rapp_rect r, rapp_color c) {
    RSGL_drawRect(r, c);
}

void rapp_drawRectF(rapp_rectF r, rapp_color c) {
    RSGL_drawRectF(r, c);
}

void rapp_drawRoundRect(rapp_rect r, rapp_point rounding, rapp_color c) {
    RSGL_drawRoundRect(r, rounding, c);
}

void rapp_drawRoundRectF(rapp_rectF r, rapp_point rounding, rapp_color c) {
    RSGL_drawRoundRectF(r, rounding, c);
}

void rapp_drawPolygon(rapp_rect r, u32 sides, rapp_color c) {
    RSGL_drawPolygon(r, sides, c);
}

void rapp_drawPolygonF(rapp_rectF r, u32 sides, rapp_color c) {
    RSGL_drawPolygonF(r, sides, c);
}

void rapp_drawArc(rapp_rect o, rapp_point arc, rapp_color color) {
    RSGL_drawArc(o, arc, color);
}

void rapp_drawArcF(rapp_rectF o, rapp_pointF arc, rapp_color color) {
    RSGL_drawArcF(o, arc, color);
}

void rapp_drawCircle(rapp_circle c, rapp_color color) {
    RSGL_drawCircle(c, color);
}

void rapp_drawCircleF(rapp_circleF c, rapp_color color) {
    RSGL_drawCircleF(c, color);
}

void rapp_drawOval(rapp_rect o, rapp_color c) {
    RSGL_drawOval(o, c);
}

void rapp_drawOvalF(rapp_rectF o, rapp_color c) {
    RSGL_drawOvalF(o, c);
}

void rapp_drawLine(rapp_point p1, rapp_point p2, u32 thickness, rapp_color c) {
    RSGL_drawLine(p1, p2, thickness, c);
}

void rapp_drawLineF(rapp_pointF p1, rapp_pointF p2, u32 thickness, rapp_color c) {
    RSGL_drawLineF(p1, p2, thickness, c);
}

/* 2D outlines */

void rapp_drawTriangleOutline(rapp_triangle t, u32 thickness, rapp_color c) {
    RSGL_drawTriangleOutline(t, thickness, c);
}

void rapp_drawTriangleFOutline(rapp_triangleF t, u32 thickness, rapp_color c) {
    RSGL_drawTriangleFOutline(t, thickness, c);
}

void rapp_drawRectOutline(rapp_rect r, u32 thickness, rapp_color c) {
    RSGL_drawRectOutline(r, thickness, c);
}

void rapp_drawRectFOutline(rapp_rectF r, u32 thickness, rapp_color c) {
    RSGL_drawRectFOutline(r, thickness, c);
}

void rapp_drawRoundRectOutline(rapp_rect r, rapp_point rounding, u32 thickness, rapp_color c) {
    RSGL_drawRoundRectOutline(r, rounding, thickness, c);
}

void rapp_drawRoundRectFOutline(rapp_rectF r, rapp_point rounding, u32 thickness, rapp_color c) {
    RSGL_drawRoundRectFOutline(r, rounding, thickness, c);
}

void rapp_drawPolygonOutline(rapp_rect r, u32 sides, u32 thickness, rapp_color c) {
    RSGL_drawPolygonOutline(r, sides, thickness, c);
}

void rapp_drawPolygonFOutline(rapp_rectF r, u32 sides, u32 thickness, rapp_color c) {
    RSGL_drawPolygonFOutline(r, sides, thickness, c);
}

void rapp_drawArcOutline(rapp_rect o, rapp_point arc, u32 thickness, rapp_color color) {
    RSGL_drawArcOutline(o, arc, thickness, color);
}

void rapp_drawArcFOutline(rapp_rectF o, rapp_pointF arc, u32 thickness, rapp_color color) {
    RSGL_drawArcFOutline(o, arc, thickness, color);
}

void rapp_drawCircleOutline(rapp_circle c, u32 thickness, rapp_color color) {
    RSGL_drawCircleOutline(c, thickness, color);
}

void rapp_drawCircleFOutline(rapp_circleF c, u32 thickness, rapp_color color) {
    RSGL_drawCircleFOutline(c, thickness, color);
}

void rapp_drawOvalFOutline(rapp_rectF o, u32 thickness, rapp_color c) {
    RSGL_drawOvalFOutline(o, thickness, c);
}

void rapp_drawOvalOutline(rapp_rect o, u32 thickness, rapp_color c) {
    RSGL_drawOvalOutline(o, thickness, c);
}


rapp_font* rapp_loadFont(const char* font) {
    return (rapp_font*)RSGL_loadFont(font);
}

rapp_font* rapp_loadFontEx(const char* font, size_t atlasWidth, size_t atlasHeight) {
    return (rapp_font*)RSGL_loadFontEx(font, atlasWidth, atlasHeight);
}

void rapp_setFont(rapp_font* font) {
    RSGL_setFont((RSGL_font*)font);
}

void rapp_drawText(const char* text, rapp_circle c, rapp_color color) {
    RSGL_drawText(text, c, color);
}

rapp_area rapp_textArea(const char* text, u32 fontSize, size_t textEnd) {
    return RSGL_textArea(text, fontSize, textEnd);
}

rapp_image rapp_drawImage(rapp_image image, rapp_rect r) {
    u32 texture = RSGL_args.texture;

    RSGL_setTexture(image.tex);
    RSGL_drawRect(r, RSGL_RGBA(255, 255, 255, 255));
    RSGL_setTexture(texture);
}

rapp_image rapp_drawImageFile(const char* image, rapp_rect r) {

}


rapp_image rapp_loadImage(const char* image) {
    rapp_image img;

    i32 c;
    u8* bitmap = stbi_load(image, (int*)&img.srcSize.w, (int*)&img.srcSize.h, &c, 0);
    img.tex = RSGL_renderCreateTexture(bitmap, (RSGL_area){img.srcSize.w, img.srcSize.h}, c);

    RSGL_FREE(bitmap);

    return img;
}

rapp_bool rapp_circleCollidePoint(rapp_circle c, rapp_point p) {
}

rapp_bool rapp_circleCollideRect(rapp_circle c, rapp_rect r) {
}

rapp_bool rapp_circleCollide(rapp_circle cir1, rapp_circle cir2) {
}

rapp_bool rapp_rectCollidePoint(rapp_rect r, rapp_point p) {
}

rapp_bool rapp_rectCollide(rapp_rect r, rapp_rect r2) {
}

rapp_bool rapp_pointCollide(rapp_point p, rapp_point p2) {
}


rapp_bool rapp_pointCollideF(rapp_pointF p, rapp_pointF p2) {
}

rapp_bool rapp_rectCollideF(rapp_rectF r, rapp_rectF r2) {
}

rapp_bool rapp_rectCollidePointF(rapp_rectF r, rapp_pointF p) {
}

rapp_bool rapp_circleCollideF(rapp_circleF cir1, rapp_circleF cir2) {
}

rapp_bool rapp_circleCollideRectF(rapp_circleF c, rapp_rectF r) {
}

rapp_bool rapp_circleCollidePointF(rapp_circleF c, rapp_pointF p) {
}

rapp_area rapp_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line) {
    return RSGL_textLineArea(text, fontSize, textEnd, line);
}

rapp_circle rapp_alignText_len(const char* str, size_t str_len, rapp_circle c, rapp_rectF larger, u8 alignment) {
}

rapp_circle rapp_alignText(const char* str, rapp_circle c, rapp_rectF larger, u8 alignment) {
}

void rapp_drawText_pro(const char* text, size_t len, float spacing, rapp_circle c, rapp_color color) {
    RSGL_drawText_pro(text, len, spacing, c, color);
}

void rapp_drawText_len(const char* text, size_t len, rapp_circle c, rapp_color color) {
    RSGL_drawText_len(text, len, c, color);
}

#include <stdarg.h>
const char* rapp_strFmt(const char* string, ...) {
   static char output[1024];

   va_list args;
   va_start(args, string);
   
   RFONT_VSNPRINTF(output, 1024, string, args);
   va_end(args);

   return output;

}
