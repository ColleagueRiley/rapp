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



#ifndef RI_HEADER
#define RILIB_SHARED
#include "rapp.h"
#endif

#ifndef RI_ALLOC
#include <malloc.h>
#define RI_ALLOC malloc
#define RI_FREE free
#define RI_REALLOC realloc
#endif

#define RSGL_MALLOC RI_ALLOC
#define RSGL_REALLOC RI_REALLOC
#define RSGL_FREE RI_FREE
#define RSGL_bool riBool
#define RSGL_color riColor
#define RSGL_rect riRect
#define RSGL_rectF riRectF
#define RSGL_point riPoint
#define RSGL_triangleF riTriangleF
#define RSGL_triangle riTriangle
#define RSGL_pointF riPointF
#define RSGL_point3D riPoint3D
#define RSGL_point3DF riPoint3DF
#define RSGL_circle riCircle
#define RSGL_circleF riCircleF
#define RSGL_MATRIX RI_MATRIX
#define RSGL_programInfo riProgramInfo
#define RSGL_texture riTexture
#define RSGL_image riImage
#define RSGL_MATRIX RI_MATRIX
#define RSGL_area riArea


#define RSGL_NO_DEPS_FOLDER
#define RSGL_IMPLEMENTATION
#define RSGLDEF
#include "deps/RSGL.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef RI_RENDERER_OPENGL
#include "deps/RSGL_gl.h"
#else
#error no renderer defined
#endif

void ri_setTexture(riTexture texture) {
    RSGL_setTexture(texture);
}

void ri_setProgram(u32 program) {
    RSGL_setProgram(program);
}

void ri_setGradient(float* gradient, size_t len) {
    RSGL_setGradient(gradient, len);
}

void ri_fill(riBool fill) {
    RSGL_fill(fill);
}

void ri_center(riPoint3DF center) {
    RSGL_center(center);
}

void ri_setClearArgs(riBool clearArgs) {
    RSGL_setClearArgs(clearArgs);
}

void ri_clearArgs(void) {
    RSGL_clearArgs();
}

riRect ri_alignRect(riRect larger, riRect smaller, u16 alignment) {
    return RSGL_alignRect(larger, smaller, alignment);
}

riRectF ri_alignRectF(riRectF larger, riRectF smaller, u16 alignment) {
    return RSGL_alignRectF(larger, smaller, alignment);
}

RI_MATRIX ri_initDrawMatrix(riPoint3DF center) {
    return RSGL_initDrawMatrix(center);
}

void ri_clear(riColor color) {
    RSGL_clear(color);
}

void ri_viewport(i32 x, i32 y, i32 w, i32 h) {
    RSGL_renderViewport(x, y, w, h);
}

riTexture ri_createTexture(u8* bitmap, riArea memsize,  u8 channels) {
    return RSGL_renderCreateTexture(bitmap, memsize, channels);
}

void ri_deleteTexture(riTexture tex) {
    RSGL_renderDeleteTexture(tex);
}

void ri_scissorStart(riRectF scissor) {
    RSGL_renderScissorStart(scissor);
}

void ri_scissorEnd(void) {
    RSGL_renderScissorEnd();
}

riProgramInfo ri_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName) {
    return RSGL_renderCreateProgram(VShaderCode, FShaderCode, posName, texName, colorName);
}

void ri_renderDeleteProgram(riProgramInfo program) {
    RSGL_renderDeleteProgram(program);
}

void ri_renderSetShaderValue(u32 program, char* var, float value[], u8 len) {
    RSGL_renderSetShaderValue(program, var, value, len);
}

RI_MATRIX ri_matrixMultiply(float left[16], float right[16]) {
    return RSGL_matrixMultiply(left, right);
}

RI_MATRIX ri_rotatef(RI_MATRIX* matrix, float angle, float x, float y, float z) {
    return RSGL_rotatef(matrix, angle, x, y, z);
}

RI_MATRIX ri_translatef(RI_MATRIX* matrix, float x, float y, float z) {
    return RSGL_translatef(matrix, x, y, z);
}

void ri_drawPoint(riPoint p, riColor c) {
    RSGL_drawPoint(p, c);
}

void ri_drawPointF(riPointF p, riColor c) {
    RSGL_drawPointF(p, c);
}

