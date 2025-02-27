#include <QtCore/QTimer>
#include <QtWidgets/QMenu>

#include "capworddialog.h"
#include "ui_capworddialog.h"
#include "VBookModel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Log.h"

// QDialog(owner) causes closing mainwindow when app resides at system tray. 
CapWordDialog::CapWordDialog(MainWindow *owner, bool autoclose, int inv):
    QDialog(NULL),
    ui(new Ui::CapWordDialog),
    m_bAutoClose(autoclose),
    m_autoCloseInterval(inv),
    m_owner(owner)
{
    ui->setupUi(this);
#ifdef WIN32
	setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
#else
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::Dialog);
#endif
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //move(QCursor::pos().x()+CWD_X_OFFSET, QCursor::pos().y()+CWD_Y_OFFSET);
    //qApp->installEventFilter(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(close()));
    m_timer->setSingleShot(true);
}

CapWordDialog::~CapWordDialog()
{
    m_timer->stop();
    close();
    delete ui;
}

void CapWordDialog::moveToCursor()
{
    move(QCursor::pos().x()+CWD_X_OFFSET, QCursor::pos().y()+CWD_Y_OFFSET);
}

void CapWordDialog::setDictItemList(DictItemList *itemList)
{
    //DictItemList* itemList = (DictItemList*) v;
    ui->textEdit->clear();

    QTextCursor cursor(ui->textEdit->textCursor());
    QTextCharFormat titleFormat;
    QTextCharFormat bodyFormat;
    QTextBlockFormat itemBlock;
    QString text;

    titleFormat.setFontWeight(QFont::DemiBold);
    //cursor.insertBlock();
    m_capword = QString::fromUtf8((*itemList)[0].word.c_str());
    text = m_capword;
    cursor.insertText(text, titleFormat);
    text = QString::fromUtf8((*itemList)[0].phonetic.c_str());
    text = text.trimmed();
    if (text != "") {
        cursor.insertBlock();
        text = text.replace('\n', "    ");
        cursor.insertText(text, titleFormat);
        cursor.insertBlock();
    }

    bodyFormat.setFontWeight(QFont::Light);
    cursor.insertBlock(itemBlock);
    text = QString::fromUtf8((*itemList)[0].expl.c_str());
    text = text.trimmed();
    cursor.insertText(text,bodyFormat);
    ui->textEdit->moveCursor(QTextCursor::Start);
    
    if (m_bAutoClose)
        m_timer->start(m_autoCloseInterval);

    delete itemList;
}

#if 0
void CapWordDialog::on_saveToolButton_clicked()
{
    QString word = m_capword;
    if (word != "") {
    }
}

void CapWordDialog::on_dictToolButton_clicked()
{
    close();
}
#endif

bool CapWordDialog::event(QEvent * event)
{
    switch (event->type()) {
    case QEvent::ActivationChange:
        if(QApplication::activeWindow() != this)
            close();
        break;

    case QEvent::Close:
        m_timer->stop();
        break;

    case QEvent::Enter:
        m_timer->stop();
        activateWindow();
        raise();
        break;

    case QEvent::Leave:
        if (m_bAutoClose)
            m_timer->start(m_autoCloseInterval);
        break;

    default:
        break;
    }
    return QWidget::event(event);
}

#if 0
bool CapWordDialog::eventFilter( QObject * watched, QEvent * event )
{
    //g_sysLog.e("event type2 %d\n", event->type());
    return false;
}
#endif
#if 0
void CapWordDialog::on_textEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = ui->textEdit->createStandardContextMenu();
    menu->addAction(tr("My Menu Item"));
    menu->exec(mapToGlobal(pos));
}
#endif

void CapWordDialog::on_addToVbToolButton_clicked()
{
    if (m_capword != ""  && m_owner->m_vbookModel->add(m_capword)) {
        m_owner->showToolTip(tr("Add to vocabulary book,success"));
    } else {
        m_owner->showToolTip(tr("Add to vocabulary book,failure"));
    }
}
