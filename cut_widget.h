#ifndef CUT_WIDGET_H
#define CUT_WIDGET_H

#include <QPainter>
#include <QRubberBand>
#include <QVector>
#include <QWidget>

#include "detail.h"

namespace Ui {
class Cut_Widget;
}

class Cut_Widget : public QWidget {
  Q_OBJECT

 public:
  QVector<QRubberBand*> rect_;
  uint8_t colour_count_{0};
  QVector<QColor> colours_{Qt::yellow
                         , Qt::blue
                         , Qt::cyan
                         , Qt::green
                         , Qt::red
                         , Qt::white
                         , Qt::magenta};
  static const size_t screen_width_ = 840;
  static const size_t screen_height_ = 840;
  explicit Cut_Widget(QWidget* parent = nullptr);
  ~Cut_Widget();
  virtual void paintEvent(QPaintEvent* event);
  void AddRectangle(const size_t& x1
                  , const size_t& y1
                  , const size_t& x2
                  , const size_t& y2);

 private:
  Ui::Cut_Widget* ui;
};

#endif  // CUT_WIDGET_H
