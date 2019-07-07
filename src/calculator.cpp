#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));

    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButton()));
    connect(ui->Sign, SIGNAL(released()), this,
            SLOT(ChangeSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearScreen()));
    connect(ui->MemAdd, SIGNAL(released()), this,
            SLOT(AddToMemory()));
    connect(ui->MemClear, SIGNAL(released()), this,
            SLOT(ClearMemory()));
    connect(ui->MemGet, SIGNAL(released()), this,
            SLOT(GetFromMemory()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed() {
    QPushButton *button = static_cast<QPushButton *>(sender());
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0.0) || (displayVal.toInt() == 0)) {
        ui->Display->setText(buttonVal);
    }
    else {
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed() {
    this->divTriggered = false;
    this->multTriggered = false;
    this->subtTriggered = false;
    this->addTriggered = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = static_cast<QPushButton *>(sender());

    QString buttonVal = button->text();

    if(QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0) {
        this->divTriggered = true;
    }
    else if(QString::compare(buttonVal, "x", Qt::CaseInsensitive) == 0) {
        this->multTriggered = true;
    }
    else if(QString::compare(buttonVal, "-", Qt::CaseInsensitive) == 0) {
        this->subtTriggered = true;
    }
    else if(QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0) {
        this->addTriggered = true;
    }

    ui->Display->setText(buttonVal);
}

void Calculator::EqualButton() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(divTriggered || multTriggered || subtTriggered || addTriggered) {
        if(divTriggered) {
            solution = this->calcVal / dblDisplayVal;
        }
        else if(multTriggered) {
            solution = this->calcVal * dblDisplayVal;
        }
        else if(subtTriggered) {
            solution = this->calcVal - dblDisplayVal;
        }
        else if(addTriggered) {
            solution = this->calcVal + dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeSign() {
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");

    if(reg.exactMatch(displayVal)) {
        double dblDisplayVal = displayVal.toDouble();
        dblDisplayVal *= -1;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::ClearScreen() {
    ui->Display->setText("0");
    this->calcVal = 0.0;
}

void Calculator::AddToMemory() {
    QString memoryVal = ui->Display->text();
    QRegExp reg("[0-9.]*");

    if(reg.exactMatch(memoryVal)) {
        double dblMemoryVal = memoryVal.toDouble();
        this->memVal = dblMemoryVal;
    }
}

void Calculator::ClearMemory() {
    this->memVal = 0.0;
}

void Calculator::GetFromMemory() {
    double memoryVal = this->memVal;
    ui->Display->setText(QString::number(memoryVal));
}
