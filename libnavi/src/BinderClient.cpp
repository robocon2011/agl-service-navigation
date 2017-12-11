// Copyright 2017 AW SOFTWARE CO.,LTD
// Copyright 2017 AISIN AW CO.,LTD

#include <cstring>

#include "BinderClient.h"
#include "JsonRequestGenerator.h"
#include "JsonResponseAnalyzer.h"

#include "traces.h"

/**
 *  @brief コンストラクタ
 */
BinderClient::BinderClient() : navicoreListener(nullptr)
{
	// インスタンス化
	requestMng = new RequestManage();
}

/**
 *  @brief デストラクタ
 */
BinderClient::~BinderClient()
{
	delete requestMng;
}

/**
 *  @brief Binderサーバーと接続する
 */
bool BinderClient::ConnectServer(std::string url, naviapi::NavicoreListener* listener)
{
	this->navicoreListener = listener;

	if( !requestMng->Connect(url.c_str(), this))
	{
		TRACE_ERROR("cannot connect to binding service.\n");
		return false;
	}

	return true;
}

/**
 *  @brief Binder経由でGeniviのGetPositionを呼び出し、結果を取得する
 */
void BinderClient::NavicoreGetPosition(const std::vector< int32_t >& valuesToReturn)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		std::string req_json = JsonRequestGenerator::CreateRequestGetPosition(valuesToReturn);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_GETPOSITION, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_getposition success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_getposition failed.\n");
		}
	}
}

/**
 *  @brief ルートハンドル取得
 */
void BinderClient::NavicoreGetAllRoutes()
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		std::string req_json = JsonRequestGenerator::CreateRequestGetAllRoutes();

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_GETALLROUTES, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_getallroutes success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_getallroutes failed.\n");
		}
	}
}

/**
 *  @brief ルート作成モジュールハンドルの生成
 */
void BinderClient::NavicoreCreateRoute(const uint32_t& sessionHandle)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestCreateRoute(&session);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_CREATEROUTE, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_createroute success.\n");

		}
		else
		{
			TRACE_ERROR("navicore_createroute failed.\n");
		}
	}
}

/**
 *  @brief  デモ一時停止
 */
void BinderClient::NavicorePauseSimulation(const uint32_t& sessionHandle)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestPauseSimulation(&session);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_PAUSESIMULATION, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_pausesimulationmode success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_pausesimulationmode failed.\n");
		}
	}
}

/**
 *  @brief  デモ状態設定
 */
void BinderClient::NavicoreSetSimulationMode(const uint32_t& sessionHandle, const bool& activate)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestSetSimulationMode(&session, &activate);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_SETSIMULATIONMODE, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_setsimulationmode success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_setsimulationmode failed.\n");
		}
	}
}

/**
 *  @brief  ルート情報削除
 */
void BinderClient::NavicoreCancelRouteCalculation(const uint32_t& sessionHandle, const uint32_t& routeHandle)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestCancelRouteCalculation(&session, &routeHandle);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_CANCELROUTECALCULATION, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_cancelroutecalculation success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_cancelroutecalculation failed.\n");
		}
	}
}

/**
 *  @brief 目的地設定
 */
void BinderClient::NavicoreSetWaypoints(const uint32_t& sessionHandle, const uint32_t& routeHandle, const bool& startFromCurrentPosition, const std::vector<naviapi::Waypoint>& waypointsList)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		uint32_t route = requestMng->GetRouteHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestSetWaypoints(&session, &route, 
													 &startFromCurrentPosition, &waypointsList);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_SETWAYPOINTS, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_setwaypoints success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_setwaypoints failed.\n");
		}
	}
}

/**
 *  @brief  ルート計算処理
 */
void BinderClient::NavicoreCalculateRoute(const uint32_t& sessionHandle, const uint32_t& routeHandle)
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		uint32_t session = requestMng->GetSessionHandle();
		uint32_t route = requestMng->GetRouteHandle();
		std::string req_json = JsonRequestGenerator::CreateRequestCalculateroute(&session, &route);

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_CALCULATEROUTE, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_calculateroute success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_calculateroute failed.\n");
		}
	}
}

/**
 *  @brief  各Naviのセッション情報取得
 *  @return セッション情報のマップ
 */
void BinderClient::NavicoreGetAllSessions()
{
	// 接続中かチェック
	if( requestMng->IsConnect() )
	{
		// JSONリクエスト生成
		std::string req_json = JsonRequestGenerator::CreateRequestGetAllSessions();

		// リクエスト送信
		if( requestMng->CallBinderAPI(API_NAME, VERB_GETALLSESSIONS, req_json.c_str()) )
		{
			TRACE_DEBUG("navicore_getallsessions success.\n");
		}
		else
		{
			TRACE_ERROR("navicore_getallsessions failed.\n");
		}
	}
}

void BinderClient::OnReply(struct json_object* reply)
{
	struct json_object* requestObject = nullptr;
	json_object_object_get_ex(reply, "request", &requestObject);

	struct json_object* infoObject = nullptr;
	json_object_object_get_ex(requestObject, "info", &infoObject);

	const char* info = json_object_get_string(infoObject);

	if (strcmp(VERB_GETALLSESSIONS, info) == 0)
	{
		std::map<uint32_t, std::string> ret = JsonResponseAnalyzer::AnalyzeResponseGetAllSessions(reply);

		// セッション設定
		requestMng->SetSessionHandle( ret.begin()->first );

		this->navicoreListener->getAllSessions_reply(ret);
	}
	else if (strcmp(VERB_GETPOSITION, info) == 0)
	{
		std::map< int32_t, naviapi::variant > ret = JsonResponseAnalyzer::AnalyzeResponseGetPosition(reply);

	this->navicoreListener->getPosition_reply(ret);
	}
	else if (strcmp(VERB_GETALLROUTES, info) == 0)
	{
		std::vector< uint32_t > ret = JsonResponseAnalyzer::AnalyzeResponseGetAllRoutes(reply);

		// ルートハンドル保存
		if(ret.size() > 0)
		{
			requestMng->SetRouteHandle(ret[0]);
		}

		this->navicoreListener->getAllRoutes_reply(ret);
	}
	else if (strcmp(VERB_CREATEROUTE, info) == 0)
	{
		uint32_t ret = JsonResponseAnalyzer::AnalyzeResponseCreateRoute(reply);

		// ルートハンドル保存
		requestMng->SetRouteHandle(ret);

		this->navicoreListener->createRoute_reply(ret);
	}
}

