#ifndef PDF_H
#define PDF_H

#include "mainwindow.h"


class PDF {

public:
    int current_page;
    int page_count;

    fz_context *ctx;
    fz_document *doc;
    fz_pixmap *pix;
    fz_matrix ctm;

    PDF() {}
    int load();
    int ppm(int page_number, int zoom, int rotate);
    void fdoc();
    ~PDF() {}
};

#endif // PDF_H
