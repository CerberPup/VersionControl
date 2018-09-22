#include "headerfiles/dialog_settings.h"

#include "GeneratedFiles/ui_dialog_settings_color.h"
#include "headerfiles/config_manager.h"

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcolordialog.h>
#include <QtWidgets/QFontDialog>

namespace {
    void clearLayout(QLayout *layout)
    {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0) {
            if (child->layout() != 0)
                clearLayout(child->layout());
            else if (child->widget() != 0)
                delete child->widget();

            delete child;
        }
    }
}
//////////////////////////////////////////
FontPickingWidget::FontPickingWidget(QString label, QString key, QWidget* parrent) :QWidget(parrent), m_key(key)
{
    QHBoxLayout* container = new QHBoxLayout(this);
    container->setSpacing(5);
    container->setMargin(2);

    container->addWidget(new QLabel(label, this));
    m_fontLabel = new QLabel(this);
    m_fontLabel->setMinimumSize(QSize(64, 16));
    container->addWidget(m_fontLabel);

    QPushButton* button = new QPushButton("...", this);
    button->setFixedSize(24, 18);
    connect(button, SIGNAL(clicked()), this, SLOT(onFontChoose()));
    container->addWidget(button);

    setLayout(container);
}

void FontPickingWidget::onFontChoose()
{
    QFont font = ConfigManager::getInstance().getQFont(m_key);
    QFontDialog dialog(font, this);
    if (dialog.exec())
    {
        ConfigManager::getInstance().setQFont(m_key, dialog.selectedFont());
        QApplication::setFont(dialog.selectedFont());
        m_fontLabel->setFont(dialog.selectedFont());
    }

}
////////////////////////////////////////////////////
ColorPickingWidget::ColorPickingWidget(QString label, QString key, QWidget* parrent):QWidget(parrent), m_key(key)
{
    QHBoxLayout* container = new QHBoxLayout(this);
    container->setSpacing(5);
    container->setMargin(2);

    container->addWidget(new QLabel(label, this));
    QPixmap pix(64, 16);
    pix.fill(ConfigManager::getInstance().getQColor(key));
    m_colorLabel = new QLabel(this);
    m_colorLabel->setPixmap(pix);
    container->addWidget(m_colorLabel);

    QPushButton* button = new QPushButton("...", this);
    button->setFixedSize(24, 18);
    connect(button, SIGNAL(clicked()), this, SLOT(onColorChoose()));
    container->addWidget(button);

    setLayout(container);
}

void ColorPickingWidget::onColorChoose()
{
    QColor color = ConfigManager::getInstance().getQColor(m_key);
    QColorDialog dialog(color,this);
    if (dialog.exec())
    {
        ConfigManager::getInstance().setQColor(m_key, dialog.selectedColor());
        QPixmap pix(64, 16);
        pix.fill(dialog.selectedColor());
        m_colorLabel->setPixmap(pix);
    }

}
//////////////////////////////////////////////////
void DialogSettings::createColorRow(QString label, QString key)
{
    wdg->verticalLayout->addWidget(new ColorPickingWidget(label, key, this));
}

void DialogSettings::createFontRow(QString label, QString key)
{
    wdg->verticalLayout->addWidget(new FontPickingWidget(label, key, this));
}

DialogSettings::DialogSettings(QWidget *parent)
    : QDialog(parent),
    m_model(this)
{
    setupUi(this);
    setWindowTitle("Settings");
    wdg = new Ui::DialogSettingsColor;
    wdg->setupUi(widget);
    widget->hide();
    wdg->Title->setObjectName("Title");
    treeView->setModel(&m_model);

    connect(treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onSelectedItem(const QModelIndex &)));
}

DialogSettings::~DialogSettings()
{
}

void DialogSettings::onSelectedItem(const QModelIndex &index)
{
    QStandardItem* item = m_model.itemFromIndex(index);
    if (!item->hasChildren())
    {
        clearLayout(wdg->verticalLayout);
        QStringList keys = m_model.data(index, Qt::UserRole).toStringList();
        QString title = item->text();
        wdg->verticalLayout->addWidget(new QLabel(title,this));
        for each (QString var in keys)
        {
            if (var.split('/').last() == "Font")
            {
                createFontRow("Font", var);
            }
            else
            {
                createColorRow(var.split('/').last(), var);
            }
        }
        widget->show();

        
    }
    else
    {
        widget->hide();
    }
}