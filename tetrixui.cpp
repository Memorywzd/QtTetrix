#include <QtWidgets>

#include "tetrixlogic.h"
#include "tetrixui.h"

TetrixUI::TetrixUI()
{
    //ui.setupUi(this);
    logic = new TetrixLogic;

    nextCubeLabel = new QLabel;
    nextCubeLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextCubeLabel->setAlignment(Qt::AlignCenter);

    logic->setNextCubeLabel(nextCubeLabel);

    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);


    connect(startButton, &QPushButton::clicked, logic, &TetrixLogic::start);
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, logic, &TetrixLogic::pause);

    connect(logic, &TetrixLogic::scoreChanged, scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(logic, &TetrixLogic::levelChanged, levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(logic, &TetrixLogic::removedLinesChanged, linesLcd, QOverload<int>::of(&QLCDNumber::display));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(createLabel(tr("NEXT")), 0, 0);
    layout->addWidget(nextCubeLabel, 1, 0);
    layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(logic, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);
    setLayout(layout);

    setWindowTitle(tr("QtTetrix by Memorywzd"));
    resize(550, 370);
}

QLabel* TetrixUI::createLabel(const QString& text)
{
    QLabel* label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
