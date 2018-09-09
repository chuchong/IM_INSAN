#include "SceneBattle.h"

SceneBattle::SceneBattle()
{

}

void SceneBattle::parseFromFile(QString j)
{
    QFile loadFile(j);

     if(!loadFile.open(QIODevice::ReadOnly))
     {
         qDebug() << "could't open projects json";
         return;
     }

     QByteArray allData = loadFile.readAll();
     loadFile.close();

     QJsonParseError json_error;
     QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

     if(json_error.error != QJsonParseError::NoError)
     {
         qDebug() << "json error!";
         return;
     }
    //以上为初始化过程
     QJsonObject rootObj = jsonDoc.object();
    //详见qt教程

}

void SceneBattle::update()
{

}

void SceneBattle::redraw()
{

}

void SceneBattle::load()
{

}

void SceneBattle::unload()
{

}

