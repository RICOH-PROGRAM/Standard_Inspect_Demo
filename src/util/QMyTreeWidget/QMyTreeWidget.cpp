#include "QMyTreeWidget.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <fstream>
#include <QHeaderView>
#include <QFontDialog>
#include <QScrollBar>
#define SLIDERSTYLE "  \
     QSlider::add-page:Horizontal\
     {     \
        background-color: rgb(87, 97, 106);\
        height:4px;\
     }\
     QSlider::sub-page:Horizontal \
    {\
        background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(7,208,255, 255), stop:1 rgba(7,208,255, 255));\
        height:4px;\
     }\
    QSlider::groove:Horizontal \
    {\
        background:transparent;\
        height:6px;\
    }\
    QSlider::handle:Horizontal \
    {\
        height: 25px;\
        width:35px;\
        border-image: url(./btn.png);\
        margin: -15 0px; \
    }\
    "
QMyTreeWidget::QMyTreeWidget(QWidget* parent)
	: QTreeWidget(parent)
{
	QObject::connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(showCnDetail(QTreeWidgetItem*, int)));

	this->setStyleSheet("QTreeWidget::item{height:60px;}\
	QTreeView::branch:has-children:!has-siblings:closed,\
		QTreeView::branch:closed:has-children:has-siblings\
		{\
			padding: -3px;\
			image:url(./340.png);\
		}\
		QTreeView::branch:open:has-children:!has-siblings,\
			QTreeView::branch:open:has-children:has-siblings\
		{\
			padding: -3px;\
			image:url(./440.png);\
		}");

	this->verticalScrollBar()->setStyleSheet("QScrollBar{background:White; width: 40px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	this->setFont(QFont(QString::fromLocal8Bit("宋体"), 20));
}
enum MyEnum
{
	SCALAR = 0,
};

