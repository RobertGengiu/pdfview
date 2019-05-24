#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtMath>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pdf = new PDF();
    pdf->current_page = 0;

    pdf->load();
    pdf->ppm(pdf->current_page, 100, 0);

    // de schimbat
    QPixmap pix("C:/Users/gengi/Documents/pdfView/tmp/reg.ppm");
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}



MainWindow::~MainWindow()
{
    pdf->fdoc();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (pdf->current_page > 0) {
        pdf->current_page -= 1;

        pdf->ppm(pdf->current_page, 100, 0);
        QPixmap pix("C:/Users/gengi/Documents/pdfView/tmp/reg.ppm");
        int w = ui->label->width();
        int h = ui->label->height();
        ui->label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if (pdf->current_page <= pdf->page_count) {
        pdf->current_page += 1;

        pdf->ppm(pdf->current_page, 100, 0);
        QPixmap pix("C:/Users/gengi/Documents/pdfView/tmp/reg.ppm");
        int w = ui->label->width();
        int h = ui->label->height();
        ui->label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    }
}
