#ifndef TEXTURE_VIEW_HPP
#define TEXTURE_VIEW_HPP

#include <QtWidgets>
#include <QtOpenGlWidgets>
#include <vector>
#include "../TextureList.hpp"
#include "../../Driver_Routines/driver_levels.hpp"

class TextureViewGL : public QOpenGLWidget, IDriverTextureEvents
{
    Q_OBJECT

    private:
        class TexturePositioner
        {
            public:
                TexturePositioner();

                void setTextureIndex(int idx);
                void setPaletteIndex(int idx);
                void setPosition(int x, int y, int gridX = -1, int gridY = -1);
                void setTargetPosition(int x, int y, int gridX, int gridY, int currentTime);
                void setTransitionTime(int start, int end);

                int getTextureIndex() const;
                int getPaletteIndex() const;
                bool highlightEnabled() const;
                int getXPosition(int msecTime) const;
                int getYPosition(int msecTime) const;
                int getGridX() const;
                int getGridY() const;

            protected:
                int startX, startY;
                int endX, endY;
                int gridX, gridY;
                int startTime, endTime;
                int textureIndex;
                int paletteIndex;
        };

    public:
        TextureViewGL(QWidget* parent = NULL, Qt::WindowFlags f = Qt::WindowFlags());
        ~TextureViewGL();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;

        void setTextureData(DriverTextures* newTexData);
        void setGLTextureProvider(TextureList* newTexList);

        void setTextureHidden(int idx, bool hidden, bool refresh = true);
        void setTextureColor(int idx, unsigned char r, unsigned char b, unsigned char g);
        void enableTextureHighlight(int idx, bool enabled);
        void setDisplacement(int x, int y);

        int getSelectedTexture() const;
        int getSelectedPalette() const;
        bool textureAt(const QPoint& point, int* texture, int* palette) const;
        int getVerticalScrollStep();
        int getHorizontalScrollStep();
        QSize getVirtualDimensions();
        QRect getSelectionRect();

        void texturesDestroyed();
        void texturesReset(bool aboutToBe);
        void texturesOpened();
        void textureRemoved(int idx);
        void textureChanged(int idx);
        void textureInserted(int idx);
        void textureMoved(int from, int to);

    public slots:
        void setSelectedTexture(int idx);
        void setSelectedPalette(int idx);
        void setTextureSize(int size);
        void setViewMode(int mode);

    signals:
        void textureSelectionChanged(int s);
        void paletteSelectionChanged(int s);
        void sizeHasChanged();

    protected slots:
        void checkTimer();

    protected:
        void setup();
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void findSelectedPositioner();
        void drawPositioner(int i, int currentTime);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void resizeEvent(QResizeEvent* event);

        void drawTexture(int x, int y, GLuint texture);
        void drawHighlight(int x, int y, unsigned char r, unsigned char g, unsigned char b);
        int getMilliseconds();
        void rebuildView();

        int textureSize;
        int viewMode;
        int selectedTexture, selectedPalette;
        int selectedPositioner;
        int heldPositioner;
        int heldPositionX;
        int heldPositionY;
        int lastGridX, lastGridY;
        int lastTransition;
        int xDisplacement, yDisplacement;
        QTime timeKeeper;
        QTimer timer;
        DriverTextures* textures;
        TextureList* textureList;
        bool textureHidden[256];
        int textureColors[256];
        vector<TexturePositioner> texturePositions;
};

class TextureView : public QAbstractScrollArea
{
    Q_OBJECT

    public:
        TextureView(QWidget* parent = NULL, Qt::WindowFlags f = Qt::WindowFlags());
        ~TextureView();
        void setup();

        void setTextureData(DriverTextures* newTexData);
        void setGLTextureProvider(TextureList* newTexList);

        TextureViewGL* viewer();
        bool textureAt(const QPoint& point, int* texture, int* palette) const;

    public slots:
        void reconfigureScrollbars();
        void ensureSelectionVisible();
        void setSelectedTexture(int idx);
        void setSelectedPalette(int idx);
        void setLocked(bool lock);

    protected:
        void scrollContentsBy(int dx, int dy);
        void updateStep();
        void updateViewerPosition();
        void wheelEvent(QWheelEvent* event);

        TextureViewGL* glView;
        QWidget* viewportWidget;
        bool locked;
};

#endif
