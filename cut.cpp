#include<QDebug>

#include "cut.h"

Cut::Cut() : blank_({0, 0, 0, 0}) {}
//Cut::Cut(size_t width, size_t length) : blank({0, 0, width, length}) {}

Detail Cut::WidthOrientation(const Detail& d, const Detail& s) {
    if ((s.width_ - d.length_)<(s.width_ - d.width_)) {
        Detail new_detail; // RVO
        new_detail.length_ = d.width_;
        new_detail.width_ = d.length_;
      return new_detail;
    } else {
      return d;
    }
  }

  /*
                  y ←-0
                      ↓
                      x
     ← length →
  ----------D-----A
     blank  | cut |   ↑
     sheet  C-----B  width
  ________________|   ↓

  */
  void Cut::Mark(const int& s_x0
               , const int& s_y0
               , const Detail& d) {
    ref_points_.push_back({s_x0, s_y0});                        // A
    ref_points_.push_back({s_x0 + d.width_, s_y0});             // B
    ref_points_.push_back({s_x0 + d.width_, s_y0 + d.length_}); // C
    ref_points_.push_back({s_x0, s_y0 + d.length_});            // D

  }

  bool Cut::IsSuitLeftover(const Detail& d) {
      if(leftovers_.empty()) return false;
      for (auto it = leftovers_.begin(); it != leftovers_.end(); ++it) {
        // enought width
        if ((*it).width_>=d.width_) {
          // enought length:
          /*
                           y ←-0
                               ↓
                               x
             ← length →
          ---------+-------+   ↑
                   |   1   |
                   +-------+  width
                     |  2  |
          ___________|_____|   ↓
          */
          if ((*it).length_>=d.length_) {
            Mark((*it).x0_, (*it).y0_, d);
            // width leftover
            Detail new_w_d {(*it).x0_ + d.width_, (*it).y0_, (*it).width_-d.width_, (*it).length_};
            // length leftover
            Detail new_l_d {(*it).x0_, (*it).y0_+ d.length_, (*it).width_, (*it).length_-d.length_};
            leftovers_.erase(it);
            if (new_l_d.length_>0) {
                leftovers_.push_front(new_l_d);
            }
            leftovers_.push_back(new_w_d);
            return true;
          }
          // need more length:
          /*
                           y ←-0
                               ↓
                               x
             ← length →
          -----+----+------+   ↑
               |  2 |   1  |
               +--+-+------+  width
                  |    3   |
          ________|________|   ↓
          */
          else {
            int init_length = d.length_;// - (*it).length_;
            int remain_length = init_length;
            auto start_l = it;
            auto end_l = start_l;
            for (; end_l != leftovers_.end(); ++end_l) {
              if ((*end_l).width_>=d.width_) {
                remain_length-=(*end_l).length_;
              } else {
                remain_length = init_length;
                start_l = end_l;
              }
              if (remain_length<=0) {
                Mark((*start_l).x0_, (*start_l).y0_, d);
                Detail new_l_d {(*end_l).x0_
                            , (*end_l).y0_+(*end_l).length_+ remain_length
                            , (*end_l).width_
                            , abs(remain_length)};
                //(*end_l).width_-=d.width_;
                leftovers_.erase(start_l, ++end_l);
                leftovers_.push_back(new_l_d);
                return true;
              }
            }
            // leftovers + cut from blank for additional length:
            /*
                             y ←-0
                                 ↓
                                 x
               ← length →
            -----+----+------+   ↑
                 |  2 |   1  |
              +--+----+------+  width
              |       3      |
            __|______________|   ↓
            */
            if (remain_length>0) {
                //if ((*start_l).width_>=d.width_) {
                    Mark((*start_l).x0_, (*start_l).y0_, d);
                    leftovers_.erase(start_l, end_l);
                    leftovers_.push_back({blank_.x0_, blank_.y0_, blank_.width_-d.width_, remain_length});
                    blank_.length_ -= remain_length; // cut detail length from blank
                    blank_.y0_ += remain_length ; // shift blank start_point
                    return true;
                //}
            }
          }
        }
      }
      return false;
    }

  void Cut::Place(const Detail& pd) {
    Detail d = WidthOrientation(pd, blank_);
    if (!IsSuitLeftover(d)) {
      // cut from blank
      /*
                         y ←-0
                             ↓
                             x
           ← length →
        -----+----+------+   ↑
             |    |      |
             | 2  |   1  |  width
             |    |      |
        _____|____|______|   ↓
      */
      Mark(blank_.x0_, blank_.y0_, d);
      leftovers_.push_back({d.width_, blank_.y0_, blank_.width_-d.width_, d.length_});
      blank_.length_ -= d.length_; // cut detail length from blank
      blank_.y0_ += d.length_ ; // shift blank start_point
    }
  }
