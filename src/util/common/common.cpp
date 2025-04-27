
#include "common.h"
namespace wikky_algo
{
	CheckParam _Node2Param(YAML::Node node)
	{
		CheckParam _param;
		_param._iThreadX = getValue<int>(node, "Param_AxisMask", "X", 5);
		_param._iThreadY = getValue<int>(node, "Param_AxisMask", "Y", 10);
		_param._iThreadZ = getValue<int>(node, "Param_AxisMask", "Z", 101);
		return _param;
	};
	YAML::Node _Param2Node(CheckParam checkparam)
	{
		YAML::Node _param;
		_param["Param_AxisMask"]["X"]["value"] = checkparam._iThreadX;
		_param["Param_AxisMask"]["Y"]["value"] = checkparam._iThreadY;
		_param["Param_AxisMask"]["Z"]["value"] = checkparam._iThreadZ;
		return _param;
	};
}