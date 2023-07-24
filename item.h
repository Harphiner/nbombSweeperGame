#ifndef ITEM_H
#define ITEM_H

#include <QPoint>

class item {
   public:
    item();
    item(QPoint pos);
    QPoint my_pos;   // 物体所处的位置
    bool isBomb;     // 是否是雷
    bool ifFlaged;   // 是否被标记
    bool ifLighted;  // 非雷情况，是否打开
    int number;      // 显示的数字
};

#endif  // ITEM_H
