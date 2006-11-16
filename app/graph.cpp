#include <qmessagebox.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qcolor.h>
#include <qnamespace.h>
#include <QTimerEvent>
#include <qlistwidget.h>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QModelIndex>
#include <QComboBox>

#include "graph.h"
#include "agent.h"

#if 0
class PenWidthListBoxItem : public QListWidgetItem
{
public:
    PenWidthListBoxItem(uint w)
        : QListWidgetItem()
    {
        thewidth = w;
        setCustomHighlighting( TRUE );
    }

protected:
    virtual void paint( QPainter * );
    virtual int width( const QListWidget* ) const { return 65; }
    virtual int height( const QListWidget* ) const { return 18; }
    
private:
    uint thewidth;
};

class PenStyleListBoxItem : public QListWidgetItem
{
public:
    PenStyleListBoxItem(enum Qt::PenStyle s)
        : QListWidgetItem()
    {
        style = s;
        setCustomHighlighting( TRUE );
    }

protected:
    virtual void paint( QPainter * );
    virtual int width( const QListWidget* ) const { return 65; }
    virtual int height( const QListWidget* ) const { return 18; }
    
private:
    enum Qt::PenStyle style;
};
#endif

void ColorBoxDelegate::paint( QPainter * painter, 
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    QRect r = option.rect;

    if (option.state & QStyle::State_Selected) {
        painter->save();
        painter->setBrush(option.palette.highlight());
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
        painter->setPen(QPen(option.palette.highlightedText(), 0));
    }

    r.setRight(r.right() - 3);
    r.setLeft(r.left() + 3);
    r.setTop(r.top() + 3);
    r.setBottom(r.bottom() - 3);
    painter->fillRect( r, index.data().value<QColor>());

    if (option.state & QStyle::State_Selected)
        painter->restore();
}

#if 0 
#if 1 
    QComboBox* cb = ((QComboBox*)parent());

     QPainter painter_cb(cb);

     QStyleOptionFocusRect opt;
     opt.initFrom(cb);
     opt.backgroundColor = Qt::black;
//     painter->eraseRect( r );

     cb->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &opt, &painter_cb/*, cb*/);
#endif

void PenWidthListBoxItem::paint( QPainter *painter )
{
    // evil trick: find out whether we are painted onto our listbox
    bool in_list_box = listBox() && listBox()->viewport() == painter->device();
    QStyleOptionFocusRect f; 
    QRect r ( 0, 0, width( listBox() ), height( listBox() ) );
    if ( in_list_box && isSelected() )
        painter->eraseRect( r );
    QPen pen( Qt::black, thewidth);
    painter->setPen(pen);
    painter->drawLine ( 0, height(listBox())/2, width(listBox()), height(listBox())/2);    
    if ( in_list_box && isCurrent() )
        listBox()->style()->drawPrimitive( QStyle::PE_FrameFocusRect, &f, painter);
}

void PenStyleListBoxItem::paint( QPainter *painter )
{
    // evil trick: find out whether we are painted onto our listbox
    bool in_list_box = listBox() && listBox()->viewport() == painter->device();
    QStyleOptionFocusRect f; 
    QRect r ( 0, 0, width( listBox() ), height( listBox() ) );
    if ( in_list_box && isSelected() )
        painter->eraseRect( r );
    QPen pen( Qt::black, 2, style);
    painter->setPen(pen);
    painter->drawLine ( 0, height(listBox())/2, width(listBox()), height(listBox())/2);    
    if ( in_list_box && isCurrent() )
        listBox()->style()->drawPrimitive( QStyle::PE_FrameFocusRect, &f, painter);
}
#endif

GraphItem::GraphItem(QString name, QTabWidget* tab):QwtPlot(name)
{
    Tab = tab;
    Tab->addTab(this, name);
    dataCount = 0;
    timerID = 0;
    
    for ( int i = 0; i < PLOT_HISTORY; i++ )
        timeData[i] = i;

    // Zero all curve structures
    for( int j = 0; j < NUM_PLOT_PER_GRAPH; j++)
    {
#if 0 //TODO
        curves[j].key = 0;
#endif
        memset(curves[j].data, 0, sizeof(double)*PLOT_HISTORY);
    }
}

GraphItem::~GraphItem()
{
    if (Tab && (Tab->indexOf(this) != -1))
        Tab->removeTab(Tab->indexOf(this));
}

void GraphItem::AddCurve(QString name, QPen& pen)
{
    int i = 0;
    
    for (i=0; i<NUM_PLOT_PER_GRAPH; i++)
    {
#if 0 //TODO
        if (curves[i].key && (curves[i].name == name))
            return;
        else if (curves[i].key == 0)
            break;
#endif
    }
    
    if (i >= NUM_PLOT_PER_GRAPH)
        return;
#if 0 //TODO
    curves[i].key = insertCurve(name);
    curves[i].name = name;
    setCurvePen(curves[i].key, pen);
#endif 
    if (!timerID)
        timerID = startTimer(1000); // 1 second
    
    replot();
}

