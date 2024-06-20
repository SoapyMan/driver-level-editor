#ifndef DRIVER_MODEL_VIEW_HPP
#define DRIVER_MODEL_VIEW_HPP

#include <QtOpenGL>
#include <QtWidgets>
#include <QtOpenGlWidgets>
#include "../TextureList.hpp"
#include "../../Driver_Routines/driver_levels.hpp"
#include "ModelRenderer.hpp"

class ModelView : public QOpenGLWidget
{
    Q_OBJECT

    public:
        ModelView(QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags(), DebugLogger* logger = NULL);
        ~ModelView();

        void setLevel(DriverLevel* lev);
        void setTextureProvider(TextureList* list);

    public slots:
        void setModelIndex(int idx);
        void setEventModelIndex(int idx);
        void viewEventModels(bool view);
        void loadSettings();
        void saveSettings();

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;
        void rebuildModelRenderer();

        DebugLogger dummy;
        DebugLogger* log;
        DriverLevel* level;
        TextureList* textures;
        ModelRenderer* render;
        ModelShaders* shaders;
        ModelMatrixHandler* matrixHandler;
        BasicCamera camera;

        int modelIndex;
        int eventModelIndex;
        bool viewingEvent;
        bool legacyRendering;
        QPointF lastPoint;
        double wheelSensitivity;
        double mouseSensitivity;
        double zoomSensitivity;

        QTimer timer;
};

class RenderOptionsWidget : public QWidget
{
    Q_OBJECT

    public:
        RenderOptionsWidget(QWidget* parent = 0);
};

#endif
