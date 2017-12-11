// Copyright 2017 AW SOFTWARE CO.,LTD
// Copyright 2017 AISIN AW CO.,LTD

#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <systemd/sd-event.h>
#include <json-c/json.h>
#include <traces.h>
#include "RequestManage.h"

/**
 *  グローバル変数
 */
std::string response_json;

/**
 *  @brief コンストラクタ
 */
RequestManage::RequestManage() : listener(nullptr)
{
	// コールバック設定
	this->wsj1_itf.on_hangup	= RequestManage::OnHangupStatic;
	this->wsj1_itf.on_call	  = RequestManage::OnCallStatic;
	this->wsj1_itf.on_event	 = RequestManage::OnEventStatic;
}

/**
 *  @brief デストラクタ
 */
RequestManage::~RequestManage()
{
}

/**
 *  @brief  サービスと接続する
 *  @param  接続先のURL
 *  @return 接続の成否
 */
bool RequestManage::Connect(const char* api_url, RequestManageListener* listener)
{
	this->listener = listener;

	int rc = sd_event_default(&this->loop);
	if (rc < 0) {
		TRACE_ERROR("connection to default event loop failed: %s\n", strerror(-rc));
		return false;
	}

	this->wsj1 = afb_ws_client_connect_wsj1(loop, api_url, &this->wsj1_itf, NULL);
	if (this->wsj1 == NULL) {
		TRACE_ERROR("connection to %s failed: %m\n", api_url);
		return false;
	}
	
	return true;
}

/**
 *  @brief  サービスとの接続状態チェック
 *  @return 接続の状態
 */
bool RequestManage::IsConnect(){
	return (this->wsj1 != NULL);
}

/**
 *  @brief  BinderのAPIをコールする
 *  @param  api	  API名
 *  @param  verb	 メソッド名
 *  @param  req_json Json形式のリクエスト
 *  @return 処理の成否
 */
bool RequestManage::CallBinderAPI(const char* api, const char* verb, const char* req_json)
{
	// リクエスト送信
	int rc = afb_wsj1_call_s(this->wsj1, api, verb, req_json, RequestManage::OnReplyStatic, this);
	if (rc < 0)
	{
		TRACE_ERROR("calling %s/%s(%s) failed: %m\n", api, verb, req_json);
		return false;
	}

	// ライブラリ内部がsd_eventで動いてるため、
	// runを呼び出さないとコールバックが呼ばれない
	sd_event_run(this->loop, 10 * 1000 * 1000); // 10[sec]

	return true;
}

/**
 *  @brief  レスポンス取得
 */
std::string RequestManage::GetResponse()
{
	return response_json;
}

/**
 *  @brief  セッションハンドル設定
 *  @param session セッションハンドル
 */
void RequestManage::SetSessionHandle( uint32_t session )
{
	this->sessionHandle = session;
}

/**
 *  @brief  セッションハンドル取得
 *  @return セッションハンドル
 */
uint32_t RequestManage::GetSessionHandle()
{
	return this->sessionHandle;
}

/**
 *  @brief  ルートハンドル設定
 *  @param session ルートハンドル
 */
void RequestManage::SetRouteHandle( uint32_t route )
{
	this->routeHandle = route;
}

/**
 *  @brief  ルートハンドル取得
 *  @return ルートハンドル
 */
uint32_t RequestManage::GetRouteHandle()
{
	return this->routeHandle;
}

void RequestManage::OnReply(struct afb_wsj1_msg *msg)
{
	struct json_object * json = afb_wsj1_msg_object_j(msg);

	this->listener->OnReply(json);
}

void RequestManage::OnHangup(struct afb_wsj1 *wsj1)
{
}

void RequestManage::OnCallStatic(const char *api, const char *verb, struct afb_wsj1_msg *msg)
{
}

void RequestManage::OnEventStatic(const char *event, struct afb_wsj1_msg *msg)
{
}


/**
 *  @brief  サービスからの応答コールバック
 */
void RequestManage::OnReplyStatic(void *closure, struct afb_wsj1_msg *msg)
{
	RequestManage* instance = (RequestManage *)closure;
	instance->OnReply(msg);
}

/**
 *  @brief  サービスのハングアップ通知
 */
void RequestManage::OnHangupStatic(void *closure, struct afb_wsj1 *wsj1)
{
}

void RequestManage::OnCallStatic(void *closure, const char *api, const char *verb, struct afb_wsj1_msg *msg)
{
}

void RequestManage::OnEventStatic(void *closure, const char *event, struct afb_wsj1_msg *msg)
{
}

