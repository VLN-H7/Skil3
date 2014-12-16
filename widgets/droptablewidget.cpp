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
    setDefaultDropAction(Qt::MoveAction);

    setDragEnabled(true);
    setAcceptDrops(true);

}

void DropTableWidget::dragEnterEvent(QDragEnterEvent *event) {

    //event->acceptProposedAction();
	emit changed(event->mimeData());
    QTableWidget::dragEnterEvent(event);
}

void DropTableWidget::dragMoveEvent(QDragMoveEvent *event) {
    //event->acceptProposedAction();
    QTableWidget::dragMoveEvent(event);
}

void DropTableWidget::dropEvent(QDropEvent *event) {
    //event->acceptProposedAction();
    //emit dropped(event->mimeData());
    const DropMimeData *myData =
                qobject_cast<const DropMimeData *>(event->mimeData());
    if (myData) {
        // access myData's data directly (not through QMimeData's API)
        int size, temp;
        qDebug() << myData->type;
    }
    QTableWidget::dropEvent(event);
}

void DropTableWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    //event->accept();
    QTableWidget::dragLeaveEvent(event);
}

bool DropTableWidget::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action){
    const DropMimeData *myData =
                qobject_cast<const DropMimeData *>(data);
    if (!myData)
        return false;
    // access myData's data directly (not through QMimeData's API)
    int size, temp;
    qDebug() << myData->type;
    bool result = QTableWidget::dropMimeData(row, column, myData->realData, action);
    emit dropped(row, column, data);
    return result;
}

QMimeData *DropTableWidget::mimeData(const QList<QTableWidgetItem*> items) const
{
    QMimeData *realData = QTableWidget::mimeData(items);
    DropMimeData *data = new DropMimeData;
    if(!items.isEmpty())
        data->type = items.first()->type();
    data->realData = realData;
    qDebug() << items.first()->type();
    //data->setTypes(encodedData);
    return data;
}

void DropTableWidget::clear() {
	emit changed();
    QTableWidget::clear();
}
