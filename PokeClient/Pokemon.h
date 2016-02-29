#ifndef POKEMON_H
#define POKEMON_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QDebug>

class Pokemon : public QGraphicsItem
{
public:
    Pokemon();
    Pokemon(const Pokemon&);
    Pokemon(int no, QString n, QString a1, QString a2, QString a3, QPixmap img, QRectF r);
    Pokemon(int no, QString n, QString a1, QString a2, QString a3, QPixmap img);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int number;
    QString name;
    enum {max_health=200};
    int health;
    QString attack1;
    QString attack2;
    QString attack3;
    QPixmap image;
    QRectF boundRect;

signals:

public slots:
};

#endif // POKEMON_H
