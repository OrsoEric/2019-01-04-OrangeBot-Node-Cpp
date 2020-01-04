/****************************************************************
**	OrangeBot Project
*****************************************************************
**        /
**       /
**      /
** ______ \
**         \
**          \
*****************************************************************
**	OrangeBot Node C++
*****************************************************************
**  High performance C++ methods meant to be used by NODE.JS
**	orangebot.js script running inside the RPI3 B+ inside OrangeBot
**	The bindings take care of more compute intensive work not suited for javascript
**
**		OrangeBot Motor Board -> RPI 3B+ message decoding
**	Decode messages coming from the motor board
****************************************************************/

/****************************************************************************
**	INCLUDES
****************************************************************************/

//NODE bindings
#include <napi.h>
//C++ implementation of high performance methods
#include "ob.h"

/****************************************************************************
**	BINDINGS
****************************************************************************/

/****************************************************************************
**	@brief Function
**	ParseWrapped | Napi::CallbackInfo&
****************************************************************************/
//! @param f bool
//! @return bool |
//! @details
//! Feed a string to Uniparser
//! Uniparser takes care of decoding the string to update relevant fields
/***************************************************************************/

//Interface between function and NODE.JS
Napi::Number ParseWrapped(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
	//Check arguments
    if ((info.Length() != 1) || (!info[0].IsString()))
	{
		Napi::TypeError::New(env, "ERR: Expecting one argument of type String").ThrowAsJavaScriptException();
	}
	//Get argument
    Napi::String str = info[0].As<Napi::String>();
	//Execute function
	Orangebot::orangebotParse( std::string(str) );
	//Return
    return Napi::Number::New(env, (int)0);
} //End Function: ParseWrapped | Napi::CallbackInfo&

/****************************************************************************
**	@brief Function
**	GetPwmWrapped | Napi::CallbackInfo&
****************************************************************************/
//! @param f bool
//! @return bool |
//! @details
//! Get the PWM field reading
/***************************************************************************/

Napi::Number GetPwmWrapped(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	//Check arguments
    if ((info.Length() != 1) || (!info[0].IsNumber()))
	{
		Napi::TypeError::New(env, "ERR: Expecting one argument of type number").ThrowAsJavaScriptException();
	}
	//Get argument
	Napi::Number index = info[0].As<Napi::Number>();
	//Execute function
    int returnValue = Orangebot::get_pwm(index.Int32Value());
	//Return
    return Napi::Number::New(env, (int)returnValue);
}	//End function: GetPwmWrapped | Napi::CallbackInfo&

/****************************************************************************
**	@brief Function
**	Init | Napi::Env | Napi::Object
****************************************************************************/
//! @param f bool
//! @return bool |
//! @details
//! Select the methods to be exported to the NODE.JS application and initialize the module
/***************************************************************************/

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	//Initialize the module
	Orangebot::orangebotNodeCppInit();
	//Register methods accessible from the outside in the NODE.JS environment
	exports.Set( "parse", Napi::Function::New(env, ParseWrapped) );
	exports.Set( "getPwm", Napi::Function::New(env, GetPwmWrapped) );

    return exports;
}	//End function: Init | Napi::Env | Napi::Object


NODE_API_MODULE( OrangebotNodeCpp, Init)
