#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double calcVal = 0.0;
    double memVal = 0.0;
    bool divTriggered = false;
    bool multTriggered = false;
    bool subtTriggered = false;
    bool addTriggered = false;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeSign();
    void ClearScreen();
    void AddToMemory();
    void ClearMemory();
    void GetFromMemory();

};

#endif // CALCULATOR_H
