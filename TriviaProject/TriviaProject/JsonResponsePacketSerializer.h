#pragma once
#include "json.hpp"
#include "Structs.h"
using json = nlohmann::json;

static class JsonResponsePacketSerializer
{
public:
	const char* serializeLoginResponse(LoginResponse Response);
	const char* serializeSignUpResponse(SignUpResponse Response);
	const char* serializeErrorResponse(ErrorResponse Response);
};