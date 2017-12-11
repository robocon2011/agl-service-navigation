// Copyright 2017 AW SOFTWARE CO.,LTD
// Copyright 2017 AISIN AW CO.,LTD

#ifndef JSON_RESPONSE_ANALYZER_H_
#define JSON_RESPONSE_ANALYZER_H_

#include <json-c/json.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#include "libnavicore.hpp"

/**
*  @brief JSONレスポンス解析クラス
*/
class JsonResponseAnalyzer
{
public:
	static std::map< int32_t, naviapi::variant > AnalyzeResponseGetPosition( struct json_object * json );
	static std::vector< uint32_t > AnalyzeResponseGetAllRoutes( struct json_object * json );
	static uint32_t AnalyzeResponseCreateRoute( struct json_object * json );
	static std::map<uint32_t, std::string> AnalyzeResponseGetAllSessions( struct json_object * json );
};

#endif