void ri_plotLines(riPointF* lines, size_t points_count, u32 thickness, riColor c) {
    RSGL_plotLines(lines, points_count, thickness, c);
}

void ri_drawTriangle(riTriangle t, riColor c) {
    RSGL_drawTriangle(t, c);
}

void ri_drawTriangleF(riTriangleF t, riColor c) {
    RSGL_drawTriangleF(t, c);
}

void ri_drawTriangleHyp(riPointF p, size_t angle, float hypotenuse, riColor color) {
    RSGL_drawTriangleHyp(p, angle, hypotenuse, color);
}

void ri_drawRect(riRect r, riColor c) {
    RSGL_drawRect(r, c);
}

void ri_drawRectF(riRectF r, riColor c) {
    RSGL_drawRectF(r, c);
}

void ri_drawRoundRect(riRect r, riPoint rounding, riColor c) {
    RSGL_drawRoundRect(r, rounding, c);
}

void ri_drawRoundRectF(riRectF r, riPoint rounding, riColor c) {
    RSGL_drawRoundRectF(r, rounding, c);
}

void ri_drawPolygon(riRect r, u32 sides, riColor c) {
    RSGL_drawPolygon(r, sides, c);
}

void ri_drawPolygonF(riRectF r, u32 sides, riColor c) {
    RSGL_drawPolygonF(r, sides, c);
}

void ri_drawArc(riRect o, riPoint arc, riColor color) {
    RSGL_drawArc(o, arc, color);
}

void ri_drawArcF(riRectF o, riPointF arc, riColor color) {
    RSGL_drawArcF(o, arc, color);
}

void ri_drawCircle(riCircle c, riColor color) {
    RSGL_drawCircle(c, color);
}

void ri_drawCircleF(riCircleF c, riColor color) {
    RSGL_drawCircleF(c, color);
}

void ri_drawOval(riRect o, riColor c) {
    RSGL_drawOval(o, c);
}

void ri_drawOvalF(riRectF o, riColor c) {
    RSGL_drawOvalF(o, c);
}

void ri_drawLine(riPoint p1, riPoint p2, u32 thickness, riColor c) {
    RSGL_drawLine(p1, p2, thickness, c);
}

void ri_drawLineF(riPointF p1, riPointF p2, u32 thickness, riColor c) {
    RSGL_drawLineF(p1, p2, thickness, c);
}

/* 2D outlines */

void ri_drawTriangleOutline(riTriangle t, u32 thickness, riColor c) {
    RSGL_drawTriangleOutline(t, thickness, c);
}

void ri_drawTriangleFOutline(riTriangleF t, u32 thickness, riColor c) {
    RSGL_drawTriangleFOutline(t, thickness, c);
}

void ri_drawRectOutline(riRect r, u32 thickness, riColor c) {
    RSGL_drawRectOutline(r, thickness, c);
}

void ri_drawRectFOutline(riRectF r, u32 thickness, riColor c) {
    RSGL_drawRectFOutline(r, thickness, c);
}

void ri_drawRoundRectOutline(riRect r, riPoint rounding, u32 thickness, riColor c) {
    RSGL_drawRoundRectOutline(r, rounding, thickness, c);
}

void ri_drawRoundRectFOutline(riRectF r, riPoint rounding, u32 thickness, riColor c) {
    RSGL_drawRoundRectFOutline(r, rounding, thickness, c);
}

void ri_drawPolygonOutline(riRect r, u32 sides, u32 thickness, riColor c) {
    RSGL_drawPolygonOutline(r, sides, thickness, c);
}

void ri_drawPolygonFOutline(riRectF r, u32 sides, u32 thickness, riColor c) {
    RSGL_drawPolygonFOutline(r, sides, thickness, c);
}

void ri_drawArcOutline(riRect o, riPoint arc, u32 thickness, riColor color) {
    RSGL_drawArcOutline(o, arc, thickness, color);
}

void ri_drawArcFOutline(riRectF o, riPointF arc, u32 thickness, riColor color) {
    RSGL_drawArcFOutline(o, arc, thickness, color);
}

void ri_drawCircleOutline(riCircle c, u32 thickness, riColor color) {
    RSGL_drawCircleOutline(c, thickness, color);
}

void ri_drawCircleFOutline(riCircleF c, u32 thickness, riColor color) {
    RSGL_drawCircleFOutline(c, thickness, color);
}

