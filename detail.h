#ifndef DETAIL_H
#define DETAIL_H

#include<cstddef>

struct Detail
{
    int x0_;
    int y0_;
    int width_;
    int length_;

    bool operator < (const Detail &d) const;
    Detail Rotate();
    void Show();
};

#endif // DETAIL_H
