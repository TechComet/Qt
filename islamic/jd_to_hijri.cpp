#include "widget.h"
#include <QApplication>
#include <QtCore>
#include <QtDebug>

static double gregToJd (int m, int d, int y)
    {
    int a;
    int b;
    int jd;

        if (m < 3) {
            y--;
            m += 12;
        }

        if ((y < 1582) || (y == 1582 && m < 10)
            || (y == 1582 && m == 10 && d <= 15)
        ) {
            // This is ignored in the GregorianToJD PHP function!
            b = 0;
        } else {
            a = (int)(y / 100);
            b = 2 - a + (int)(a / 4);
        }

        jd = (int)(365.25 * (y + 4716)) + (int)(30.6001 * (m + 1))
            + d + b - 1524.5;

        return round(jd);
    }

static QList<int> jdToIslamic(double jd)
    {
    int l;
    int n;
    int j;
    int m;
    int d;
    int y;

        l = (int)jd - 1948440 + 10632;
        n = (int)((l - 1) / 10631);
        l = l - 10631 * n + 354;
        j = (int)((10985 - l) / 5316) * (int)((50 * l) / 17719)
            + (int)(l / 5670) * (int)((43 * l) / 15238);
        l = l - (int)((30 - j) / 15) * (int)((17719 * j) / 50)
            - (int)(j / 16) * (int)((15238 * j) / 43) + 29;
        m = (int)((24 * l) / 709);
        d = l - (int)((709 * m) / 24);
        y = (int)(30 * n + j - 30);

        return QList<int>() << y << m << d;
    }

int main(int argc, char *argv[])
{

    QDate curDate = QDate().currentDate();
    qDebug() << jdToIslamic(gregToJd(curDate.month(), curDate.day(), curDate.year()));
}
