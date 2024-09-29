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
    Cut_Widget *cut_widget = new Cut_Widget();
    cut_widget->resize(screen_width_, screen_height_);
    details_.push_back({0, 0, 200, 100});
    details_.push_back({0, 0, 200, 100});
    details_.push_back({0, 0, 70, 70});
    details_.push_back({0, 0, 70, 70});
    details_.push_back({0, 0, 70, 70});
    std::sort(details_.begin(), details_.end());
    for(auto it = details_.rbegin(); it!=details_.rend(); ++it) {
        cut_.Place(*it);
    }
    for (int i = 0; i<cut_.ref_points_.size();) {
      cut_widget->AddRectangle(  cut_.ref_points_[i].first*scale_factor_
                               , cut_.ref_points_[i].second*scale_factor_
                               , cut_.ref_points_[i+2].first*scale_factor_
                               , cut_.ref_points_[i+2].second*scale_factor_);
      i+=4;
    }
    /*for (auto& el:cut_.leftovers_) {
        el.Show();
    }*/
    // add blank sheet contour
    cut_widget->AddRectangle( 0
                             ,0
                             ,blank_width_*scale_factor_
                             ,blank_length_*scale_factor_);
    cut_widget->show();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void MainWindow::on_addButton_clicked()
{
   details_.push_back({0, 0, detail_width_, detail_length_});
   QString new_detail = QString::number(detail_width_)+" x "+QString::number(detail_length_);
   ui->label_5->setText(new_detail);
   ui->lineEdit_3->setText("");
   ui->lineEdit_4->setText("");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    blank_width_= arg1.toUInt();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    blank_length_ = arg1.toUInt();
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    detail_width_ = arg1.toUInt();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    detail_length_ = arg1.toUInt();
}

