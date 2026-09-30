#include "RoomLayoutView.h"

#include "GripItem.h"
#include "WallGraphicsItem.h"

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QWheelEvent>
#include <cmath>

namespace {
constexpr int    MoveThreshold = 5;
constexpr qreal  OsnapRadius   = 12.0;

bool isAxisTool(FloorPlanTool tool)
{
    return tool == FloorPlanTool::PlaceHAxis || tool == FloorPlanTool::PlaceVAxis;
}

bool usesCrossCursor(FloorPlanTool tool)
{
    return tool == FloorPlanTool::DrawWall || tool == FloorPlanTool::PlaceDoor
           || tool == FloorPlanTool::PlaceStair || tool == FloorPlanTool::PlaceText
           || isAxisTool(tool) || tool == FloorPlanTool::MoveByPoints;
}

template <typename Item>
void deleteSceneItem(Item *&item)
{
    if (!item) return;
    if (item->scene()) item->scene()->removeItem(item);
    delete item;
    item = nullptr;
}
}

RoomLayoutView::RoomLayoutView(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void RoomLayoutView::resetView()
{
    resetTransform();
    if (scene()) fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void RoomLayoutView::setEditorEnabled(bool enabled)
{
    editorEnabled = enabled;
    updateDragMode();
}

void RoomLayoutView::setTool(FloorPlanTool newTool)
{
    if (tool != newTool) cancelTransient();
    tool = newTool;
    updateDragMode();
    setCursor(editorEnabled && usesCrossCursor(tool) ? Qt::CrossCursor : Qt::ArrowCursor);
}

void RoomLayoutView::setOrthoEnabled(bool e)  { orthoEnabled = e; }
void RoomLayoutView::setOsnapEnabled(bool e)  { osnapEnabled = e; if (!e) showSnapMarker({}, false); }
void RoomLayoutView::setSnapPoints(const QVector<SnapCandidate> &pts) { snapCandidates = pts; }
void RoomLayoutView::setWallSegments(const QVector<QPair<QPointF,QPointF>> &segs) { wallSegs = segs; }

void RoomLayoutView::cancelTransient()
{
    stopPanning();
    hasFirstPoint = false;
    moveHasBase   = false;
    moveSelectedItems.clear();
    deleteSceneItem(previewItem);
    deleteSceneItem(axisPreviewItem);
    deleteSceneItem(moveGuideItem);
    deleteSceneItem(snapMarkerRect);
    deleteSceneItem(snapMarkerText);
    dragState = ViewDragState::None;
    activeGrip = nullptr;
    dragItems.clear(); dragItemsOldPos.clear();
}

void RoomLayoutView::updateDragMode()
{
    setDragMode(editorEnabled && tool == FloorPlanTool::Select
                    ? QGraphicsView::RubberBandDrag
                    : QGraphicsView::NoDrag);
}

void RoomLayoutView::stopPanning()
{
    if (!isPanning) return;
    isPanning = false;
    if (viewport()->mouseGrabber() == viewport()) viewport()->releaseMouse();
}

QPointF RoomLayoutView::constrainMoveDelta(QPointF delta) const
{
    if (!orthoEnabled) return delta;
    if (qAbs(delta.x()) >= qAbs(delta.y())) delta.setY(0.0);
    else delta.setX(0.0);
    return delta;
}

QVector<QGraphicsItem *> RoomLayoutView::selectedMovableItems() const
{
    QVector<QGraphicsItem *> items;
    if (!scene()) return items;
    for (QGraphicsItem *item : scene()->selectedItems()) {
        if (!dynamic_cast<GripItem *>(item)) items.append(item);
    }
    return items;
}

void RoomLayoutView::updatePreviewLine(QGraphicsLineItem *&item, const QLineF &line,
                                       const QPen &pen, qreal zValue)
{
    if (!item) {
        item = scene()->addLine(line, pen);
        item->setZValue(zValue);
    } else {
        item->setLine(line);
    }
}

void RoomLayoutView::setWallCreatedHandler     (std::function<void(QPointF,QPointF)> f) { wallCreatedHandler=std::move(f); }
void RoomLayoutView::setRoomLabelPositionHandler(std::function<void(QPointF)> f)        { roomLabelPositionHandler=std::move(f); }
void RoomLayoutView::setSymbolPlacedHandler    (std::function<void(SymbolType,QPointF)> f){ symbolPlacedHandler=std::move(f); }
void RoomLayoutView::setTextPositionHandler    (std::function<void(QPointF)> f)         { textPositionHandler=std::move(f); }
void RoomLayoutView::setAxisCreatedHandler     (std::function<void(AxisDirection,QPointF,QPointF)> f){ axisCreatedHandler=std::move(f); }
void RoomLayoutView::setGripReleasedHandler    (std::function<void(QString,GripOwnerType,bool,QPointF)> f){ gripReleasedHandler=std::move(f); }
void RoomLayoutView::setItemsMovedHandler      (std::function<void(QVector<QGraphicsItem*>,QPointF)> f){ itemsMovedHandler=std::move(f); }
void RoomLayoutView::setRequestMoveHandler     (std::function<void()> f) { requestMoveHandler=std::move(f); }

void RoomLayoutView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
    if (!scene()) return;
    const qreal step = 40.0;
    QPen gridPen(QColor(170, 180, 190, 115), 0.0, Qt::CustomDashLine, Qt::FlatCap);
    gridPen.setCosmetic(true);
    gridPen.setDashPattern({1.5, 3.5});
    painter->setPen(gridPen);
    qreal x = std::floor(rect.left()/step)*step;
    for (; x <= rect.right(); x += step) painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
    qreal y = std::floor(rect.top()/step)*step;
    for (; y <= rect.bottom(); y += step) painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
}

void RoomLayoutView::wheelEvent(QWheelEvent *event)
{
    const qreal factor = event->angleDelta().y() > 0 ? 1.15 : (1.0/1.15);
    const qreal cur = transform().m11();
    if ((cur > 8.0 && factor > 1.0) || (cur < 0.05 && factor < 1.0)) return;
    scale(factor, factor);
    event->accept();
}

void RoomLayoutView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton) {
        isPanning = true;
        lastPanPosition = event->pos();
        viewport()->grabMouse();
        setCursor(Qt::ClosedHandCursor);
        event->accept(); return;
    }
    stopPanning();
    if (!editorEnabled || event->button() != Qt::LeftButton) {
        QGraphicsView::mousePressEvent(event); return;
    }

    const QPointF scenePos = mapToScene(event->pos());

    if (tool == FloorPlanTool::DrawWall) {
        bool snapped; const QPointF pt = acquirePoint(scenePos, &snapped);
        if (!hasFirstPoint) {
            firstPoint = pt; hasFirstPoint = true;
            showSnapMarker(pt, snapped);
        } else {
            const QPointF start = firstPoint;
            cancelTransient();
            if (pt != start && wallCreatedHandler) {
                wallCreatedHandler(start, pt);
            }
        }
        event->accept(); return;
    }

    if (isAxisTool(tool)) {
        bool snapped; const QPointF pt = acquirePoint(scenePos, &snapped);
        if (!hasFirstPoint) {
            firstPoint = pt; hasFirstPoint = true;
            showSnapMarker(pt, snapped);
        } else {
            QPointF locked = (tool == FloorPlanTool::PlaceHAxis)
                             ? QPointF(pt.x(), firstPoint.y())
                             : QPointF(firstPoint.x(), pt.y());
            if (locked != firstPoint && axisCreatedHandler) {
                const AxisDirection dir = (tool==FloorPlanTool::PlaceHAxis)
                                          ? AxisDirection::Horizontal
                                          : AxisDirection::Vertical;
                const QPointF start = firstPoint;
                cancelTransient();
                axisCreatedHandler(dir, start, locked);
            } else {
                cancelTransient();
            }
        }
        event->accept(); return;
    }

    if (tool == FloorPlanTool::PlaceRoomLabel) {
        if (roomLabelPositionHandler) roomLabelPositionHandler(scenePos);
        event->accept(); return;
    }
    if (tool == FloorPlanTool::PlaceDoor || tool == FloorPlanTool::PlaceStair) {
        if (symbolPlacedHandler)
            symbolPlacedHandler(tool==FloorPlanTool::PlaceDoor ? SymbolType::Door:SymbolType::Stair, scenePos);
        event->accept(); return;
    }
    if (tool == FloorPlanTool::PlaceText) {
        if (textPositionHandler) textPositionHandler(scenePos);
        event->accept(); return;
    }

    if (tool == FloorPlanTool::MoveByPoints) {
        if (!moveHasBase) {
            bool snapped;
            const QPointF pt = acquirePoint(scenePos, &snapped);
            moveBasePoint = pt;
            moveHasBase   = true;
            hasFirstPoint = true;
            firstPoint    = pt;
            moveSelectedItems = selectedMovableItems();
            showSnapMarker(pt, snapped);
        } else {
            bool snapped;
            const QPointF dest = acquirePointFrom(scenePos, moveBasePoint, &snapped);
            const QPointF delta(dest.x() - moveBasePoint.x(), dest.y() - moveBasePoint.y());
            const QVector<QGraphicsItem *> items = moveSelectedItems;
            cancelTransient();
            if (delta.manhattanLength() > 0.01 && itemsMovedHandler)
                itemsMovedHandler(items, delta);
            if (scene()) scene()->clearSelection();
            if (requestMoveHandler) requestMoveHandler();
        }
        event->accept(); return;
    }

    if (tool == FloorPlanTool::Select) {
        QGraphicsItem *hit = itemAt(event->pos());
        if (auto *grip = dynamic_cast<GripItem *>(hit)) {
            dragState        = ViewDragState::GripDrag;
            activeGrip       = grip;
            dragStartScenePos = scenePos;
            event->accept(); return;
        }

        if (hit) {
            setDragMode(QGraphicsView::NoDrag);
        } else {
            setDragMode(QGraphicsView::RubberBandDrag);
        }

        QGraphicsView::mousePressEvent(event);

        dragItems = selectedMovableItems();
        if (!dragItems.isEmpty()) {
            dragItemsOldPos.clear();
            for (auto *item : dragItems) {
                dragItemsOldPos << item->pos();
            }
            dragStartViewPos  = event->pos();
            dragStartScenePos = scenePos;
            dragState = ViewDragState::PotentialItemMove;
        }
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void RoomLayoutView::mouseMoveEvent(QMouseEvent *event)
{
    if (isPanning) {
        const QPoint delta = event->pos() - lastPanPosition;
        lastPanPosition = event->pos();
        const qreal scaleX = transform().m11();
        const qreal scaleY = transform().m22();
        if (!qFuzzyIsNull(scaleX) && !qFuzzyIsNull(scaleY)) {
            translate(delta.x() / scaleX, delta.y() / scaleY);
        }
        event->accept(); return;
    }

    if (editorEnabled && tool == FloorPlanTool::DrawWall) {
        updateWallPreview(event->pos()); event->accept(); return;
    }

    if (editorEnabled && isAxisTool(tool)) {
        updateAxisDrawPreview(event->pos()); event->accept(); return;
    }

    if (editorEnabled && tool == FloorPlanTool::MoveByPoints && moveHasBase) {
        const QPointF raw = mapToScene(event->pos());
        bool snapped;
        const QPointF dest = acquirePointFrom(raw, moveBasePoint, &snapped);
        showSnapMarker(dest, snapped);
        const QLineF guide(moveBasePoint, dest);
        QPen pen(QColor(255, 180, 0), 1.5, Qt::DashLine);
        pen.setCosmetic(true);
        updatePreviewLine(moveGuideItem, guide, pen, 29.0);
        event->accept(); return;
    }

    if (dragState == ViewDragState::GripDrag && activeGrip) {
        const QPointF raw = mapToScene(event->pos());
        QPointF constrained;
        const bool isAxis = (activeGrip->ownerType()==GripOwnerType::HAxis
                             || activeGrip->ownerType()==GripOwnerType::VAxis);
        bool snapped = false;
        if (isAxis) {
            constrained = constrainAxisGrip(activeGrip, raw);
        } else {
            constrained = acquirePointFrom(raw, activeGrip->otherEndpoint(), &snapped);
        }
        showSnapMarker(constrained, snapped && !isAxis);

        const QLineF line(activeGrip->otherEndpoint(), constrained);
        QPen pen(QColor(0,145,105),2.0,Qt::DashLine); pen.setCosmetic(true);
        updatePreviewLine(previewItem, line, pen, 30.0);
        event->accept(); return;
    }

    if (dragState == ViewDragState::PotentialItemMove) {
        if ((event->pos()-dragStartViewPos).manhattanLength() > MoveThreshold)
            dragState = ViewDragState::ItemMove;
    }

    if (dragState == ViewDragState::ItemMove) {
        const QPointF delta = constrainMoveDelta(mapToScene(event->pos()) - dragStartScenePos);
        for (int i = 0; i < dragItems.size(); ++i)
            dragItems[i]->setPos(dragItemsOldPos[i] + delta);
        event->accept(); return;
    }

    QGraphicsView::mouseMoveEvent(event);
}

void RoomLayoutView::mouseReleaseEvent(QMouseEvent *event)
{
    updateDragMode();

    if (isPanning && (event->button()==Qt::MiddleButton||event->button()==Qt::RightButton)) {
        stopPanning();
        setCursor(tool==FloorPlanTool::DrawWall||isAxisTool(tool)
                      ? Qt::CrossCursor : Qt::ArrowCursor);
        event->accept(); return;
    }

    if (event->button() == Qt::LeftButton) {
        if (dragState == ViewDragState::GripDrag && activeGrip) {
            const QPointF raw = mapToScene(event->pos());
            QPointF finalPos;
            bool snapped = false;
            if (activeGrip->ownerType()==GripOwnerType::HAxis
                || activeGrip->ownerType()==GripOwnerType::VAxis) {
                finalPos = constrainAxisGrip(activeGrip, raw);
            } else {
                finalPos = acquirePointFrom(raw, activeGrip->otherEndpoint(), &snapped);
            }
            if (gripReleasedHandler && finalPos != activeGrip->otherEndpoint()) {
                gripReleasedHandler(activeGrip->ownerId(), activeGrip->ownerType(),
                                    activeGrip->role()==GripRole::StartPoint, finalPos);
            }
            deleteSceneItem(previewItem);
            showSnapMarker({}, false);
            dragState = ViewDragState::None; activeGrip = nullptr;
            event->accept(); return;
        }

        if (dragState == ViewDragState::ItemMove) {
            const QPointF delta = constrainMoveDelta(mapToScene(event->pos()) - dragStartScenePos);
            for (int i = 0; i < dragItems.size(); ++i)
                dragItems[i]->setPos(dragItemsOldPos[i]);

            if (delta.manhattanLength() > 0.5 && itemsMovedHandler)
                itemsMovedHandler(dragItems, delta);

            dragItems.clear(); dragItemsOldPos.clear();
            dragState = ViewDragState::None;
            event->accept(); return;
        }

        if (dragState == ViewDragState::PotentialItemMove) {
            dragItems.clear(); dragItemsOldPos.clear();
            dragState = ViewDragState::None;
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void RoomLayoutView::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
}

void RoomLayoutView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_M) {
        if (editorEnabled && tool == FloorPlanTool::Select
            && !selectedMovableItems().isEmpty()) {
            setTool(FloorPlanTool::MoveByPoints);
        }
        event->accept();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

QPointF RoomLayoutView::acquirePoint(QPointF raw, bool *snapped)
{
    return acquirePointFrom(raw, firstPoint, snapped);
}

QPointF RoomLayoutView::acquirePointFrom(QPointF raw, QPointF ref, bool *snapped)
{
    if (snapped) *snapped = false;
    QPointF orthoRaw = raw;
    if (orthoEnabled && hasFirstPoint) {
        const qreal dx = qAbs(raw.x()-ref.x()), dy = qAbs(raw.y()-ref.y());
        orthoRaw = (dx >= dy) ? QPointF(raw.x(), ref.y()) : QPointF(ref.x(), raw.y());
    }
    if (!osnapEnabled) return orthoRaw;

    const qreal scale = transform().m11();
    const qreal tolSq = (OsnapRadius / scale) * (OsnapRadius / scale);
    qreal bestSq = tolSq;
    const SnapCandidate *best = nullptr;

    for (const SnapCandidate &c : snapCandidates) {
        const qreal dx = c.point.x()-raw.x(), dy = c.point.y()-raw.y();
        if (dx*dx + dy*dy < bestSq) { bestSq = dx*dx+dy*dy; best = &c; }
    }

    QPointF livePerpPt;
    bool livePerpFound = false;
    if (hasFirstPoint && !wallSegs.isEmpty()) {
        qreal perpBestSq = bestSq;
        for (const auto &seg : wallSegs) {
            const QPointF AB = seg.second - seg.first;
            const qreal lenSq = AB.x()*AB.x() + AB.y()*AB.y();
            if (lenSq < 1e-9) continue;
            const qreal t = QPointF::dotProduct(ref - seg.first, AB) / lenSq;
            if (t < 0.0 || t > 1.0) continue;
            const QPointF foot = seg.first + t * AB;
            const qreal dx = foot.x()-raw.x(), dy = foot.y()-raw.y();
            const qreal dsq = dx*dx + dy*dy;
            if (dsq < perpBestSq) { perpBestSq = dsq; livePerpPt = foot; livePerpFound = true; }
        }
    }

    if (livePerpFound) {
        if (snapped) *snapped = true;
        snapMarkerType = SnapType::Perpendicular;
        return livePerpPt;
    }
    if (best) {
        if (snapped) *snapped = true;
        snapMarkerType = best->type;
        return best->point;
    }
    return orthoRaw;
}

QPointF RoomLayoutView::constrainAxisGrip(const GripItem *grip, QPointF raw) const
{
    if (grip->ownerType() == GripOwnerType::HAxis)
        return QPointF(raw.x(), grip->otherEndpoint().y());
    else
        return QPointF(grip->otherEndpoint().x(), raw.y());
}

void RoomLayoutView::updateWallPreview(QPoint vp)
{
    if (!scene()) return;
    bool snapped;
    const QPointF pt = acquirePoint(mapToScene(vp), &snapped);
    showSnapMarker(pt, snapped && (hasFirstPoint || osnapEnabled));
    if (!hasFirstPoint) return;
    const QLineF line(firstPoint, pt);
    QPen pen(QColor(0,145,105),2.0,Qt::DashLine); pen.setCosmetic(true);
    updatePreviewLine(previewItem, line, pen, 30.0);
}

void RoomLayoutView::updateAxisDrawPreview(QPoint vp)
{
    if (!scene()) return;
    bool snapped;
    const QPointF pt = acquirePoint(mapToScene(vp), &snapped);
    showSnapMarker(pt, snapped && (hasFirstPoint || osnapEnabled));
    if (!hasFirstPoint) return;

    QPointF locked = (tool == FloorPlanTool::PlaceHAxis) ? QPointF(pt.x(), firstPoint.y()) : QPointF(firstPoint.x(), pt.y());
    const QLineF line(firstPoint, locked);

    QPen pen(QColor(60,90,200),2.0,Qt::CustomDashLine);
    pen.setDashPattern({8.0,4.0}); pen.setCosmetic(true);
    updatePreviewLine(axisPreviewItem, line, pen, 29.0);
}

void RoomLayoutView::showSnapMarker(QPointF pos, bool visible)
{
    if (!scene()) return;

    const QPen markerPen(QColor(0,200,150), 1.5);
    const qreal S = 5.0;

    if (visible) {
        if (snapMarkerRect && snapMarkerRect->data(0).toInt() != static_cast<int>(snapMarkerType)) {
            deleteSceneItem(snapMarkerRect);
            deleteSceneItem(snapMarkerText);
        }
        if (!snapMarkerRect) {
            snapMarkerRect = scene()->addRect(QRectF(-S,-S,2*S,2*S), markerPen, Qt::NoBrush);
            snapMarkerRect->setFlag(QGraphicsItem::ItemIgnoresTransformations);
            snapMarkerRect->setZValue(31.0);
            snapMarkerRect->setData(0, static_cast<int>(snapMarkerType));

            snapMarkerText = new QGraphicsSimpleTextItem();
            snapMarkerText->setFlag(QGraphicsItem::ItemIgnoresTransformations);
            snapMarkerText->setZValue(32.0);
            QFont f; f.setPointSize(7); snapMarkerText->setFont(f);
            snapMarkerText->setBrush(QColor(0,200,150));
            scene()->addItem(snapMarkerText);

            switch (snapMarkerType) {
            case SnapType::Endpoint:
                snapMarkerRect->setPen(markerPen);
                snapMarkerText->setText(QStringLiteral("\u25a0"));
                break;
            case SnapType::Midpoint:
                snapMarkerRect->setPen(QPen(QColor(0,160,230),1.5));
                snapMarkerText->setText(QStringLiteral("\u25b3"));
                snapMarkerText->setBrush(QColor(0,160,230));
                break;
            case SnapType::Intersection:
                snapMarkerRect->setPen(QPen(QColor(230,100,0),1.5));
                snapMarkerText->setText(QStringLiteral("\u00d7"));
                snapMarkerText->setBrush(QColor(230,100,0));
                break;
            case SnapType::Perpendicular:
                snapMarkerRect->setPen(QPen(QColor(200,50,200),1.5));
                snapMarkerText->setText(QStringLiteral("\u22a5"));
                snapMarkerText->setBrush(QColor(200,50,200));
                break;
            }
        }
        snapMarkerRect->setPos(pos);
        snapMarkerRect->setVisible(true);
        snapMarkerText->setPos(QPointF(pos.x() + S + 1, pos.y() - S - 1));
        snapMarkerText->setVisible(true);
    } else {
        if (snapMarkerRect) snapMarkerRect->setVisible(false);
        if (snapMarkerText) snapMarkerText->setVisible(false);
    }
}
