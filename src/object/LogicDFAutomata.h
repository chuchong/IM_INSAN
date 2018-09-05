//利用DFA(有限自动机)来进行AI管理,简单的情况使用SWITCH即可,复杂时考虑状态模式
#ifndef LOGICDFAUTOMATA_H
#define LOGICDFAUTOMATA_H

#include <QObject>
#include "Logic.h"
class LogicDFAutomata : public Logic
{
public:
    LogicDFAutomata();
};

#endif // LOGICDFAUTOMATA_H
