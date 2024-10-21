#include "detail.h"
#include <QDebug>

bool Detail::operator < (const Detail &d) const {
  return (width_ * length_) < (d.width_ * d.length_);
}

void Detail::Show() {
    qDebug()<<"Start point: ("<<x0_<<" : "<<y0_<<")\n";
    qDebug()<<"Sheet: "<<width_<<" x "<<length_<<'\n';
}
