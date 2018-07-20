#ifndef ppdesktop_clickablelabel_h_included
#define ppdesktop_clickablelabel_h_included

#include <QLabel>
#include <QMouseEvent>
#include <QObject>

/**
 * @brief A label that emits a `clicked` signal when there is a mouse click
 */
class ClickableLabel : public QLabel
{

    Q_OBJECT

    public:

    /**
     * @brief Trivial constructor
     *
     * @param parent The (optional) parent widget of the label
     */
    explicit ClickableLabel(QWidget* parent = nullptr);

    /**
     * @brief Trivial destructor
     */
    virtual ~ClickableLabel(void) {}

    signals:

    /**
     * @brief Signal that the mouse was clicked on the label
     *
     * @param x The x-coordinate
     *
     * @param y The y-coordinate
     *
     * @todo Add other parameters for the mouse click, like left or right
     * mouse button, and whether additional keys were held down
     */
    void clicked(int x, int y);

    protected:

    /**
     * @brief Emit the `clicked` event when the mouse is clicked on the label
     *
     * @param mouseEvent The event structure for the mouse click
     */
    void mousePressEvent(QMouseEvent* mouseEvent) override
    {
        emit clicked(mouseEvent->x(), mouseEvent->y());
    }

};  // end ClickableLabel class

#endif // ppdesktop_clickablelabel_h_included
