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
  Detail WidthOrientation(Detail d, Detail s);
  void Mark(int s_x0, int s_y0, Detail d);
  bool IsSuitLeftover(Detail d);
  void Place(Detail d);
};

#endif  // CUT_H
