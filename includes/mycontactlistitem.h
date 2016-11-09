#ifndef MYCONTACTLISTITEM_H
#define MYCONTACTLISTITEM_H

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QListWidgetItem>

#ifdef _MSC_VER
#pragma warning(pop)
#endif


class MyContactListItem : public QListWidgetItem
{
public:
    MyContactListItem(const QString &);
    void    setOnline(bool);
    bool    getOnline();

private:
    bool    online;
};

#endif // MYCONTACTLISTITEM_H
