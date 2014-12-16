#ifndef DROPAREA_H
#define DROPAREA_H

#include <QTableWidget>
#include "dropmimedata.h"
class QMimeData;

class DropTableWidget : public QTableWidget {
	Q_OBJECT

 	public:
 		DropTableWidget(QWidget *parent = 0);

	public slots:
		void clear();

	signals:
		void changed(const QMimeData *mimeData = 0);
        void dropped(int row, int column, const QMimeData *mimeData = 0);

	protected:
		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dragLeaveEvent(QDragLeaveEvent *event);
		void dropEvent(QDropEvent *event);

        bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action);
        QMimeData *mimeData(const QList<QTableWidgetItem *> items) const;
private:
		QTableWidget *tablewidget;
};

#endif
