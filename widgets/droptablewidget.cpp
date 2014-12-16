#include <QtGui>
#include "droptablewidget.h"

DropTableWidget::DropTableWidget(QWidget *parent) : QTableWidget(parent) {
    //set widget default properties:
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //setShowGrid(false);
    //setWordWrap(false);
    setDragDropMode(QAbstractItemView::DragDrop);
    //setDefaultDropAction(Qt::MoveAction);

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
