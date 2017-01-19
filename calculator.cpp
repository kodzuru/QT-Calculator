#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);

    QString aButtons[4][4]{ {"7", "8", "9", "/"},
                            {"4", "5", "6", "*"},
                            {"1", "2", "3", "-"},
                            {"0", ".", "=", "+"}
                            };
    QGridLayout *pTopLayout = new QGridLayout;
    pTopLayout->addWidget(m_plcd, 0,0,1,4);
    pTopLayout->addWidget(createButton("CE"), 1, 3);

    for( int i(0); i < 4; i++){
        for( int j(0); j < 4; j++){
            pTopLayout->addWidget( createButton(aButtons[i][j]), i+2, j );
        }
    }
    setLayout(pTopLayout);

}

Calculator::~Calculator()
{

}
QPushButton* Calculator::createButton(const QString &str)
{
    QPushButton *button = new QPushButton(str);
    button->setMinimumSize(40, 40);
    connect( button, SIGNAL(clicked()), SLOT(slotButtonClicked()) );
    return button;
}
 void Calculator::slotButtonClicked()
 {

    QString str = ((QPushButton*)sender())->text();

    if(str == "CE"){
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if(str.contains(QRegExp("[0-9]"))){
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if( str == "."){
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }else{
        if(m_stk.count() >= 2){
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));
            if(str != "="){
                m_stk.push(str);
            }
        }else{
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(str);
            m_strDisplay = "";
            m_plcd->display("0");
        }
    }


 }
void Calculator::calculate(){

    double dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    double dOperand1 = m_stk.pop().toDouble();
    double dResult = 0;

    if(strOperation == "+"){
        dResult = dOperand1 + dOperand2;
    }
    if(strOperation == "-"){
        dResult = dOperand1 - dOperand2;
    }
    if(strOperation == "*"){
        dResult = dOperand1 * dOperand2;
    }
    if(strOperation == "/"){
        dResult = dOperand1 / dOperand2;
    }

    m_plcd->display(dResult);

}
