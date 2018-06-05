//
// Created by hubao on 2018/4/6.
//

#ifndef MYACCOUNT_CHA13_4_MSGHANDLER_H
#define MYACCOUNT_CHA13_4_MSGHANDLER_H

#include <set>

class Message;
class Floder{
public:
    void addMsg(Message* apMsg)
    {
        if(NULL != apMsg)
            mpMsgSet.insert(apMsg);
    }
    void removeMsg(Message* apMsg)
    {
        std::set<Message*>::iterator liIter = mpMsgSet.find(apMsg);
        if(liIter != mpMsgSet.end()) mpMsgSet.erase(liIter);
    }
private:
    std::set<Message*> mpMsgSet;
};
class Message{
public:
    Message(const std::string& aoContent = NULL) : moContent(aoContent){}
    Message(const Message& aoObj){
        moContent = aoObj.moContent;
        moFloderSet = aoObj.moFloderSet;

        addToFloder(aoObj.moFloderSet);
    }
    Message& operator=(const Message& aoObj)
    {
        if(&aoObj != this){
            removeFromFloder();

            moContent = aoObj.moContent;
            moFloderSet = aoObj.moFloderSet;
            addToFloder(aoObj.moFloderSet);
        }
        return *this;
    }
private:
    void removeFromFloder()
    {
        for(std::set<Floder*>::iterator liIter = moFloderSet.begin();
            liIter != moFloderSet.end(); ++liIter){
            (*liIter)->removeMsg(this);
        }
    }
    void addToFloder(std::set<Floder*> aoSet)
    {
        for(std::set<Floder*>::iterator liIter = aoSet.begin();
            liIter != aoSet.end(); ++liIter){
            (*liIter)->addMsg(this);
        }
    }
    std::string moContent;
    std::set<Floder*> moFloderSet;
};
#endif //MYACCOUNT_CHA13_4_MSGHANDLER_H
