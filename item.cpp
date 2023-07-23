#include "item.h"
#include <QPoint>

item::item()
{
    my_pos=QPoint(-1,-1);
    number=0;
    isOpen=false;
    isMarked=false;
    isMine=false;
}

item::item(QPoint pos)
{
    my_pos=pos;
    number=0;
    isOpen=false;
    isMarked=false;
    isMine=false;
}