void GraphItem::RemoveCurve(QString name)
{
    /* No other curve left, kill the timer first ... */
    if (timerID && ((/*TODO*/1-1) == 0))
    {
        killTimer(timerID);
        timerID = 0;
    }

#if 0 //TODO
      
    for (int i=0; i<NUM_PLOT_PER_GRAPH; i++)
    {
        if (curves[i].key && (curves[i].name == name))
        {
            curves[i].key = 0;
            return;
        }
        else if (curves[i].key == 0)
            return;
    }
#endif
}

void GraphItem::timerEvent(QTimerEvent *)
{
    if ( dataCount < PLOT_HISTORY )
    {
        dataCount++;
    }
    else
    {
        /* Time shift of 1 sec */
        for ( int j = 0; j < PLOT_HISTORY; j++ )
            timeData[j]++;
        
        for ( int i = 0; i < PLOT_HISTORY - 1; i++ )
        {
            for ( int c = 0; c < 1; c++ )
            {
                curves[c].data[i] = curves[c].data[i+1];
            }
        }    
    }
    
    /* Set the data */
    curves[0].data[dataCount-1] = CurrentAgent->GetSyncValue(curves[0].name);
    
    setAxisScale(QwtPlot::xBottom,
        timeData[PLOT_HISTORY - 1], timeData[0]);
#if 0 //TODO
    for ( int c = 0; c < 1/* TODO */; c++ )
    {
        setCurveRawData(curves[c].key,
            timeData, curves[c].data, dataCount);
    }
#endif
    replot();
}

Graph::Graph(QTabWidget* GT, QPushButton* GC, QPushButton* GD,
             QComboBox* GN, QComboBox* PO, QPushButton* PA,
             QPushButton* PD, QComboBox* PI, QComboBox* PC,
             QComboBox* PS, QComboBox* PW, BasicMibView* PM)
{
    GraphTab = GT;
    GraphCreate = GC;
    GraphDelete = GD;
    GraphName = GN;
    PlotObject = PO;
    PlotAdd = PA;
    PlotDelete = PD;
    PlotIndex = PI;
    PlotColor = PC;
    PlotShape = PS;
    PlotWidth = PW;
    PlotMIBTree = PM;
    
    // Connect some signals
    connect( GC, SIGNAL( clicked() ), this, SLOT( CreateGraph() ));
    connect( GD, SIGNAL( clicked() ), this, SLOT( DeleteGraph() ));
    connect( PA, SIGNAL( clicked() ), this, SLOT( CreatePlot() ));
    connect( PD, SIGNAL( clicked() ), this, SLOT( DeletePlot() ));    
    connect( PM, SIGNAL( SelectedOid(const QString&) ), 
             this, SLOT( SetObjectString(const QString&) ));

    // Fill the color combobox ...
    ColorModel = new QStandardItemModel(17, 1);
    PC->setModel(ColorModel);
    ColorDelegate = new ColorBoxDelegate(PC);
    PC->setItemDelegate(ColorDelegate);

    for (int row = 0; row < 17; row++)
    {
        QModelIndex index = ColorModel->index(row, 0, QModelIndex());
        switch (row)
        {
            case 0: ColorModel->setData(index, QVariant(Qt::black)); break;
            case 1: ColorModel->setData(index, QVariant(Qt::white)); break;
            case 2: ColorModel->setData(index, QVariant(Qt::darkGray)); break;
            case 3: ColorModel->setData(index, QVariant(Qt::gray)); break;
            case 4: ColorModel->setData(index, QVariant(Qt::lightGray)); break;
            case 5: ColorModel->setData(index, QVariant(Qt::red)); break;
            case 6: ColorModel->setData(index, QVariant(Qt::green)); break;
            case 7: ColorModel->setData(index, QVariant(Qt::blue)); break;
            case 8: ColorModel->setData(index, QVariant(Qt::cyan)); break;
            case 9: ColorModel->setData(index, QVariant(Qt::magenta)); break;            
            case 10: ColorModel->setData(index, QVariant(Qt::yellow)); break;
            case 11: ColorModel->setData(index, QVariant(Qt::darkRed)); break;
            case 12: ColorModel->setData(index, QVariant(Qt::darkGreen)); break;
            case 13: ColorModel->setData(index, QVariant(Qt::darkBlue)); break;
            case 14: ColorModel->setData(index, QVariant(Qt::darkCyan)); break;
            case 15: ColorModel->setData(index, QVariant(Qt::darkMagenta)); break;
            case 16: ColorModel->setData(index, QVariant(Qt::darkYellow)); break;
            default: break;
        }
    }

#if 0 // TODO  
    // Fill the pen width combobox ...
    PlotWidth->listBox()->insertItem( new PenWidthListBoxItem(1) );
    PlotWidth->listBox()->insertItem( new PenWidthListBoxItem(2) );
    PlotWidth->listBox()->insertItem( new PenWidthListBoxItem(3) );
    PlotWidth->listBox()->insertItem( new PenWidthListBoxItem(4) );
    PlotWidth->listBox()->insertItem( new PenWidthListBoxItem(5) );
    
    // Fill the pen shape combobox ...
    PlotShape->listBox()->insertItem( new PenStyleListBoxItem(Qt::SolidLine) );
    PlotShape->listBox()->insertItem( new PenStyleListBoxItem(Qt::DashLine) );
    PlotShape->listBox()->insertItem( new PenStyleListBoxItem(Qt::DotLine) );
    PlotShape->listBox()->insertItem( new PenStyleListBoxItem(Qt::DashDotLine) );
    PlotShape->listBox()->insertItem( new PenStyleListBoxItem(Qt::DashDotDotLine) );
#endif
}

