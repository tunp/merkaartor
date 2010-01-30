#ifndef MERKATOR_LAYERWIDGET_H_
#define MERKATOR_LAYERWIDGET_H_

#include "Layer.h"
#include "ImageMapLayer.h"

#include <QActionGroup>
#include <QAbstractButton>

class MainWindow;
class Layer;

class LayerWidget : public QAbstractButton
{
	Q_OBJECT

		friend class LayerDock;

	public:
		LayerWidget(Layer* aLayer, QWidget* aParent = 0);
		virtual ~LayerWidget();

		virtual QSize sizeHint () const;
		virtual QSize minimumSizeHint () const;

		virtual Layer* getMapLayer();
		virtual void setLayerVisible(bool b);
		virtual void setLayerReadonly(bool b);
		virtual	void initActions();

		QMenu* getAssociatedMenu();

	protected:
		virtual void showContextMenu(QContextMenuEvent* anEvent);

		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent* anEvent);

		virtual void paintEvent(QPaintEvent* anEvent);
		virtual void checkStateSet();
		virtual void nextCheckState();

		QPointer<Layer> theLayer;
		QPixmap visibleIcon;
		QPixmap hiddenIcon;
		QBrush backColor;
		QMenu* ctxMenu;
		QAction* closeAction;
		QAction* actZoom;
		QAction* actVisible;
		QAction* actReadonly;
		QMenu* associatedMenu;
		QPoint dragStartPosition;

	signals:
		void layerSelected(LayerWidget *);
		void layerChanged(LayerWidget *, bool adjustViewport);
		void layerClosed(Layer *);
		void layerCleared(Layer *);
		void layerZoom(Layer *);

	protected slots:
		void setOpacity(QAction*);
		void zoomLayer(bool);
		void visibleLayer(bool);
		void readonlyLayer(bool);
		void close();
		void clear();
		void associatedAboutToShow();
};

class DrawingLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		DrawingLayerWidget(DrawingLayer* aLayer, QWidget* aParent = 0);
		virtual ~DrawingLayerWidget() {};

	public:
		virtual void initActions();

	private:
		//DrawingMapLayer* theLayer;
};

class TrackLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		TrackLayerWidget(TrackLayer* aLayer, QWidget* aParent = 0);
		virtual ~TrackLayerWidget();

	public:
		virtual void initActions();

	private slots:
		void extractLayer(bool);
};

class ImageLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		ImageLayerWidget(ImageMapLayer* aLayer, QWidget* aParent = 0);
		virtual ~ImageLayerWidget();

	public:
		virtual void initActions();

	private:
		QAction* actShape;
		QAction* actNone;
		QMenu* wmsMenu;
		QMenu* tmsMenu;

	private slots:
		void setWms(QAction*);
		void setTms(QAction*);
		void setOther(QAction*);

		void setBackground(QAction*);
};

class DirtyLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		DirtyLayerWidget(DirtyLayer* aLayer, QWidget* aParent = 0);
		virtual ~DirtyLayerWidget() {};

	public:
		virtual void initActions();
};

class UploadedLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		UploadedLayerWidget(UploadedLayer* aLayer, QWidget* aParent = 0);
		virtual ~UploadedLayerWidget() {};

	public:
		virtual void initActions();
};

class OsbLayerWidget : public LayerWidget
{
	Q_OBJECT

	public:
		OsbLayerWidget(OsbLayer* aLayer, QWidget* aParent = 0);
		virtual ~OsbLayerWidget() {};

	public:
		virtual void initActions();
};


#endif

