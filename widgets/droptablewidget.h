#ifndef DROPAREA_H
#define DROPAREA_H

#include <QTableWidget>
#include "dropmimedata.h"
class QMimeData;

class DropTableWidget : public QTableWidget {
	Q_OBJECT

 	public:
        DropTableWidget(QWidget *parent = 0);

    signals:
        void changed(const DropMimeData *mimeData = 0);
        void dropped(const DropMimeData *mimeData = 0);

    public slots:
        void clear();

    protected:
            void dragEnterEvent(QDragEnterEvent *event);
            void dragMoveEvent(QDragMoveEvent *event);
            void dragLeaveEvent(QDragLeaveEvent *event);
            void dropEvent(QDropEvent *event);
        QMimeData *mimeData(const QList<QTableWidgetItem *> items) const;
};

#endif