void Graph::CreateGraph(void)
{
    if (!GraphName->currentText().isEmpty())
    {        
        GraphItem *GI;
        for (int i = 0; i < Items.count(); i++)
        {
            GI = Items[i];
            if (GI->title().text() == GraphName->currentText())
            {
                QString err = QString("Graph \"%1\" already exist !")
                      .arg(GraphName->currentText());
                QMessageBox::information ( NULL, "Graph", err, 
                             QMessageBox::Ok, Qt::NoButton);
                return;
            }
        }
                
        GI = new GraphItem(GraphName->currentText(), GraphTab);
        Items.append(GI);
    }
}

void Graph::DeleteGraph(void)
{
    if (!GraphName->currentText().isEmpty())
    {
        GraphItem *GI;
        for (int i = 0; i < Items.count(); i++)
        {
            GI = Items[i];
            if (GI->title().text() == GraphName->currentText())
            {
                Items.removeAll(GI);
                delete GI;
                return;
            }
        }
    }
}

void Graph::CreatePlot(void)
{
    if (!PlotObject->currentText().isEmpty())
    {
        QPen p;
     
        switch (PlotColor->currentIndex())
        {
        case 0: p.setColor(Qt::black); break;
        case 1: p.setColor(Qt::white); break;
        case 2: p.setColor(Qt::darkGray); break;
        case 3: p.setColor(Qt::gray); break;
        case 4: p.setColor(Qt::lightGray); break;
        case 5: p.setColor(Qt::red); break;
        case 6: p.setColor(Qt::green); break;
        case 7: p.setColor(Qt::blue); break;
        case 8: p.setColor(Qt::cyan); break;
        case 9: p.setColor(Qt::magenta); break;            
        case 10: p.setColor(Qt::yellow); break;
        case 11: p.setColor(Qt::darkRed); break;
        case 12: p.setColor(Qt::darkGreen); break;
        case 13: p.setColor(Qt::darkBlue); break;
        case 14: p.setColor(Qt::darkCyan); break;
        case 15: p.setColor(Qt::darkMagenta); break;
        case 16: p.setColor(Qt::darkYellow); break;
        default: break;
        }
        
        p.setWidth(PlotWidth->currentIndex()+1);
        
        switch (PlotShape->currentIndex())
        {
        case 0: p.setStyle(Qt::SolidLine); break;
        case 1: p.setStyle(Qt::DashLine); break;
        case 2: p.setStyle(Qt::DotLine); break;
        case 3: p.setStyle(Qt::DashDotLine); break;
        case 4: p.setStyle(Qt::DashDotDotLine); break;
        default: break;
        }

        printf("Creating plot %s\n", PlotObject->currentText().toLatin1().data());
        
        if (!GraphName->currentText().isEmpty())
        {
            GraphItem *GI = NULL;
            for (int i = 0; i < Items.count(); i++)
            {
                GI = Items[i];
                if (GI->title().text() == GraphName->currentText())
                    break;
            }
            if (GI)
                GI->AddCurve(PlotObject->currentText(), p);
        }
    }
}

void Graph::DeletePlot(void)
{
    if (!PlotObject->currentText().isEmpty())
    {
        printf("Deleting plot %s\n", PlotObject->currentText().toLatin1().data());
        
        if (!GraphName->currentText().isEmpty())
        {
            GraphItem *GI = NULL;
            for (int i = 0; i < Items.count(); i++)
            {
                GI = Items[i];
                if (GI->title().text() == GraphName->currentText())
                    break;
            }
            if (GI) 
                GI->RemoveCurve(PlotObject->currentText());
        }
    }
}

void Graph::SetObjectString(const QString& oid)
{
    PlotObject->insertItem(0, oid);
    PlotObject->setCurrentIndex(0);
}

