#ifndef MYCONTACTLISTITEM_H
#define MYCONTACTLISTITEM_H
#include <QListWidgetItem>

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
