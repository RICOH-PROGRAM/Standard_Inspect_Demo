
#include "common.h"
namespace wikky_algo
{
	CheckParam _Node2Param(YAML::Node node)
	{
		CheckParam _param;
		_param._iThreadX = getValue<int>(node, "Param_DetNet", "X", 5);
		_param._iThreadY = getValue<int>(node, "Param_DetNet", "Y", 10);
		_param._iThreadZ = getValue<int>(node, "Param_DetNet", "Z", 101);
		return _param;
	};
	//todo
	YAML::Node _Param2Node(CheckParam checkparam, YAML::Node node)
	{
		YAML::Node _param = node;
		_param["Param_DetNet"]["X"]["value"] = checkparam._iThreadX;
		_param["Param_DetNet"]["Y"]["value"] = checkparam._iThreadY;
		_param["Param_DetNet"]["Z"]["value"] = checkparam._iThreadZ;
		return _param;
	};
}