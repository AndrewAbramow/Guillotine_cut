#ifndef CUT_H
#define CUT_H

#include <QList>
#include <QVector>

#include "detail.h"

struct Cut {
  QList<Detail> leftovers_;
  QVector<std::pair<size_t, size_t>> ref_points_;
  Detail blank_;
  // Cut(size_t width, size_t length);
  Cut();
  Detail WidthOrientation(const Detail& d, const Detail& s);
  void Mark(const int& s_x0, const int& s_y0, const Detail& d);
  bool IsSuitLeftover(const Detail& d);
  void Place(const Detail& pd);
};

#endif  // CUT_H
