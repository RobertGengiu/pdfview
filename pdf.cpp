#include "mainwindow.h"
#include "pdf.h"

int PDF::load() {

    // de schimbat
    char input[] = "C:/Users/gengi/Documents/pdfView/input/reg.pdf";

    int page_count;

    /* Create a context to hold the exception stack and various caches. */
    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!ctx) {
            fprintf(stderr, "cannot create mupdf context\n");
            return EXIT_FAILURE;
    }

    /* Register the default file types to handle. */
    fz_try(ctx)
    fz_register_document_handlers(ctx);
    fz_catch(ctx)
    {
       fprintf(stderr, "cannot register document handlers: %s\n", fz_caught_message(ctx));
       fz_drop_context(ctx);
       return EXIT_FAILURE;
    }

    /* Open the document. */
    fz_try(ctx)
    doc = fz_open_document(ctx, input);
    fz_catch(ctx) {
    fprintf(stderr, "cannot open document: %s\n", fz_caught_message(ctx));
    fz_drop_context(ctx);
            return EXIT_FAILURE;
     }

    /* Count the number of pages. */
    fz_try(ctx)
    page_count = fz_count_pages(ctx, doc);
    fz_catch(ctx) {
        fprintf(stderr, "cannot count number of pages: %s\n", fz_caught_message(ctx));
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);
        return EXIT_FAILURE;
    }

    this->page_count = page_count;

}

int PDF::ppm(int page_number, int zoom, int rotate) {

    // de schimbat
    char output[] = "C:/Users/gengi/Documents/pdfView/tmp/reg.ppm";
    int x, y;

    if (page_number < 0 || page_number > page_count)
        return EXIT_FAILURE;

    ctm = fz_scale(zoom / 100, zoom / 100);
    ctm = fz_pre_rotate(ctm, rotate);

    /* Render page to an RGB pixmap. */

    fz_try(ctx)
    pix = fz_new_pixmap_from_page_number(ctx, doc, page_number, ctm, fz_device_rgb(ctx), 0);
    fz_catch(ctx) {
        fprintf(stderr, "cannot render page: %s\n", fz_caught_message(ctx));
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);
        return EXIT_FAILURE;
    }


     FILE *fp = fopen(output, "w");
     /* Print image data in ascii PPM format. */
     fprintf(fp, "P3\n");
     fprintf(fp, "%d %d\n", pix->w, pix->h);
     fprintf(fp, "255\n");
     for (y = 0; y < pix->h; ++y) {
         unsigned char *p = &pix->samples[y * pix->stride];
         for (x = 0; x < pix->w; ++x) {
            if (x > 0)
                fprintf(fp, "  ");

            fprintf(fp, "%3d %3d %3d", p[0], p[1], p[2]);
            p += pix->n;
         }
         fprintf(fp, "\n");
     }

     fclose(fp);

    /* Clean up. */
    fz_drop_pixmap(ctx, pix);
    return EXIT_SUCCESS;

}

void PDF::fdoc() {
    fz_drop_document(ctx, doc);
    fz_drop_context(ctx);
}
