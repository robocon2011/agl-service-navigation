// Copyright 2017 AW SOFTWARE CO.,LTD
// Copyright 2017 AISIN AW CO.,LTD

#include <string.h>

#include "binder_reply.h"
#include "genivi_request.h"
#include "analyze_request.h"
#include "genivi/genivi-navicore-constants.h"

#define AFB_BINDING_VERSION 2

extern "C" {
	#include <afb/afb-binding.h>
}

/**
 *  変数宣言
 */
GeniviRequest* geniviRequest;   // Geniviにリクエストを送る
BinderReply* binderReply;	   // Geniviの応答結果をjson形式に変換する
AnalyzeRequest* analyzeRequest; // BinderClientのリクエストを解析し、GeniviAPIに渡す引数を作成する

/**
 *  @brief navicore_getpositionリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreGetPosition(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_getposition");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	std::vector< int32_t > Params;
	if( !analyzeRequest->CreateParamsGetPosition( req_json_str, Params ))
	{
		afb_req_fail(req, "failed", "navicore_getposition Bad Request");
		return;
	}

	// GENEVI APIコール
	std::map< int32_t, double > posList = geniviRequest->NavicoreGetPosition( Params );

	// json形式の応答に変換
	APIResponse response = binderReply->ReplyNavicoreGetPosition( posList );

	// 成功時
	if(response.isSuccess)
	{
		AFB_REQ_NOTICE(req, "res_json_str = %s", json_object_to_json_string(response.json_data));
		// BinderClientに成功を返す
		afb_req_success(req, response.json_data, "navicore_getposition");
	}
	else
	{
		AFB_REQ_ERROR(req, "%s - %s:%d", response.errMessage.c_str(), __FILE__, __LINE__);
		afb_req_fail(req, "failed", "navicore_getposition Bad Request");
	}

	// json object解放
	json_object_put(response.json_data);

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_getallroutesリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreGetAllRoutes(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_getallroutes");

	// Json形式のリクエスト情報は無し
	AFB_REQ_NOTICE(req, "req_json_str = none");

	// GENEVI APIコール
	std::vector< uint32_t > allRoutes = geniviRequest->NavicoreGetAllRoutes();

	// json形式の応答に変換
	APIResponse response = binderReply->ReplyNavicoreGetAllRoutes( allRoutes );

	// 成功時
	if(response.isSuccess)
	{
		AFB_REQ_NOTICE(req, "res_json_str = %s", json_object_to_json_string(response.json_data));
		// BinderClientに成功を返す
		afb_req_success(req, response.json_data, "navicore_getallroutes");
	}
	else
	{
		AFB_REQ_ERROR(req, "%s - %s:%d", response.errMessage.c_str(), __FILE__, __LINE__);
		afb_req_fail(req, "failed", "navicore_getallroutes Bad Request");
	}

	// json object解放
	json_object_put(response.json_data);

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_createrouteリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreCreateRoute(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s ", __func__);
	AFB_REQ_DEBUG(req, "request navicore_createroute");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	if( !analyzeRequest->CreateParamsCreateRoute( req_json_str, sessionHdl ))
	{
		afb_req_fail(req, "failed", "navicore_createroute Bad Request");
		return;
	}

	// GENEVI APIコール
	uint32_t routeHdl = geniviRequest->NavicoreCreateRoute( sessionHdl );

	// json形式の応答に変換
	APIResponse response = binderReply->ReplyNavicoreCreateRoute( routeHdl );

	// 成功時
	if(response.isSuccess)
	{
		AFB_REQ_NOTICE(req, "res_json_str = %s", json_object_to_json_string(response.json_data));
		// BinderClientに成功を返す
		afb_req_success(req, response.json_data, "navicore_createroute");
	}
	else
	{
		AFB_REQ_ERROR(req, "%s - %s:%d", response.errMessage.c_str(), __FILE__, __LINE__);
		afb_req_fail(req, "failed", "navicore_createroute Bad Request");
	}

	// json object解放
	json_object_put(response.json_data);

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_pausesimulationリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicorePauseSimulation(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_pausesimulation");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	if( !analyzeRequest->CreateParamsPauseSimulation( req_json_str, sessionHdl ))
	{
		afb_req_fail(req, "failed", "navicore_pausesimulation Bad Request");
		return;
	}

	// GENEVI APIコール
	geniviRequest->NavicorePauseSimulation( sessionHdl );

	// 応答不要APIのためjson形式の応答に変換は不要
	AFB_REQ_NOTICE(req, "res_json_str = none");

	// BinderClientに成功を返す
	afb_req_success(req, NULL, "navicore_pausesimulation");

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_setsimulationmodeリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreSetSimulationMode(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_setsimulationmode");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	bool simuMode = false;
	if( !analyzeRequest->CreateParamsSetSimulationMode( req_json_str, sessionHdl, simuMode ))
	{
		afb_req_fail(req, "failed", "navicore_setsimulationmode Bad Request");
		return;
	}

	// GENEVI APIコール
	geniviRequest->NavicoreSetSimulationMode( sessionHdl, simuMode );

	// 応答不要APIのためjson形式の応答に変換は不要
	AFB_REQ_NOTICE(req, "res_json_str = none");

	// BinderClientに成功を返す
	afb_req_success(req, NULL, "navicore_setsimulationmode");

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_cancelroutecalculationリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreCancelRouteCalculation(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_cancelroutecalculation");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	uint32_t routeHdl = 0;
	if( !analyzeRequest->CreateParamsCancelRouteCalculation( req_json_str, sessionHdl, routeHdl ))
	{
		afb_req_fail(req, "failed", "navicore_cancelroutecalculation Bad Request");
		return;
	}

	// GENEVI APIコール
	geniviRequest->NavicoreCancelRouteCalculation( sessionHdl, routeHdl );

	// 応答不要APIのためjson形式の応答に変換は不要
	AFB_REQ_NOTICE(req, "res_json_str = none");

	// BinderClientに成功を返す
	afb_req_success(req, NULL, "navicore_cancelroutecalculation");

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_setwaypointsリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreWaypoints(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_setwaypoints");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	uint32_t routeHdl = 0;
	bool currentPos = false;
	std::vector<Waypoint> waypointsList;
	if( !analyzeRequest->CreateParamsSetWaypoints( req_json_str, sessionHdl, routeHdl, currentPos, waypointsList ))
	{
		afb_req_fail(req, "failed", "navicore_setwaypoints Bad Request");
		return;
	}

	// GENEVI APIコール
	geniviRequest->NavicoreSetWaypoints( sessionHdl, routeHdl, currentPos, waypointsList );

	// 応答不要APIのためjson形式の応答に変換は不要
	AFB_REQ_NOTICE(req, "res_json_str = none");

	// BinderClientに成功を返す
	afb_req_success(req, NULL, "navicore_setwaypoints");

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_calculaterouteリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreCalculateRoute(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_calculateroute");

	// Json形式のリクエスト取得
	json_object* req_json = afb_req_json(req);
	const char* req_json_str = json_object_to_json_string(req_json);
	AFB_REQ_NOTICE(req, "req_json_str = %s", req_json_str);

	// リクエスト解析して、Geniviに渡す引数を作成
	uint32_t sessionHdl = 0;
	uint32_t routeHdl = 0;
	if( !analyzeRequest->CreateParamsCalculateRoute( req_json_str, sessionHdl, routeHdl ))
	{
		afb_req_fail(req, "failed", "navicore_calculateroute Bad Request");
		return;
	}

	// GENEVI APIコール
	geniviRequest->NavicoreCalculateRoute( sessionHdl, routeHdl );

	// 応答不要APIのためjson形式の応答に変換は不要
	AFB_REQ_NOTICE(req, "res_json_str = none");

	// BinderClientに成功を返す
	afb_req_success(req, NULL, "navicore_calculateroute");

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief navicore_getallsessionsリクエストコールバック
 *  @param[in] req クライアントからの要求
 */