bool QMyTreeWidget::LoadYAMLFile(YAML::Node params)
{
	this->clear();
	this->setHeaderHidden(false);
	this->setColumnCount(4);
	QStringList strList;
	strList << QStringLiteral("属性") << QStringLiteral("值") << QStringLiteral("V1") << QStringLiteral("V2");

	setHeaderLabels(strList);
	//this->header()->hideSection(3);
	this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);//均分填充表头
	_mparam = params;
	try
	{
		if (_mparam.IsNull())
		{
			return false;
		}
		int n;
		for (YAML::iterator it = _mparam.begin(); it != _mparam.end(); it++)
		{
			std::string name = it->first.as<std::string>();
			if (_mparam[name].IsDefined())
			{
				if (name.find("Param_") != std::string::npos)
				{
					QTreeWidgetItem* pItemError = new QTreeWidgetItem(QStringList() << name.c_str());
					this->addTopLevelItem(pItemError);
					//if (_mparam[name].IsSequence())
					{
						YAML::Node commands = _mparam[name];
	
						for (YAML::const_iterator it = commands.begin(); it != commands.end(); ++it)
						{
							std::string key = it->first.as<std::string>();       // <- key
							if (key == "Checkable")
							{
								//if (command.begin()->first.as<std::string>() == "ability")
								{
									QCheckBox* checkbox = new QCheckBox;
									checkbox->setObjectName(QString(name.c_str()) + "+" + key.c_str());
	
									checkbox->setStyleSheet("QCheckBox{ background:transparent}\
                            QCheckBox::indicator {width: 40px; height: 40px; }\
                            QCheckBox::indicator:unchecked{background:url(./240.png)}\
                            QCheckBox::indicator:checked{background:url(./540.png)}");
	
									//	/*               QCheckBox::indicator:unchecked{background:url(:/Qt_Test/240.png)}\
									//				   QCheckBox::indicator:checked{background:url(:/Qt_Test/140.png)}");
						   //*/
									YAML::ERRORSetting ty = it->second.as<YAML::ERRORSetting>();
									if (it->second["value"].as<int>() == 0)
										checkbox->setChecked(false);
									else
										checkbox->setChecked(true);
									if (it->second["ability"].as<int>() == 0)
									{
										checkbox->setEnabled(false);
										checkbox->setStyleSheet("QCheckBox{ background:transparent}\
                            QCheckBox::indicator {width: 40px; height: 40px; }\
                            QCheckBox::indicator:unchecked{background:url(./240.png)}\
                            QCheckBox::indicator:checked{background:url(./540.png)}");
									}
									else {
										checkbox->setStyleSheet("QCheckBox{ background:transparent}\
                            QCheckBox::indicator {width: 40px; height: 40px; }\
                            QCheckBox::indicator:unchecked{background:url(./240.png)}\
                            QCheckBox::indicator:checked{background:url(./140.png)}");
									}
									this->setItemWidget(pItemError, 1, checkbox);
	
									QObject::connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(CheckValueChanged(int)));
								}
							}
							else
							{
								QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList() << key.c_str());
								pItemError->addChild(pItem);
								YAML::CharacterType ty = it->second.as<YAML::CharacterType>();
								if (ty.type == "Scale")
								{
									QMySlider* control = new QMySlider(Qt::Horizontal);
									control->setObjectName(QString(name.c_str()) + "+" + key.c_str());
									control->setMinimum(ty.Smallest);
									control->setMaximum(ty.Biggest);
									control->setValue(ty.value);
	
									control->setStyleSheet(SLIDERSTYLE);
									// 									QLineEdit* le = new QLineEdit();
									// 									le->setObjectName("le" + QString(name.c_str()) + "+" + key.c_str());
									// 									le->setText(QString::number(ty.value));
									// 									le->setEnabled(false);
	
									pItem->setData(1, Qt::DisplayRole, ty.value);
									pItem->setData(3, Qt::DisplayRole, ty.CN_Discrib);
									this->setItemWidget(pItem, 2, control);
	
									QObject::connect(control, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
								}
								if (ty.type == "Combo")
								{
									QComboBox* qcb = new QComboBox();
									qcb->setObjectName(QString(name.c_str()) + "+" + key.c_str());
									qcb->addItems(QStringList() << "R" << "G" << "B" << "H" << "S" << "V");
									qcb->setCurrentIndex(ty.value);
									pItem->setData(1, Qt::DisplayRole, ty.value);
									pItem->setData(3, Qt::DisplayRole, ty.CN_Discrib);
									this->setItemWidget(pItem, 2, qcb);
									QObject::connect(qcb, SIGNAL(activated(int)), this, SLOT(ComboValueChanged(int)));
								}
	
								if (ty.type == "Button")
								{
									QPushButton* qpb = new QPushButton();
									qpb->setObjectName(QString(name.c_str()) + "+" + key.c_str());
									qpb->setText((ty.CN_Name));
									pItem->setData(1, Qt::DisplayRole, ty.value);
									pItem->setData(3, Qt::DisplayRole, ty.CN_Discrib);
									this->setItemWidget(pItem, 2, qpb);
									QObject::connect(qpb, SIGNAL(released()), this, SLOT(ClickPushButton()));
								}
								if (ty.type == "Edit")
								{
									QLineEdit* qte = new QLineEdit();
									QRegExp rx = QRegExp("[\40]*");
									QRegExpValidator* validator = new QRegExpValidator(rx);
									qte->setValidator(validator);
									qte->setObjectName(QString(name.c_str()) + "+" + key.c_str());
									qte->setText(QString::number(ty.value));
									qte->setAlignment(Qt::AlignCenter);
									//qte->setFixedHeight(size().height());
									pItem->setData(1, Qt::DisplayRole, ty.value);
									pItem->setData(3, Qt::DisplayRole, ty.CN_Discrib);
									this->setItemWidget(pItem, 2, qte);
									QObject::connect(qte, SIGNAL(textChanged(QString)), this, SLOT(LineValueChanged(QString)));
								}
							}
						}
					}
				}
			}
		}
	}
	catch (YAML::ParserException e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	catch (YAML::RepresentationException e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	catch (YAML::Exception e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	return false;
}

void QMyTreeWidget::expandbyString()
{
	QList<QTreeWidgetItem*> alternateItems = this->findItems(m_ErrorNode, Qt::MatchContains | Qt::MatchRecursive);
	if (alternateItems.size() != 0) alternateItems[0]->setExpanded(true);
}
bool QMyTreeWidget::SaveYAMLFile(QString filepath)
{
	std::ofstream fout(filepath.toStdString().c_str());

	try
	{
		fout << _mparam;

		fout.close();
	}
	catch (YAML::ParserException e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	catch (YAML::RepresentationException e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	catch (YAML::Exception e)
	{
		QMessageBox::warning(nullptr, "", e.what());
	}
	return false;
}

void QMyTreeWidget::ComboValueChanged(int i)
{
	QComboBox* sind = qobject_cast<QComboBox*>(QObject::sender());
	QString objectname = sind->objectName();
	QString errtype = objectname.left(objectname.indexOf("+"));
	QString errname = objectname.mid(objectname.indexOf("+") + 1);
	_mparam[errtype.toStdString().c_str()][errname.toStdString().c_str()]["value"] = i;
	QTreeWidgetItem* cur = this->currentItem();
	cur->setData(1, Qt::DisplayRole, i);
	emit TempSave(objectname, QString::number(i));
}
void QMyTreeWidget::LineValueChanged(QString str)
{
	QLineEdit* sind = qobject_cast<QLineEdit*>(QObject::sender());
	if (str == "")
	{
		sind->setText("0");
		return;
	}
	QString objectname = sind->objectName();
	QString errtype = objectname.left(objectname.indexOf("+"));
	QString errname = objectname.mid(objectname.indexOf("+") + 1);
	_mparam[errtype.toStdString().c_str()][errname.toStdString().c_str()]["value"] = str.toDouble();
	//if (sind->text()=="")
	//{
	//	sind->setText("");
	//}
	QTreeWidgetItem* cur = this->currentItem();
	cur->setData(1, Qt::DisplayRole, str);
	emit TempSave(objectname, str);
}

void QMyTreeWidget::CheckValueChanged(int i)
{
	QCheckBox* sind = qobject_cast<QCheckBox*>(QObject::sender());
	QString objectname = sind->objectName();
	QString errtype = objectname.left(objectname.indexOf("+"));
	QString errname = objectname.mid(objectname.indexOf("+") + 1);
	_mparam[errtype.toStdString().c_str()][errname.toStdString().c_str()]["value"] = i;
}

void QMyTreeWidget::ClickPushButton()
{
	QPushButton* sind = qobject_cast<QPushButton*>(QObject::sender());
	QString objectname = sind->objectName();
	QString errtype = objectname.left(objectname.indexOf("+"));
	QString errname = objectname.mid(objectname.indexOf("+") + 1);
	m_ErrorNode = errtype;
	emit Signal_DrawRegion(objectname);
}

void QMyTreeWidget::showCnDetail(QTreeWidgetItem* pItem, int i)
{
	if (i != 2)
	{
		QString sts = pItem->data(3, Qt::DisplayRole).toString();
		if (sts.length() == 0)
		{
			return;
		}
		QPoint pt = cursor().pos();
		if (detailtext != nullptr)
		{
			delete detailtext;
			detailtext = nullptr;
		}
		detailtext = new QMyTextEdit(this);
		pt = this->mapFromGlobal(pt);
		//detailtext->setGeometry(pt.x(), pt.y(), 100, 50);
		detailtext->move(pt.x(), pt.y());
		detailtext->setStyleSheet("font-size:14pt");
		detailtext->topLevelWidget();
		detailtext->setWindowFlag(Qt::FramelessWindowHint);
		detailtext->show();

		//connect(detailtext->document(), SIGNAL(contentsChanged()), this, SLOT(textAreaChanged()));
		QString str = pItem->data(3, Qt::DisplayRole).toString();
		detailtext->setText(str);
		//detailtext->setFixedSize(1000, 100);

		int w = str.length();
		QFontMetrics fm = detailtext->fontMetrics();
		int width = fm.boundingRect(str).width() + 20;
		if (width > 400)
		{
			detailtext->resize(300, (fm.boundingRect(str).height() + 20) * (width / 300 + 1));
		}
		else
		{
			detailtext->resize(width, fm.boundingRect(str).height() + 20);
		}
	}
}
void QMyTreeWidget::textAreaChanged()
{
	document = qobject_cast<QTextDocument*>(sender());
	document->adjustSize();
	if (document)
	{
		editor = qobject_cast<QTextEdit*>(document->parent()->parent());
		if (editor)
		{
			int newheight = document->size().rheight() + 2;
			if (newheight != editor->height())
			{
				editor->setFixedHeight(newheight);
			}
		}
	}
}
void QMyTreeWidget::SliderValueChanged(int i)
{
	QSlider* sind = qobject_cast<QSlider*>(QObject::sender());
	QString objectname = sind->objectName();
	QString errtype = objectname.left(objectname.indexOf("+"));
	QString errname = objectname.mid(objectname.indexOf("+") + 1);
	_mparam[errtype.toStdString().c_str()][errname.toStdString().c_str()]["value"] = i;
	QTreeWidgetItem* cur = this->currentItem();
	cur->setData(1, Qt::DisplayRole, i);
	emit TempSave(objectname, QString::number(i));
}

QMyTreeWidget::~QMyTreeWidget()
{
	if (detailtext != nullptr)
	{
		delete detailtext;
		detailtext = nullptr;
	}
}