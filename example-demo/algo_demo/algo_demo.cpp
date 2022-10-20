#include "algo_demo.h"

//#include "logger.h"
#include <QCheckBox>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QSettings>
#include <functional>
#include <future>

using namespace std;
using namespace std::placeholders;


Qtalgo_demo::Qtalgo_demo(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
};

Qtalgo_demo::~Qtalgo_demo()
{
}
