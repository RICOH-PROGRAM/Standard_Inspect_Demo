﻿#include "stdio.h"
#include <Windows.h>
#include <iostream>
#include "logger.h"
#include "../../src/basealg/ibasealgorithm.h"
#include <io.h>
#include  <direct.h>  

void getFiles(string path, vector<string>& files, const char* sType)
{
	//文件句柄
	//long hFile = 0;
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files, sType);
				}
			}
			else
			{
				char* pName = fileinfo.name;
				char* pFind = strstr(pName, sType);
				if (pFind != NULL)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}

bool cmp_max(std::string x, std::string y) {
	try {
		int xx1 = std::stoi(x.substr(x.find_last_of("\\") + 1, x.find_first_of("_") - x.find_last_of("\\") - 1));
		int yy1 = std::stoi(y.substr(y.find_last_of("\\") + 1, y.find_first_of("_") - y.find_last_of("\\") - 1));
		return xx1 < yy1;
	}
	catch (const invalid_argument& e) {
		cout << "无效输入，无法解析整数。" << endl;
		return false;
	}
	catch (const out_of_range& e) {
		cout << "输入数字超出范围。" << endl;
		return false;
	}
	return std::stoi(x) > std::stoi(y);
}
int main(int argc, char *argv[])
{
    HINSTANCE hdll;
	char   buffer[MAX_PATH];
	getcwd(buffer, MAX_PATH);
	std::string sts = buffer;
	sts += "/demo_Algo.dll";
	std::cout << sts << std::endl;
	hdll = LoadLibrary(sts.c_str());
    wikky_algo::pExportALG createclass = (wikky_algo::pExportALG)GetProcAddress(hdll, "CreateExportAlgObj");
    wikky_algo::pDeleteALG deleteclass = (wikky_algo::pDeleteALG)GetProcAddress(hdll, "DeleteExportAlgObj");
    wikky_algo::IBaseAlg* _CheckClass = createclass();
	_CheckClass->setLogLevel(1);
	std::string sn = "local_camera";
	_CheckClass->initAlgoparam(sn);

	std::cout <<"input the test image file:" << std::endl;
	std::string filename;
	std::cin >> filename;
	std::vector<std::string> files;
	std::cout <<"read imageformat\r\nFORMATMONO:	0\r\nFORMATBGR:	1\r\nFORMATDEPTH:	2\r\nFORMATBAYER:	3\r\n" << std::endl;
	std::string format;
	std::cin >> format;
	int _format = atoi(format.c_str());

	while (getchar() != '\n')
	{

	}
	getFiles(filename, files,".bmp");
	std::sort(files.begin(), files.end(), cmp_max);
	for (auto it : files)
	{
		cv::Mat img;

		wikky_algo::SingleMat singleMat;
		int _depth, _channel;

		singleMat.format = 1000 + _format;
		switch (singleMat.format)
		{
		case FORMATDEPTH:
			_channel = 1;
			_depth = sizeof(double);
			img = cv::imread(it, cv::IMREAD_ANYDEPTH);
			break;
		case FORMATBAYER:
		case FORMATMONO:
			_channel = 1;
			_depth = sizeof(uchar);
			img = cv::imread(it, cv::IMREAD_GRAYSCALE);
			break;
		case FORMATBGR:
			_channel = 3;
			_depth = sizeof(uchar);
			img = cv::imread(it, cv::IMREAD_COLOR);
			break;
		default:
			LOGE("ERROR FORMAT");
		}
		singleMat.w = img.cols;
		singleMat.h = img.rows;
		singleMat.imgori = new char[singleMat.w * singleMat.h * _depth * _channel];
		memcpy(singleMat.imgori, (void*)img.data, singleMat.w * singleMat.h * _depth * _channel);

		if (_CheckClass)
		{

			_CheckClass->doing(singleMat);
		}
		std::cout << "result:" << singleMat._iresult << std::endl;
		std::cout << "error message:" << std::endl;
		for (auto it : singleMat.error_message)
		{
			std::cout << it << std::endl;
		}
		std::cout << "press any key to continue." << std::endl;
		std::cout << "e to exit." << std::endl;
		char c = getchar();
		if(0==strcmp("e", &c))
            break;
	}
    deleteclass(_CheckClass);
    FreeLibrary(hdll);
    LOGI("exit");


    return 0;
}
