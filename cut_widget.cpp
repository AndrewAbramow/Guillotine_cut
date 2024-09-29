#include "cut_widget.h"
#include "ui_cut_widget.h"

#include <QPalette>
#include <QBrush>

Cut_Widget::Cut_Widget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::Cut_Widget)
{
    ui->setupUi(this);
    setStyleSheet("background-color:white;");
}

Cut_Widget::~Cut_Widget()
{
    delete ui;
}

void Cut_Widget::AddRectangle(  size_t x1
                              , size_t y1
                              , size_t x2
                              , size_t y2) {
    QRect new_rectang;
    new_rectang.setCoords(x1,y1,x2,y2);
    QPalette palette;
    QRubberBand* rectang_band = new QRubberBand(QRubberBand::Rectangle, this);
    palette.setBrush(QPalette::Highlight, QBrush(colours_[colour_count_++]));
    rectang_band->setPalette(palette);
    rectang_band->setGeometry(new_rectang);
    rect_.push_back(rectang_band);
    if (colour_count_ > 6) {
        colour_count_ = 0;
    }
    //rect_.push_back(new_rectang);
}

void Cut_Widget::paintEvent(QPaintEvent*) {
    //QPainter painter(this);
    for(auto& r : rect_) {
       //painter.drawRect(r);
        r->show();
    }
}
