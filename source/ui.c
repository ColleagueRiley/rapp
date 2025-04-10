
#include <rapp.h>

rapp_rectF rapp_alignRectF(rapp_rectF larger, rapp_rectF smaller, u16 alignment) {
    rapp_rectF aligned = smaller;

    switch (alignment & rapp_alignHorizontal) {
        case rapp_alignLeft:
            aligned.x = larger.x;
            break;
        case rapp_alignCenter:
            aligned.x = larger.x + ((larger.w - smaller.w) / 2.0);
            break;
        case rapp_alignRight:
            aligned.x = (larger.x + larger.w) - smaller.w;
            break;
        default: break;
    }

    switch (alignment & rapp_alignVertical) {
        case rapp_alignUp:
            aligned.y = larger.y;
            break;
        case rapp_alignMiddle:
            aligned.y = larger.y + ((larger.h - smaller.h) / 2.0);
            break;
        case rapp_alignDown:
            aligned.y = (larger.y + larger.h) - smaller.h;
            break;
        default: break;
    }

    return aligned;
}

rapp_circle rapp_alignText(const char* str, rapp_circle c, rapp_rectF larger, u8 alignment) {
    return rapp_alignText_len(str, 0, c, larger, alignment);
}

rapp_circle rapp_alignText_len(const char* str, size_t str_len, rapp_circle c, rapp_rectF larger, u8 alignment) {
    rapp_area area = rapp_textArea(str, c.d, str_len);
    
    rapp_rectF smaller = RAPP_RECTF(c.x, c.y, area.w, c.d);
    rapp_rectF r = rapp_alignRectF(larger, smaller, alignment);

    return RAPP_CIRCLE(r.x, r.y + (c.d / 4), r.h);
}
