#pragma once
#include <QtCore>
#include <QTreeWidget>
#include <QObject>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/yaml.h"

#include <QTextEdit>
#include <QTimer>
#include <QSlider>
#include <QLineEdit>


namespace YAML {
	struct CharacterType {
		std::string type;
		int value;
		int Smallest;
		int Biggest;
		QString CN_Name;
		QString CN_Discrib;
	};
	struct ERRORSetting {
		int ability;
		int value;
		QString CN_Name;
	};
	//template<>
	//struct convert<std::string> {
	//	static bool decode(const Node& node, std::string& st) {
	//		try
	//		{
	//			st = node["type"].as<std::string>();
	//		}
	//		catch (YAML::Exception e)
	//		{
	//		}
	//		return true;
	//	}
	//};
	template<>
	struct convert<CharacterType> {
		static bool decode(const Node& node, CharacterType& cType) {
			try
			{
				cType.type = node["type"].as<std::string>();
				cType.value = node["value"].as<double>();
				cType.Smallest = node["Smallest"].as<int>();
				cType.Biggest = node["Biggest"].as<int>();
				cType.CN_Name = node["CN_Name"].as<std::string>().c_str();
				cType.CN_Discrib = node["CN_Discrib"].as<std::string>().c_str();
			}
			catch (YAML::Exception e)
			{
			}
			return true;
		}
	};
	template<>
	struct convert<ERRORSetting> {
		static bool decode(const Node& node, ERRORSetting& cType) {
			try
			{
				cType.ability = node["ability"].as<int>();
				cType.value = node["value"].as<int>();
				cType.CN_Name = node["CN_Name"].as<std::string>().c_str();
			}
			catch (YAML::Exception e)
			{
			}
			return true;
		}
	};
}

class QMyTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	QMyTextEdit(QWidget* parent)
		: QTextEdit(parent)
	{
	}
private:
	QTimer* times = nullptr;
public slots:
	void showEvent(QShowEvent*)
	{
		times = new QTimer(this);
		times->setSingleShot(true);
		connect(times, &QTimer::timeout, [=]()
			{
				this->setVisible(false);
			});
		times->start(2000);
	}
};

class QMySlider : public QSlider
{
	Q_OBJECT
public:
	QMySlider(Qt::Orientation orientation, QWidget* parent = nullptr)
		: QSlider(orientation, parent)
	{
	}
	void wheelEvent(QWheelEvent* e)
	{
		QWidget::wheelEvent(e);
		//备注，千万别使用QSlider::wheelEvent(e);否则等于没重写
	}
};

class QMyTreeWidget : public QTreeWidget
{
	Q_OBJECT
signals:
	void TempSave(QString, QString);
	void Signal_DrawRegion(QString);
private:
	YAML::Node _mparam;
	QTextDocument* document = nullptr;
	QTextEdit* editor = nullptr;
	QMyTextEdit* detailtext = nullptr;
	QString m_ErrorNode;
public:
	QMyTreeWidget(QWidget* parent);
	~QMyTreeWidget();
	bool LoadYAMLFile(YAML::Node);
	bool SaveYAMLFile(QString filepath);
	void expandbyString();
public slots:
	void SliderValueChanged(int);
	void ComboValueChanged(int);
	void CheckValueChanged(int);
	void ClickPushButton();
	void LineValueChanged(QString);
	void showCnDetail(QTreeWidgetItem*, int);
	void textAreaChanged();
};
