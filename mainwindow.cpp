#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cut_widget.h"
#include "detail.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cutButton_clicked()
{
    cut_.blank_.width_ = blank_width_;
    cut_.blank_.length_ = blank_length_;
//    cut_.blank_.width_ = 286;
//    cut_.blank_.length_ = 300;
    Cut_Widget *cut_widget = new Cut_Widget();
    cut_widget->resize(screen_width_, screen_height_);
//    details_.push_back({0, 0, 200, 100});
//    details_.push_back({0, 0, 200, 100});
//    details_.push_back({0, 0, 70, 70});
//    details_.push_back({0, 0, 70, 70});
//    details_.push_back({0, 0, 70, 70});
    std::sort(details_.begin(), details_.end());
    for(auto it = details_.rbegin(); it!=details_.rend(); ++it) {
        cut_.Place(*it);
    }
    int coord_of_vertices = 4;
    for (int i = 0; i<cut_.ref_points_.size();) {
      cut_widget->AddRectangle(  cut_.ref_points_[i].first*scale_factor_
                               , cut_.ref_points_[i].second*scale_factor_
                               , cut_.ref_points_[i+2].first*scale_factor_
                               , cut_.ref_points_[i+2].second*scale_factor_);
      i+=coord_of_vertices;
    }
    // add blank sheet contour
    cut_widget->AddRectangle( 0
                             ,0
                             ,blank_width_*scale_factor_
                             ,blank_length_*scale_factor_);
    cut_widget->show();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void MainWindow::on_addButton_clicked()
{
   for(int i = 0; i<amount_;i++){
     details_.push_back({0, 0, detail_width_, detail_length_});
   }
   QString new_detail = QString::number(detail_width_)+" x "+QString::number(detail_length_);
   ui->label_5->setText(new_detail);
   ui->lineEdit_3->clear();
   ui->lineEdit_4->clear();
}

void MainWindow::CheckInput(int& value
                          , QLabel* label
                          , const char* message) {
    if (value == 0) {
        label->setText("input error");
        value = 1;
    } else {
        label->setText(message);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    blank_width_= arg1.toUInt();
    CheckInput(blank_width_
               , ui->label_6
               , "width, cm");
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    blank_length_ = arg1.toUInt();
    CheckInput(blank_length_
               , ui->label_7
               , "length, cm");
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    detail_width_ = arg1.toUInt();
    CheckInput(detail_width_
               , ui->label_8
               , "width, cm");

}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    detail_length_ = arg1.toUInt();
    CheckInput(detail_length_
               , ui->label_9
               , "length, cm");
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    amount_ = arg1.toUInt();
    CheckInput(amount_
               , ui->label_10
               , "amount");
}

