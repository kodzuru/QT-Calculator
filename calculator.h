#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPushButton>
#include <QStack>
#include <QLCDNumber>
#include <QLayout>
#include <QGridLayout>
#include <QDebug>
#include <QRegExp>


class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    ~Calculator();
private:
    QLCDNumber          *m_plcd;
    QStack<QString>     m_stk;
    QString             m_strDisplay;
public:
    QPushButton* createButton(const QString &);
    void calculate();
public slots:
    void slotButtonClicked();
};

#endif // CALCULATOR_H
