#include "headerfiles/dialog_settings.h"

#include "headerfiles/config_manager.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>

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
CommandPickingWidget::CommandPickingWidget(QString label, QString key, QWidget* parrent) :QWidget(parrent), m_key(key)
{
    ui = new Ui::DialogSettingsCommand;
    ui->setupUi(this);
    
    connect(ui->m_exeSelect, SIGNAL(clicked()), this, SLOT(onSelectExe()));
    connect(ui->m_applyButton, SIGNAL(clicked()), this, SLOT(onApply()));

    ui->m_cmdExplain->setText("Example: -u <span style=\"color:#aa0000;\">$0 $1</span> > <span style=\"color:#aa0000;\">$2</span><br>\
        <span style=\"color:#aa0000;\">$1 </span>- Full first input file directory<br>\
        <span style=\"color:#aa0000;\">$2 </span>- Full second input file directory<br>\
        <span style=\"color:#aa0000;\">$3 </span>- Full output file directory<br>\
        <span style=\"color:#aa0000;\">$F </span>- First input file name directory<br>\
        <span style=\"color:#aa0000;\">$S </span>- Second input file name directory<br>\
        <span style=\"color:#aa0000;\">$O </span>- Output file name directory\
        ");

    ui->m_exeLineEdit->setText(ConfigManager::getInstance().getQString(ConfigKeys::GeneratorKey + "/Executable"));
    ui->m_cmdCommand->setPlainText(ConfigManager::getInstance().getQString(ConfigKeys::GeneratorKey + "/Attributes"));

    this->show();
}

CommandPickingWidget::~CommandPickingWidget()
{
    delete ui;
}

void CommandPickingWidget::onSelectExe()
{
    QString dir = QFileDialog::getOpenFileName(this, "Select executable file", ui->m_exeLineEdit->text(), "");
    ui->m_exeLineEdit->setText(dir);
}
void CommandPickingWidget::onApply()
{
    ConfigManager::getInstance().setQString(ConfigKeys::GeneratorKey + "/Executable", ui->m_exeLineEdit->text());
    ConfigManager::getInstance().setQString(ConfigKeys::GeneratorKey + "/Attributes", ui->m_cmdCommand->toPlainText());
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
        emit fontChanged();
    }

}
////////////////////////////////////////////////////
BoolWidget::BoolWidget(QString label, QString key, QWidget* parrent) :QWidget(parrent), m_key(key)
{
    QHBoxLayout* container = new QHBoxLayout(this);
    container->setSpacing(5);
    container->setMargin(2);

    container->addWidget(new QLabel(label, this));
    m_Label = new QLabel(this);
    m_Label->setMinimumSize(QSize(64, 16));
    container->addWidget(m_Label);

    QCheckBox* box = new QCheckBox(label,this);
    connect(box, SIGNAL(stateChanged(int)), this, SLOT(StateChanged(int)));
    box->setChecked(ConfigManager::getInstance().getBool(m_key));
    container->addWidget(box);

    setLayout(container);
}

void BoolWidget::StateChanged(int state)
{
    ConfigManager::getInstance().setBool(m_key, state == Qt::CheckState::Checked);
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
void DialogSettings::createRow(QString label, QString key, SettingsModel::keyType type)
{
    switch (type)
    {
    case SettingsModel::keyType::Color:
        wdg->verticalLayout->addWidget(new ColorPickingWidget(label, key, this));
        break;
    case SettingsModel::keyType::Font:
    {
        FontPickingWidget * fontWidget = new FontPickingWidget("Font", key, this);
        connect(fontWidget, SIGNAL(fontChanged()), this, SIGNAL(fontChanged()));
        wdg->verticalLayout->addWidget(fontWidget);
    }
        break;
    case SettingsModel::keyType::DiffGenerator:
        wdg->verticalLayout->addWidget(new CommandPickingWidget(label, key, this));
        break;
    case SettingsModel::keyType::Bool:
        wdg->verticalLayout->addWidget(new BoolWidget(label, key, this));
        break;
    default:
        break;
    }
    
}

DialogSettings::DialogSettings(QWidget *parent)
    : QDialog(parent),
    m_model(this)
{
    setupUi(this);
    setWindowTitle("Settings");
    wdg = new Ui::DialogSettingsColor;
    wdg->setupUi(widget);
    //widget->hide();
    //wdg->Title->setObjectName("Title");
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
        SettingsModel::keyType Type = m_model.data(index, Qt::UserRole+1).value<SettingsModel::keyType>();
        QString title = item->text();
        wdg->verticalLayout->addWidget(new QLabel(title,this));
        for(QString var : keys)
        {
            createRow(var.split('/').last(), var, Type);
        }
        //widget->show();
        wdg->verticalLayout->addSpacerItem(new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding));
        widget->setLayout(wdg->verticalLayout);

    }
    else
    {
        //widget->hide();
    }
}
