#include <QtGui>
#include "droptablewidget.h"
//mostly from https://github.com/imatefx/auto-file-backup/blob/master/droptablewidget.cpp
DropTableWidget::DropTableWidget(QWidget *parent) : QTableWidget(parent) {
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragDropMode(QAbstractItemView::DragDrop);

    setDragEnabled(true);
    setAcceptDrops(true);

}

void DropTableWidget::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
    const DropMimeData *myData = qobject_cast<const DropMimeData *>(event->mimeData());
    emit dropped(myData);
}

QMimeData *DropTableWidget::mimeData(const QList<QTableWidgetItem*> items) const
{
    DropMimeData *data = new DropMimeData;
    if(!items.isEmpty())
        data->type = items.first()->type();
    return data;
}

void DropTableWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
    const DropMimeData *myData = qobject_cast<const DropMimeData *>(event->mimeData());
    emit changed(myData);
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
