// Copyright 2017 AW SOFTWARE CO.,LTD
// Copyright 2017 AISIN AW CO.,LTD

#include "binder_reply.h"
#include "genivi/genivi-navicore-constants.h"

/**
 *  @brief	  GeniviAPI GetPositionコール
 *  @param[in]  posList Geneviから取得した情報のキーと値のmap情報
 *  @return	 レスポンス情報
 */
APIResponse BinderReply::ReplyNavicoreGetPosition( std::map<int32_t, double>& posList )
{
	APIResponse response = {0};

	// レスポンスとして返すjson情報
	struct json_object* response_json = json_object_new_array();
	std::map<int32_t, double>::iterator it;
	
	// 引数のmapが空ならreturn
	if(posList.empty())
	{
		response.isSuccess  = false;
		response.errMessage = "posList is empty";
		response.json_data  = response_json;
		return response;
	}

	// 渡されたGeniviの応答をjson形式にする
	for (it = posList.begin(); it != posList.end(); it++)
	{
		struct json_object* obj = json_object_new_object();

		switch(it->first)
		{
			// 緯度
			case NAVICORE_LATITUDE:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_LATITUDE));
				json_object_object_add(obj, "value", json_object_new_double(it->second) );
				json_object_array_add(response_json, obj);
				break;

			// 経度
			case NAVICORE_LONGITUDE:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_LONGITUDE));
				json_object_object_add(obj, "value", json_object_new_double(it->second));
				json_object_array_add(response_json, obj);
				break;

			// 方向
			case NAVICORE_HEADING:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_HEADING));
//				json_object_object_add(obj, "value", json_object_new_int(it->second));
				json_object_object_add(obj, "value", json_object_new_boolean (it->second));
				json_object_array_add(response_json, obj);
				break;

#if 0 // 未サポート
			// タイムスタンプ
			case NAVICORE_TIMESTAMP:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_TIMESTAMP));
				json_object_object_add(obj, "value", json_object_new_int(it->second));
				json_object_array_add(response_json, obj);
				break;

			// 速度
			case NAVICORE_SPEED:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_SPEED));
				json_object_object_add(obj, "value", json_object_new_int(it->second));
				json_object_array_add(response_json, obj);
				break;
#endif
			// デモモード
			case NAVICORE_SIMULATION_MODE:
				json_object_object_add(obj, "key", json_object_new_int(NAVICORE_SIMULATION_MODE));
//				json_object_object_add(obj, "value", json_object_new_int(it->second));
				json_object_object_add(obj, "value", json_object_new_boolean (it->second));
				json_object_array_add(response_json, obj);
				break;

			default:
				fprintf(stderr, "Unknown key.");
				json_object_put(obj);
				break;
		}
	}

	response.json_data = response_json;
	response.isSuccess = true;
	return response;
}


/**
 *  @brief	  GeniviAPI GetAllRoutesコール
 *  @param[in]  allRoutes ルートハンドル情報
 *  @return	 レスポンス情報
 */
APIResponse BinderReply::ReplyNavicoreGetAllRoutes( std::vector< uint32_t > &allRoutes )
{
	APIResponse response = {0};

	// レスポンスとして返すjson情報
	struct json_object* response_json = json_object_new_array();

	if (0 < allRoutes.size())
	{
		std::vector< uint32_t >::iterator it;

		for (it = allRoutes.begin(); it != allRoutes.end(); it++)
		{
			struct json_object* obj = json_object_new_object();
			json_object_object_add(obj, "route", json_object_new_int(*it));
			json_object_array_add(response_json, obj);
		}
	}

	response.json_data = response_json;
	response.isSuccess = true;
	return response;
}


/**
 *  @brief	  GeniviAPI CreateRouteコール
 *  @param[in]  route ルートハンドル
 *  @return	 レスポンス情報
 */
APIResponse BinderReply::ReplyNavicoreCreateRoute( uint32_t route )
{
	APIResponse response;

	// レスポンスとして返すjson情報
	struct json_object* response_json = json_object_new_object();
	json_object_object_add(response_json, "route", json_object_new_int(route));

	response.json_data = response_json;
	response.isSuccess = true;
	return response;
}


/**
 *  @brief	  GeniviAPI GetAllSessionsコール
 *  @param[in]  allSessions Geneviから取得した情報のキーと値のmap情報
 *  @return	 レスポンス情報
 */
APIResponse BinderReply::ReplyNavicoreGetAllSessions( std::map<uint32_t, std::string> &allSessions )
{
	APIResponse response = {0};

	// レスポンスとして返すjson情報
	struct json_object* response_json = json_object_new_array();
	std::map<uint32_t, std::string>::iterator it;

	for (it = allSessions.begin(); it != allSessions.end(); it++)
	{
//	  printf("first = %d, second = %s\n", it->first, it->second.c_str());
		struct json_object* obj = json_object_new_object();

		if (NAVICORE_INVALID != it->first)
		{
			json_object_object_add(obj, "sessionHandle", json_object_new_int(it->first));
			json_object_object_add(obj, "client", json_object_new_string(it->second.c_str()));
			json_object_array_add(response_json, obj);
		}
		else
		{
			fprintf(stderr, "invalid key.");
			json_object_put(obj);
		}
	}

	response.json_data = response_json;
	response.isSuccess = true;
	return response;
}

