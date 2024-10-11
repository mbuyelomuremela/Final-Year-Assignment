#include "listener.h"

#include <QTextEdit>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QLabel>
#include <QUdpSocket>
#include <QIcon>
#include <QVBoxLayout>


void Listener::setUp()
{

    action_StartServer->setIcon(QIcon(":/images/Images/start.png"));
    action_StopServer->setIcon(QIcon(":/images/Images/stop.jpg"));

    QToolBar *tool_Bar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,tool_Bar);
    tool_Bar->setMovable(false);

    tool_Bar->addAction(action_StartServer);
    tool_Bar->addSeparator();
    tool_Bar->addAction(action_StopServer);

    const QString styleSheet("background-color:#655e6f;border:none;color:white;font-weight:bold;");

    tool_Bar->setStyleSheet(styleSheet);

    setCentralWidget(textEdit);
    textEdit->setEnabled(false); // preveting user from editing
    textEdit->setStyleSheet("border:none;background-color:#ffffff;");

    statusBar()->addPermanentWidget(serverStatusLabel,1);
    statusBar()->setStyleSheet("background-color:#655e6f;");

}


Listener::Listener(QWidget *parent)
    : QMainWindow{parent},
      textEdit{new QTextEdit(this)},
      action_StartServer{new QAction(tr("Start"),this)},
      action_StopServer{new QAction(tr("Stop"),this)},
      serverSockect{new QUdpSocket(this)},
      serverStatusLabel{new QLabel("Server stopped.",this)}
{

    setWindowTitle("Listener");

    setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    setIconSize(QSize(30,30));

    setWindowState(Qt::WindowMaximized);

    setUp();

    connect(serverSockect,&QUdpSocket::readyRead,this,&Listener::readyToReadDatagrams);
    connect(action_StartServer,&QAction::triggered,this,&Listener::startServer);
    connect(action_StopServer,&QAction::triggered,this,&Listener::stopServer);

    setStyleSheet("background-color:#5e645b;");

}

Listener::~Listener()
{

}

void Listener::startServer()
{

    bool listenning = serverSockect->bind(QHostAddress::Any,1996,QAbstractSocket::ShareAddress);

    if(listenning){

        serverStatusLabel->setText("Server started.");
    }

}

void Listener::readyToReadDatagrams()
{

    if(serverSockect->hasPendingDatagrams()){

        QByteArray buffer;
        buffer.resize(serverSockect->pendingDatagramSize());

        serverSockect->readDatagram(buffer.data(),buffer.size());

        textEdit->setPlainText(QString::fromUtf8(buffer));

    }

}

void Listener::stopServer()
{

   serverSockect->close();
   serverStatusLabel->setText("Server stopped.");

}
