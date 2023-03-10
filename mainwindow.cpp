#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getBrewer(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString name;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       name += json_obj["name"].toString();
       qDebug()<<"\n DATA : "+json_obj["name"].toString();

    }

    ui->MainText->setText(name+" data " + response_data);

    reply->deleteLater();
    getManager->deleteLater();
}


void MainWindow::on_RequestButton_clicked()
{
    QString site_url="https://api.openbrewerydb.org/breweries/madtree-brewing-cincinnati";
    QNetworkRequest request((site_url));

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBrewer(QNetworkReply*)));

    reply = getManager->get(request);


}