void ri_drawOvalFOutline(riRectF o, u32 thickness, riColor c) {
    RSGL_drawOvalFOutline(o, thickness, c);
}

void ri_drawOvalOutline(riRect o, u32 thickness, riColor c) {
    RSGL_drawOvalOutline(o, thickness, c);
}


i32 ri_loadFont(const char* font) {
    return RSGL_loadFont(font);
}

i32 ri_loadFontPro(const char* font, size_t atlasWidth, size_t atlasHeight) {
    return RSGL_loadFontPro(font, atlasWidth, atlasHeight);
}

void ri_setFont(i32 font) {
    RSGL_setFont(font);
}

void ri_drawText(const char* text, riCircle c, riColor color) {
    RSGL_drawText(text, c, color);
}

riArea ri_textArea(const char* text, u32 fontSize, size_t textEnd) {
    return RSGL_textArea(text, fontSize, textEnd);
}

riImage ri_drawImage(riImage image, riRect r) {
    u32 texture = RSGL_args.texture;

    RSGL_setTexture(image.tex);
    RSGL_drawRect(r, RSGL_RGBA(255, 255, 255, 255));
    RSGL_setTexture(texture);
}

riImage ri_drawImageFile(const char* image, riRect r) {
    return RSGL_drawImage(image, r);
}


riImage ri_loadImage(const char* image) {
    riImage img;

    i32 c;
    u8* bitmap = stbi_load(image, (int*)&img.srcSize.w, (int*)&img.srcSize.h, &c, 0);
    img.tex = RSGL_renderCreateTexture(bitmap, (RSGL_area){img.srcSize.w, img.srcSize.h}, c);

    RSGL_FREE(bitmap);
    strcpy(img.file, image);

    return img;
}

riBool riCircleCollidePoint(riCircle c, riPoint p) {
    return RSGL_circleCollidePoint(c, p);
}

riBool riCircleCollideRect(riCircle c, riRect r) {
    return RSGL_circleCollideRect(c, r);
}

riBool riCircleCollide(riCircle cir1, riCircle cir2) {
    return RSGL_circleCollide(cir1, cir2);
}

riBool riRectCollidePoint(riRect r, riPoint p) {
    return RSGL_rectCollidePoint(r, p);
}

riBool riRectCollide(riRect r, riRect r2) {
    return RSGL_rectCollide(r, r2);
}

riBool riPointCollide(riPoint p, riPoint p2) {
    return RSGL_pointCollide(p, p2);
}


riBool riPointCollideF(riPointF p, riPointF p2) {
    return RSGL_pointCollideF(p, p2);
}

riBool riRectCollideF(riRectF r, riRectF r2) {
    return RSGL_rectCollideF(r, r2);
}

riBool riRectCollidePointF(riRectF r, riPointF p) {
    return RSGL_rectCollidePointF(r, p);
}

riBool riCircleCollideF(riCircleF cir1, riCircleF cir2) {
    return RSGL_circleCollideF(cir1, cir2);
}

riBool riCircleCollideRectF(riCircleF c, riRectF r) {
    return RSGL_circleCollideRectF(c, r);
}

riBool riCircleCollidePointF(riCircleF c, riPointF p) {
    return RSGL_circleCollidePointF(c, p);
}

riArea ri_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line) {
    return RSGL_textLineArea(text, fontSize, textEnd, line);
}

riCircle ri_alignText_len(const char* str, size_t str_len, riCircle c, riRectF larger, u8 alignment) {
    return RSGL_alignText_len(str, str_len, c, larger, alignment);
}

riCircle ri_alignText(const char* str, riCircle c, riRectF larger, u8 alignment) {
    return RSGL_alignText(str, c, larger, alignment);
}

void ri_drawText_pro(const char* text, size_t len, float spacing, riCircle c, riColor color) {
    RSGL_drawText_pro(text, len, spacing, c, color);
}

void ri_drawText_len(const char* text, size_t len, riCircle c, riColor color) {
    RSGL_drawText_len(text, len, c, color);
}

void ri_setRFont(struct RFont_font* font) {
    RSGL_setRFont(font);
}


#include <stdarg.h>
const char* RI_strFmt(const char* string, ...) {
   static char output[1024];

   va_list args;
   va_start(args, string);
   
   RFONT_VSNPRINTF(output, 1024, string, args);
   va_end(args);

   return output;

}
