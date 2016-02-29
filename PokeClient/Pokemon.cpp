#include "Pokemon.h"

Pokemon::Pokemon()
{

}

Pokemon::Pokemon(const Pokemon &p)
{
    this->number = p.number;
    this->name = p.name;
    this->attack1 = p.attack1;
    this->attack2 = p.attack2;
    this->attack3 = p.attack3;
    this->boundRect = p.boundRect;
}

Pokemon::Pokemon(int no, QString n, QString a1, QString a2, QString a3, QPixmap img, QRectF r)
{
    health = max_health;
    number = no;
    name = n;
    attack1 = a1;
    attack2 = a2;
    attack3 = a3;
    image = img;
    //img = img.scaledToWidth(300,Qt::SmoothTransformation);
    boundRect = r;
}

Pokemon::Pokemon(int no, QString n, QString a1, QString a2, QString a3, QPixmap img)
{
    number = no;
    name = n;
    attack1 = a1;
    attack2 = a2;
    attack3 = a3;
    image = img;
}
/*
Pokemon::Pokemon(int no, QString n, QString a1, QString a2, QString a3, QPixmap img, QRectF bRect)
{
    number = no;
    name = n;
    attack1 = a1;
    attack2 = a2;
    attack3 = a3;
    image = img;
    boundRect = bRect;
}
*/
QRectF Pokemon::boundingRect() const
{
    return boundRect;
}

void Pokemon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF source(0,0,image.width(),image.height());
    painter->drawPixmap(boundingRect(), image, source);
}

