#include <QtGui>
#include "droptablewidget.h"
//mostly from https://github.com/imatefx/auto-file-backup/blob/master/droptablewidget.cpp
DropTableWidget::DropTableWidget(QWidget *parent) : QTableWidget(parent) {
    // Set default behavior
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::IgnoreAction);
    setDragEnabled(true);
    setAcceptDrops(true);

}

void DropTableWidget::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
    const DropMimeData *myData = qobject_cast<const DropMimeData *>(event->mimeData());
    if(myData)
        emit dropped(myData);
}

QMimeData *DropTableWidget::mimeData(const QList<QTableWidgetItem*> items) const
{
    // Only store the type, only data we need to figure out the list
    DropMimeData *data = new DropMimeData;
    if(!items.isEmpty())
        data->type = items.first()->type();
    return data;
}

void DropTableWidget::dragEnterEvent(QDragEnterEvent *event) {
    const DropMimeData *myData = qobject_cast<const DropMimeData *>(event->mimeData());
    if(myData){
        event->acceptProposedAction();
        emit changed(myData);
    }
}

void DropTableWidget::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void DropTableWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void DropTableWidget::clear() {
    emit changed();
}
