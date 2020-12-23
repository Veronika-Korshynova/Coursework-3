#include "taskdelegate.hpp"

#include <cmath>

TaskDelegate::TaskDelegate(QObject *parent): QStyledItemDelegate(parent) { }

void TaskDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    const QPalette &palette(opt.palette);
    const QRect &rect(opt.rect);
    const QRect &content(rect.adjusted(margins.left(),
                                       margins.top(),
                                       -margins.right(),
                                       -margins.bottom()));
    const bool lastIndex = (index.model()->rowCount() - 1 == index.row());
    const bool hasIcon = !opt.icon.isNull();
    const int bottomEdge = rect.bottom();

    QFont font(opt.font);

    font.setPointSize(12);

    painter->save();
    painter->setClipping(true);
    painter->setClipRect(rect);
    painter->setFont(opt.font);

    painter->fillRect(rect,
                      opt.state & QStyle::State_Selected ?
                          palette.highlight().color() :
                          palette.light().color());
    painter->setPen(lastIndex ?
                        palette.dark().color() :
                        palette.mid().color());
    painter->drawLine(lastIndex ?
                          rect.left() :
                          margins.left(),
                      bottomEdge,
                      rect.right(),
                      bottomEdge);


    auto deadlineText = dataDeadline(opt);
    auto performerText = dataPerformer(opt);

    auto hasDeadline = deadlineText.length() != 0;
    auto hasPerformer = performerText.length() != 0;

    if (dataType(opt)) {
        auto iconSize = 128;
        auto iconY = content.height() / 2 - iconSize / 2;
        auto iconX = content.width() / 2 - iconSize / 2;

        painter->drawPixmap(iconX,
                            iconY,
                            opt.icon.pixmap(QSize(iconSize, iconSize)));

        auto box = opt.fontMetrics.boundingRect(content, Qt::AlignCenter | Qt::TextWordWrap, opt.text);
        QRect rect(box);

        rect.moveTo(margins.left() , iconY + spacingVert + iconSize);

        painter->setFont(font);
        painter->setPen(palette.text().color());
        painter->drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, opt.text);

    } else {
        if (hasIcon) {
            painter->drawPixmap(content.left(),
                                content.top(),
                                opt.icon.pixmap(iconSize()));
        }

        font.setBold(true);

        QFontMetrics metrics(font);

        auto priority = QString("");
        for (int i = 0; i < dataPriority(opt); i++)
            priority += "!";

        auto prBox = metrics.boundingRect(priority).adjusted(0,0,1,1);
        QRect prRect (prBox);

        prRect.moveTo(margins.left() + iconSize().width() + spacingHor,
                           content.top());

        painter->setFont(font);
        painter->setPen(QColor(255, 0, 0));
        painter->drawText(prRect, Qt::TextSingleLine, priority);

        auto messageBox = metrics.boundingRect(opt.text).adjusted(0,0,1,1);
        QRect messageRect (messageBox);

        messageRect.moveTo(margins.left() + iconSize().width() + spacingHor + prRect.width() + spacingHor,
                           content.top());

        painter->setFont(font);
        painter->setPen(palette.text().color());
        painter->drawText(messageRect, Qt::TextSingleLine, opt.text);

        font.setBold(false);

        auto deadlineBox = deadlineText.length() == 0 ? QRect() : opt.fontMetrics.boundingRect(deadlineText).adjusted(0,0,1,1);

        if (hasDeadline) {
            QRect deadlineRect (deadlineBox);
            deadlineRect.moveTo(margins.left() + iconSize().width() + spacingHor,
                               content.top() + messageBox.height() + spacingVert);

            painter->setPen(palette.text().color());
            painter->setFont(font);
            painter->drawText(deadlineRect, Qt::TextSingleLine, deadlineText);
        }

        if (hasPerformer) {
            auto performerBox = opt.fontMetrics.boundingRect(performerText).adjusted(0,0,1,1);
            QRect performerRect (performerBox);
            performerRect.moveTo(margins.left() + iconSize().width() + spacingHor,
                               content.top() + messageBox.height() + (hasDeadline ? (deadlineBox.height() + spacingVert * 2) : 0));

            painter->setPen(palette.text().color());
            painter->setFont(font);
            painter->drawText(performerRect, Qt::TextSingleLine, performerText);
        }
    }

    painter->restore();
}

QSize TaskDelegate::sizeHint (const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    auto type = dataType(opt);

    auto deadlineText = dataDeadline(opt);
    auto performerText = dataPerformer(opt);

    auto hasDeadline = deadlineText.length() != 0;
    auto hasPerformer = performerText.length() != 0;

    int deadlineHeight = !hasDeadline ? 0 : opt.fontMetrics.boundingRect(deadlineText).height();
    int performerHeight = !hasPerformer ? 0 : opt.fontMetrics.boundingRect(performerText).height();

    int textHeight = 0;
    if (!type)
        textHeight = opt.fontMetrics.boundingRect(opt.text).adjusted(0,0,1,1).height() +
            spacingVert + deadlineHeight + hasDeadline * spacingHor + performerHeight + hasPerformer * spacingHor;
    else return QSize(opt.rect.width(), opt.widget->height());

    int iconHeight = iconSize().height();
    int h = std::max(textHeight, iconHeight);

    return QSize(opt.rect.width(), margins.top() + h + margins.bottom());
}

QSize TaskDelegate::iconSize() const {
    return icon;
}

void TaskDelegate::setIconSize(int wh) {
    icon = QSize(wh,wh);
}

QMargins TaskDelegate::contentMargins() const {
    return margins;
}

void TaskDelegate::setContentMargins(int left,
                                     int top,
                                     int right,
                                     int bottom)
{
    margins = QMargins(left, top, right, bottom);
}

int TaskDelegate::horizontalSpacing() const {
    return spacingHor;
}

void TaskDelegate::setHorizontalSpacing(int spacing) {
    spacingHor = spacing;
}

int TaskDelegate::verticalSpacing() const {
    return spacingVert;
}

void TaskDelegate::setVerticalSpacing(int spacing) {
    spacingVert = spacing;
}

bool TaskDelegate::dataType(QStyleOptionViewItem &opt) const {
    return opt.index.data(Qt::UserRole).toBool();
}
QString TaskDelegate::dataDeadline(QStyleOptionViewItem &opt) const {
    return opt.index.data(Qt::UserRole + 1).toString();
}
QString TaskDelegate::dataPerformer(QStyleOptionViewItem &opt) const {
    return opt.index.data(Qt::UserRole + 2).toString();

}
int TaskDelegate::dataPriority(QStyleOptionViewItem &opt) const {
    return opt.index.data(Qt::UserRole + 3).toInt();
}

QSize TaskDelegate::bigIconSize() const {
    return bigIcon;
}

void TaskDelegate::setBigIconSize(int size) {
    bigIcon = QSize(size, size);
}