void OnRequestNavicoreGetAllSessions(afb_req req)
{
	AFB_REQ_NOTICE(req, "--> Start %s()", __func__);
	AFB_REQ_DEBUG(req, "request navicore_getallsessions");

	// Json形式のリクエスト情報は無し
	AFB_REQ_NOTICE(req, "req_json_str = none");

	// GENEVI APIコール
	std::map<uint32_t, std::string> allSessions = geniviRequest->NavicoreGetAllSessions();

	// json形式の応答に変換
	APIResponse response = binderReply->ReplyNavicoreGetAllSessions( allSessions );

	// 成功時
	if(response.isSuccess)
	{
		AFB_REQ_NOTICE(req, "res_json_str = %s", json_object_to_json_string(response.json_data));
		// BinderClientに成功を返す
		afb_req_success(req, response.json_data, "navicore_getallsessions");
	}
	else
	{
		AFB_REQ_ERROR(req, "%s - %s:%d", response.errMessage.c_str(), __FILE__, __LINE__);
		afb_req_fail(req, "failed", "navicore_getallsessions Bad Request");
	}

	// json object解放
	json_object_put(response.json_data);

	AFB_REQ_NOTICE(req, "<-- End %s()", __func__);
}


/**
 *  @brief サービス起動時に呼ばれるコールバック
 *		 各インスタンスを作成
 */
int Init()
{
	// インスタンス作成
	geniviRequest   = new GeniviRequest();
	binderReply	 = new BinderReply();
	analyzeRequest  = new AnalyzeRequest();
	
	return 0;
}

/**
 *  @brief API定義
 */
const afb_verb_v2 verbs[] = 
{
	 { verb : "navicore_getposition",			callback : OnRequestNavicoreGetPosition },
	 { verb : "navicore_getallroutes",		   callback : OnRequestNavicoreGetAllRoutes },
	 { verb : "navicore_createroute",			callback : OnRequestNavicoreCreateRoute },
	 { verb : "navicore_pausesimulation",		callback : OnRequestNavicorePauseSimulation },
	 { verb : "navicore_setsimulationmode",	  callback : OnRequestNavicoreSetSimulationMode },
	 { verb : "navicore_cancelroutecalculation", callback : OnRequestNavicoreCancelRouteCalculation },
	 { verb : "navicore_setwaypoints",		   callback : OnRequestNavicoreWaypoints },
	 { verb : "navicore_calculateroute",		 callback : OnRequestNavicoreCalculateRoute },
	 { verb : "navicore_getallsessions",		 callback : OnRequestNavicoreGetAllSessions },
	 { verb : NULL }
};

/**
 *  @brief サービス定義
 */
const afb_binding_v2 afbBindingV2 = 
{
	 "naviapi",
	 "",
	 "",
	 verbs,
	 NULL,
	 Init
};

