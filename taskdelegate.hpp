#pragma once

#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QSize>

class TaskDelegate : public QStyledItemDelegate {
public:
    TaskDelegate(QObject *parent = nullptr);

    QSize iconSize() const;

    void setIconSize(int wh);

    QMargins contentMargins() const;

    void setContentMargins(int left, int top, int right, int bottom);

    int horizontalSpacing() const;

    void setHorizontalSpacing(int spacing);

    int verticalSpacing() const;

    void setVerticalSpacing(int spacing);

    void paint (QPainter *painter,
                const QStyleOptionViewItem &option,
                const QModelIndex &index) const;

    QSize sizeHint (const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;

    QSize bigIconSize() const;

    void setBigIconSize(int size);

    bool dataType(QStyleOptionViewItem &opt) const;
    QString dataDeadline(QStyleOptionViewItem &opt) const;
    QString dataPerformer(QStyleOptionViewItem &opt) const;
    int dataPriority(QStyleOptionViewItem &opt) const;

private:
    QSize icon;
    QMargins margins;
    int spacingHor;
    int spacingVert;
    QSize bigIcon;
};

