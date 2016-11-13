#include "mycontactlistitem.h"

MyContactListItem::MyContactListItem(const QString & text) : QListWidgetItem(text)
{

}

void    MyContactListItem::setOnline(bool online)
{
    this->online = online;
}

bool    MyContactListItem::getOnline() const
{
    return (this->online);
}
